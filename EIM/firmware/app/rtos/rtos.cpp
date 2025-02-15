/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
// #include "app.hpp"
#include "cmsis_os.h"
#include "halWrappers.h"
#include "profiler.h"
#include "rtos.h"

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
// static Eim::App m_app {};

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void RtosInit(HalWrappers_Init_S * const pHalWrappersInitArg)
{
    HalWrappersInit(pHalWrappersInitArg);
    // m_app.Init();
}

void RtosRunTask1kHz(void)
{
    uint32_t currentTick = osKernelSysTick();
    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1KHZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        // m_app.RunTask1kHz();

        ProfilerScheduledTaskCheckOut();
    }
}

void RtosRunTask10Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_10HZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        // m_app.RunTask10Hz();

        ProfilerScheduledTaskCheckOut();
    }
}

void RtosRunTask1Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1HZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        // m_app.RunTask1Hz();

        ProfilerUpdateLoad();
        ProfilerScheduledTaskCheckOut();
    }
}
