/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canTransmitter.h"
#include "txModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

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
    CANTX_EIM_SetS_EIM_Servo_LossOfCommTimeout(static_cast<uint32_t>(m_servoRef.GetLossOfCommTimeout()));
    CANTX_EIM_SetS_EIM_Servo_Position(m_servoRef.GetPositionDegrees());
    CANTX_EIM_SetS_EIM_Servo_Temp(static_cast<int32_t>(m_servoRef.GetTemperature()));
    CANTX_EIM_SetS_EIM_Servo_Voltage(m_servoRef.GetVoltage());

    taskEXIT_CRITICAL();
}

void Tx1HzModule::Transmit(void)
{
    taskENTER_CRITICAL();

    CANTX_EIM_SetS_EIM_ECM_BatteryVoltage(m_klineRef.GetBatteryVoltage());
    CANTX_EIM_SetS_EIM_ECM_EctTemp(static_cast<int32_t>(m_klineRef.GetEctTemp()));
    CANTX_EIM_SetS_EIM_ECM_EctVoltage(m_klineRef.GetEctVoltage());
    CANTX_EIM_SetS_EIM_ECM_IatTemp(static_cast<int32_t>(m_klineRef.GetIatTemp()));
    CANTX_EIM_SetS_EIM_ECM_IatVoltage(m_klineRef.GetIatVoltage());
    CANTX_EIM_SetS_EIM_ECM_MapPressure(static_cast<uint32_t>(m_klineRef.GetMapPressure()));
    CANTX_EIM_SetS_EIM_ECM_MapVoltage(m_klineRef.GetMapVoltage());
    CANTX_EIM_SetS_EIM_ECM_Rpm(m_klineRef.GetRpm());
    CANTX_EIM_SetS_EIM_ECM_TpsAngle(m_klineRef.GetTpsAngle());
    CANTX_EIM_SetS_EIM_ECM_TpsVoltage(m_klineRef.GetTpsVoltage());
    CANTX_EIM_SetS_EIM_ECM_VehicleSpeed(static_cast<uint32_t>(m_klineRef.GetVehicleSpeed()));

    taskEXIT_CRITICAL();
}

} // namespace Eim
