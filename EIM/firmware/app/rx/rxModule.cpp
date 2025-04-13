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

void Rx100HzModule::Receive(void)
{
    m_outputData.brakeLightEn = CANRX_EIM_GetS_TESTER_BrakeLightEnable().Convert(uint8_t());
    m_outputData.headlightEn = CANRX_EIM_GetS_TESTER_HeadlightEnable().Convert(uint8_t());
    m_outputData.highBeamEn = CANRX_EIM_GetS_TESTER_HighBeamEnable().Convert(uint8_t());
    m_outputData.hornEn = CANRX_EIM_GetS_TESTER_HornEnable().Convert(uint8_t());
    m_outputData.mainRelayEn = CANRX_EIM_GetS_TESTER_MainRelayEnable().Convert(uint8_t());
    m_outputData.turnRightEn = CANRX_EIM_GetS_TESTER_TurnRightEnable().Convert(uint8_t());
    m_outputData.turnLeftEn = CANRX_EIM_GetS_TESTER_TurnLeftEnable().Convert(uint8_t());
}

void Rx10HzModule::Receive(void)
{
    m_outputData.servoPositionRequest = CANRX_EIM_GetS_TESTER_Servo_Position();
}

} // namespace Eim
