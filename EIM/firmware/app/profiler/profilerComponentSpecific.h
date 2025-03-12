#ifndef PROFILER_COMPONENT_SPECIFIC_H
#define PROFILER_COMPONENT_SPECIFIC_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef enum
{
    // Non-scheduled profilers
    PROFILER_CAN_TX_ISR,
    PROFILER_CAN_RX_ISR,
    PROFILER_NON_SCHEDULED_MAX_NUM,

    // Scheduled tasks
    PROFILER_SCHEDULED_FIRST = PROFILER_NON_SCHEDULED_MAX_NUM,
    PROFILER_TASK_1KHZ = PROFILER_SCHEDULED_FIRST,
    PROFILER_TASK_10HZ,
    PROFILER_TASK_1HZ,

    PROFILER_MAX_NUM
} Profiler_E;
#define PROFILER_SCHEDULED_IDX(p)       (p - PROFILER_SCHEDULED_FIRST)
#define PROFILER_SCHEDULED_MAX_NUM      PROFILER_SCHEDULED_IDX(PROFILER_MAX_NUM)

UTIL_ASSERT((size_t)PROFILER_NON_SCHEDULED_MAX_NUM == 2U,   "Number of profilers incorrectly deduced");
UTIL_ASSERT((size_t)PROFILER_SCHEDULED_MAX_NUM == 3U,       "Number of profilers incorrectly deduced");
UTIL_ASSERT((size_t)PROFILER_MAX_NUM == 5U,                 "Number of profilers incorrectly deduced");

#ifdef __cplusplus
}
#endif

#endif // PROFILER_COMPONENT_SPECIFIC_H
