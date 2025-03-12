/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "profiler.h"

#define FREERTOS_TASK_ADDITIONS_AS_HEADER (1)
#include "freertos_tasks_c_additions.h"

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
// Scheduled tasks will use thread local storage for their data. For all other profiler purposes,
// store data here
static Profiler_Data_S gProfilerNonScheduledData[PROFILER_NON_SCHEDULED_MAX_NUM];
static TaskHandle_t gProfilerScheduledTaskHandles[PROFILER_SCHEDULED_MAX_NUM];
static uint32_t gProfilerLoadStartCounts[PROFILER_MAX_NUM];
static uint32_t gProfilerLoadEndCounts[PROFILER_MAX_NUM];
static uint32_t gProfilerLoadTicks;
static uint32_t gProfilerLoadIdleTicks;
static float gProfilerTotalLoad;
static float gProfilerLoad[PROFILER_MAX_NUM];

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
static Profiler_Data_S * ProfilerGetDataPointer(const Profiler_E profiler)
{
    Profiler_Data_S * pData = NULL;

    if (profiler < PROFILER_NON_SCHEDULED_MAX_NUM)
    {
        // Non-scheduled
        pData = &gProfilerNonScheduledData[profiler];
    }
    else if (profiler < PROFILER_MAX_NUM)
    {
        // Scheduled task
        TaskHandle_t taskHandle = gProfilerScheduledTaskHandles[PROFILER_SCHEDULED_IDX(profiler)];

        if (NULL != taskHandle)
        {
            void * tlsPointer = pvTaskGetThreadLocalStoragePointer(taskHandle, THREAD_LOCAL_STORAGE_PROFILER_IDX);

            if (NULL != tlsPointer)
            {
                pData = (Profiler_Data_S *)tlsPointer;
            }
        }
    }
    else
    {
        // Invalid
    }

    return pData;
}

static void ProfilerCollectPeriodStats(Profiler_Data_S * const pData, const uint32_t period)
{
    if (NULL != pData)
    {
        pData->minPeriod = MIN(pData->minPeriod, period);
        pData->maxPeriod = MAX(pData->maxPeriod, period);
        pData->sumPeriods += period;
        pData->numPeriods += 1U;

        pData->runTimeCounts += period;

        // In configured number of window periods is 0, rely on periodic profiler poll to clear stats
        if (   (pData->configWindowNumPeriods != 0U)
            && (pData->numPeriods >= pData->configWindowNumPeriods))
        {
            pData->latchedAvgPeriod = (pData->sumPeriods / pData->numPeriods);
            pData->latchedMinPeriod = pData->minPeriod;
            pData->latchedMaxPeriod = pData->maxPeriod;

            pData->numPeriods = 0U;
            pData->sumPeriods = 0U;
            pData->minPeriod = UINT_MAX;
            pData->maxPeriod = 0U;
        }
    }
}

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// Implementations for configGENERATE_RUN_TIME_STATS
//--------------------------------------------------------------------------------------------------
void configureTimerForRunTimeStats(void)
{
    ProfilerSpecificClearTimerUs();
}

unsigned long getRunTimeCounterValue(void)
{
    return ProfilerSpecificGetTimerUs();
}

//--------------------------------------------------------------------------------------------------
// Profiler functions
//--------------------------------------------------------------------------------------------------
void ProfilerScheduledTaskRegister(const Profiler_E profiler, void * taskHandle)
{
    if ((profiler >= PROFILER_SCHEDULED_FIRST) && (profiler < PROFILER_MAX_NUM))
    {
        gProfilerScheduledTaskHandles[PROFILER_SCHEDULED_IDX(profiler)] = (TaskHandle_t)taskHandle;
    }
}

//--------------------------------------------------------------------------------------------------
// Profiler period checks
//--------------------------------------------------------------------------------------------------
void ProfilerScheduledTaskCheckIn(void)
{
    // Called from FreeRTOS Hook

    // Going from task handle to index would require a lookup.
    // As an optimization, use thread local storage to directly acquire profiler data.
    // NULL task handle will yield this task's storage.
    void * const tlsPointer = pvTaskGetThreadLocalStoragePointer(NULL, THREAD_LOCAL_STORAGE_PROFILER_IDX);

    if (NULL != tlsPointer)
    {
        Profiler_Data_S * const pData = (Profiler_Data_S * const)tlsPointer;
        pData->checkInTime = ProfilerSpecificGetTimerUs();
    }
}

