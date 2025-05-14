/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "canModule.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "DEV_canReceiver.hpp"
#include "DEV_canTransmitter.hpp"
#include "DEV_messageInfo.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

UTIL_ASSERT(CANRX_DEV_NUM_MESSAGES <= Shared::HAL_WRAPPERS_FILTERS_PER_BUS,
    "CAN bus with too many messages for filter config");

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
using namespace CanGen;

void CanModule::Init(void)
{
    // Driver and HAL initialization
    (void)CANTX_DEV_Init();
    (void)CANRX_DEV_Init();

    for (uint32_t i = 0U; i < CANRX_DEV_NUM_MESSAGES; ++i)
    {
        const uint32_t mid = CANRX_DEV_GetMidFromIdx(i);
        gHalWrappers.CanRegisterRxFilter(CAN_1, mid);
    }
    gHalWrappers.CanSetRxFilters(CAN_1);
    gHalWrappers.CanStart(CAN_1);
}

void CanModule::Run(void)
{
    CANRX_DEV_Run1ms();
    CANTX_DEV_Run1ms();
}

} // namespace Eim
