/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.hpp"
#include "profiler.h"

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
extern "C" {

void ProfilerSpecificClearTimerUs(void)
{
    Eim::HalWrappersClearTimerUs();
}

uint32_t ProfilerSpecificGetTimerUs(void)
{
    return Eim::HalWrappersGetTimerUs();
}

} // extern "C"
