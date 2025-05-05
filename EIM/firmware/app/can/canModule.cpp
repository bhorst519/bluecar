/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "canModule.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "PT_canReceiver.hpp"
#include "PT_canTransmitter.hpp"
#include "PT_messageInfo.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

UTIL_ASSERT(CANRX_PT_NUM_MESSAGES <= Shared::HAL_WRAPPERS_FILTERS_PER_BUS,
    "CAN bus with too many messages for filter config");

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
using namespace CanGen;

void CanModule::Init(void)
{
    // Driver and HAL initialization
    CANTX_PT_Init();

    for (uint32_t i = 0U; i < CANRX_PT_NUM_MESSAGES; ++i)
    {
        const uint32_t mid = CANRX_PT_GetMidFromIdx(i);
        gHalWrappers.CanRegisterRxFilter(CAN_1, mid);
    }
    gHalWrappers.CanSetRxFilters(CAN_1);
    gHalWrappers.CanStart(CAN_1);
}

void CanModule::Run(void)
{
    CANTX_PT_Run1ms();
}

} // namespace Eim
