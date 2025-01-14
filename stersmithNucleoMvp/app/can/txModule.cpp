/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canTransmitter.hpp"
#include "txModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

using namespace CanGen;

void TxNoneModule::Transmit(void)
{
    // Nothing to do
}

void Tx10HzModule::Transmit(void)
{
    taskENTER_CRITICAL();

    CANTX_EIM_SetS_EIM_Servo_Current(m_servoRef.GetCurrent());
    CANTX_EIM_SetS_EIM_Servo_Id(m_servoRef.GetId());
    CANTX_EIM_SetS_EIM_Servo_LossOfCommPosition(m_servoRef.GetLossOfCommPositionDegrees());
    CANTX_EIM_SetS_EIM_Servo_LossOfCommTimeout(m_servoRef.GetLossOfCommTimeout().Convert(uint32_t()));
    CANTX_EIM_SetS_EIM_Servo_Position(m_servoRef.GetPositionDegrees());
    CANTX_EIM_SetS_EIM_Servo_Temp(m_servoRef.GetTemperature().Convert(int32_t()));
    CANTX_EIM_SetS_EIM_Servo_Voltage(m_servoRef.GetVoltage());

    taskEXIT_CRITICAL();
}

void Tx1HzModule::Transmit(void)
{
    taskENTER_CRITICAL();

    CANTX_EIM_SetS_EIM_ECM_BatteryVoltage(m_klineRef.GetBatteryVoltage());
    CANTX_EIM_SetS_EIM_ECM_EctTemp(m_klineRef.GetEctTemp().Convert(int32_t()));
    CANTX_EIM_SetS_EIM_ECM_EctVoltage(m_klineRef.GetEctVoltage());
    CANTX_EIM_SetS_EIM_ECM_IatTemp(m_klineRef.GetIatTemp().Convert(int32_t()));
    CANTX_EIM_SetS_EIM_ECM_IatVoltage(m_klineRef.GetIatVoltage());
    CANTX_EIM_SetS_EIM_ECM_MapPressure(m_klineRef.GetMapPressure().Convert(uint32_t()));
    CANTX_EIM_SetS_EIM_ECM_MapVoltage(m_klineRef.GetMapVoltage());
    CANTX_EIM_SetS_EIM_ECM_Rpm(m_klineRef.GetRpm().Convert(uint32_t()));
    CANTX_EIM_SetS_EIM_ECM_TpsAngle(m_klineRef.GetTpsAngle());
    CANTX_EIM_SetS_EIM_ECM_TpsVoltage(m_klineRef.GetTpsVoltage());
    CANTX_EIM_SetS_EIM_ECM_VehicleSpeed(m_klineRef.GetVehicleSpeed().Convert(uint32_t()));

    taskEXIT_CRITICAL();
}

} // namespace Eim
