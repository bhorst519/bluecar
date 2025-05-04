/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "PT_canReceiver.hpp"
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
    // m_outputData.brakeLightEn = CANRX_PT_GetS_TESTER_BrakeLightEnable().Convert(uint8_t());
    m_outputData.headlightEn = CANRX_PT_GetS_TESTER_HeadlightEnable().Convert(uint8_t());
    m_outputData.highBeamEn = CANRX_PT_GetS_TESTER_HighBeamEnable().Convert(uint8_t());
    m_outputData.hornEn = CANRX_PT_GetS_TESTER_HornEnable().Convert(uint8_t());
    // m_outputData.mainRelayEn = CANRX_PT_GetS_TESTER_MainRelayEnable().Convert(uint8_t());
    m_outputData.turnRightEn = CANRX_PT_GetS_TESTER_TurnRightEnable().Convert(uint8_t());
    m_outputData.turnLeftEn = CANRX_PT_GetS_TESTER_TurnLeftEnable().Convert(uint8_t());

    m_outputData.mainRelayEn = uint8_q(1U, SignalStatus_E::VALID);
    m_outputData.engineOnEn = CANRX_PT_GetS_VCU_PCBA_EngEnable().Convert(uint8_t());
    m_outputData.engineStartEn = CANRX_PT_GetS_VCU_PCBA_EngStart().Convert(uint8_t());
    m_outputData.brakeLightEn = CANRX_PT_GetS_VCU_PCBA_BrakeSwitch().Convert(uint8_t());
}

void Rx10HzModule::Receive(void)
{
    m_outputData.apsFrac = CANRX_PT_GetS_VCU_PCBA_Aps1Pct() * 0.01F;
    m_outputData.servoPositionRequest = CANRX_PT_GetS_TESTER_Servo_Position();
}

} // namespace Eim
