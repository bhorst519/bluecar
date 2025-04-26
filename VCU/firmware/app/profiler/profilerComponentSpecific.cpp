/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
// #include "halWrappersComponentSpecific.hpp"
#include "profiler.h"

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
extern "C" {

void ProfilerSpecificClearTimerUs(void)
{
    // Vcu::gHalWrappers.TimerClearUs();
}

uint32_t ProfilerSpecificGetTimerUs(void)
{
    // return Vcu::gHalWrappers.TimerGetUs();
    return 0U;
}

} // extern "C"