void ProfilerScheduledTaskCheckOut(void)
{
    // Called from FreeRTOS Hook

    // Going from task handle to index would require a lookup.
    // As an optimization, use thread local storage to directly acquire profiler data.
    // NULL task handle will yield this task's storage.
    void * const tlsPointer = pvTaskGetThreadLocalStoragePointer(NULL, THREAD_LOCAL_STORAGE_PROFILER_IDX);

    if (NULL != tlsPointer)
    {
        Profiler_Data_S * const pData = (Profiler_Data_S * const)tlsPointer;
        taskENTER_CRITICAL();
        const uint32_t period = ProfilerSpecificGetTimerUs() - pData->checkInTime;
        ProfilerCollectPeriodStats(pData, period);
        taskEXIT_CRITICAL();
    }
}

void ProfilerCheckIn(const Profiler_E profiler)
{
    Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);

    if (NULL != pData)
    {
        pData->checkInTime = ProfilerSpecificGetTimerUs();
    }
}

void ProfilerCheckOut(const Profiler_E profiler)
{
    Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);

    if (NULL != pData)
    {
        taskENTER_CRITICAL();
        const uint32_t period = ProfilerSpecificGetTimerUs() - pData->checkInTime;
        ProfilerCollectPeriodStats(pData, period);
        taskEXIT_CRITICAL();
    }
}

//--------------------------------------------------------------------------------------------------
// Profiler load checks
//--------------------------------------------------------------------------------------------------
void ProfilerUpdateLoad(void)
{
    // Take a snapshot of CPU counts
    taskENTER_CRITICAL();
    const uint32_t cpuTicksNow = ProfilerSpecificGetTimerUs();
    const uint32_t idleTicksNow = ulTaskGetIdleRunTimeCounter();

    for (size_t i = 0U; i < (size_t)PROFILER_MAX_NUM; ++i)
    {
        const Profiler_E profiler = (Profiler_E)i;

        if (profiler >= PROFILER_SCHEDULED_FIRST)
        {
            TaskHandle_t taskHandle = gProfilerScheduledTaskHandles[PROFILER_SCHEDULED_IDX(profiler)];
            gProfilerLoadEndCounts[i] = ulTaskGetRunTimeCounter(taskHandle);
        }
        else
        {
            Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);
            if (NULL != pData)
            {
                gProfilerLoadEndCounts[i] = pData->runTimeCounts;
            }
        }
    }

    const uint32_t elapsedTicks = cpuTicksNow - gProfilerLoadTicks;
    const uint32_t idleTicks = idleTicksNow - gProfilerLoadIdleTicks;
    gProfilerLoadTicks = cpuTicksNow;
    gProfilerLoadIdleTicks = idleTicksNow;
    taskEXIT_CRITICAL();

    gProfilerTotalLoad = (float)(elapsedTicks - idleTicks) / (float)elapsedTicks;

    for (size_t i = 0U; i < (size_t)PROFILER_MAX_NUM; ++i)
    {
        gProfilerLoad[i] = (float)(gProfilerLoadEndCounts[i] - gProfilerLoadStartCounts[i]) / (float)elapsedTicks;
        gProfilerLoadStartCounts[i] = gProfilerLoadEndCounts[i];
    }
}

//--------------------------------------------------------------------------------------------------
// Getters
//--------------------------------------------------------------------------------------------------
float ProfilerGetTotalLoad(void)
{
    return gProfilerTotalLoad;
}

float ProfilerGetLoad(const Profiler_E profiler)
{
    float val = 0.0F;

    if (profiler < PROFILER_MAX_NUM)
    {
        val = gProfilerLoad[profiler];
    }

    return val;
}

uint32_t ProfilerGetAvgPeriodUs(const Profiler_E profiler)
{
    uint32_t val = 0U;
    Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);

    if (NULL != pData)
    {
        val = pData->latchedAvgPeriod;
    }

    return val;
}

uint32_t ProfilerGetMinPeriodUs(const Profiler_E profiler)
{
    uint32_t val = 0U;
    Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);

    if (NULL != pData)
    {
        val = pData->latchedMinPeriod;
    }

    return val;
}

uint32_t ProfilerGetMaxPeriodUs(const Profiler_E profiler)
{
    uint32_t val = 0U;
    Profiler_Data_S * const pData = ProfilerGetDataPointer(profiler);

    if (NULL != pData)
    {
        val = pData->latchedMaxPeriod;
    }

    return val;
}
