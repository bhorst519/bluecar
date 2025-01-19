#ifndef PROFILER_H
#define PROFILER_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "profilerComponentSpecific.h"
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef struct
{
    // Configuration data - shouldn't touch after init
    uint32_t configWindowNumPeriods;

    // Run time data
    uint32_t checkInTime;
    uint32_t numPeriods;
    uint32_t sumPeriods;
    uint32_t minPeriod;
    uint32_t maxPeriod;
    uint32_t runTimeCounts;

    // Latched run time window data
    uint32_t latchedAvgPeriod;
    uint32_t latchedMinPeriod;
    uint32_t latchedMaxPeriod;
} Profiler_Data_S;

/***************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                      *
***************************************************************************************************/
void ProfilerScheduledTaskRegister(const Profiler_E profiler, void * taskHandle);

// Profiler period checks
void ProfilerScheduledTaskCheckIn(void);
void ProfilerScheduledTaskCheckOut(void);
void ProfilerCheckIn(const Profiler_E profiler);
void ProfilerCheckOut(const Profiler_E profiler);

// Profiler load checks
void ProfilerUpdateLoad(void);

// Getters
float ProfilerGetTotalLoad(void);
float ProfilerGetLoad(const Profiler_E profiler);
uint32_t ProfilerGetAvgPeriodUs(const Profiler_E profiler);
uint32_t ProfilerGetMinPeriodUs(const Profiler_E profiler);
uint32_t ProfilerGetMaxPeriodUs(const Profiler_E profiler);

#ifdef __cplusplus
}
#endif

#endif // PROFILER_H
