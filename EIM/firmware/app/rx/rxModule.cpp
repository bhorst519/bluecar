/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canReceiver.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "rxModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

using namespace CanGen;

void RxNoneModule::Receive(void)
{
    // Nothing to do
}

void Rx10HzModule::Receive(void)
{
    m_outputData.servoPositionRequest = CANRX_EIM_GetS_TESTER_Servo_Position();

    const uint32_t relayEn = CANRX_EIM_GetS_TESTER_Relay_Enable();
    gHalWrappers.GpioSet(GPIO_MAIN_RELAY_EN, static_cast<bool>(relayEn));
}

} // namespace Eim
