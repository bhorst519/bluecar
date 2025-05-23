/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "DEV_canTransmitter.hpp"
#include "profiler.h"
#include "txModule.hpp"

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
namespace
{

inline float ProfilerGetAvgPeriodMs(const Profiler_E profiler)
{
    return static_cast<float>(ProfilerGetAvgPeriodUs(profiler)) * 0.001F;
}

inline float ProfilerGetMinPeriodMs(const Profiler_E profiler)
{
    return static_cast<float>(ProfilerGetMinPeriodUs(profiler)) * 0.001F;
}

inline float ProfilerGetMaxPeriodMs(const Profiler_E profiler)
{
    return static_cast<float>(ProfilerGetMaxPeriodUs(profiler)) * 0.001F;
}

} // namespace (anonymous)

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
    CANTX_DEV_SetS_EIM_Servo_Current(m_servoRef.GetCurrent());
    CANTX_DEV_SetS_EIM_Servo_Id(m_servoRef.GetId());
    CANTX_DEV_SetS_EIM_Servo_LossOfCommPosition(m_servoRef.GetLossOfCommPositionDegrees());
    CANTX_DEV_SetS_EIM_Servo_LossOfCommTimeout(m_servoRef.GetLossOfCommTimeout().Convert(uint32_t()));
    CANTX_DEV_SetS_EIM_Servo_Position(m_servoRef.GetPositionDegrees());
    CANTX_DEV_SetS_EIM_Servo_Temp(m_servoRef.GetTemperature().Convert(int32_t()));
    CANTX_DEV_SetS_EIM_Servo_Voltage(m_servoRef.GetVoltage());
    taskEXIT_CRITICAL();
}

void Tx1HzModule::Transmit(void)
{
    // CPU load
    taskENTER_CRITICAL();
    CANTX_DEV_SetS_EIM_CPU_Load(ProfilerGetTotalLoad() * 100.0F);
    CANTX_DEV_SetS_EIM_1kHz_Load(ProfilerGetLoad(PROFILER_TASK_1KHZ) * 100.0F);
    CANTX_DEV_SetS_EIM_10Hz_Load(ProfilerGetLoad(PROFILER_TASK_10HZ) * 100.0F);
    CANTX_DEV_SetS_EIM_1Hz_Load(ProfilerGetLoad(PROFILER_TASK_1HZ) * 100.0F);
    taskEXIT_CRITICAL();

    // 1kHz task data
    taskENTER_CRITICAL();
    CANTX_DEV_SetS_EIM_1kHz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_1KHZ));
    CANTX_DEV_SetS_EIM_1kHz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_1KHZ));
    CANTX_DEV_SetS_EIM_1kHz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_1KHZ));
    taskEXIT_CRITICAL();

    // 10Hz task data
    taskENTER_CRITICAL();
    CANTX_DEV_SetS_EIM_10Hz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_10HZ));
    CANTX_DEV_SetS_EIM_10Hz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_10HZ));
    CANTX_DEV_SetS_EIM_10Hz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_10HZ));
    taskEXIT_CRITICAL();

    // 1Hz task data
    taskENTER_CRITICAL();
    CANTX_DEV_SetS_EIM_1Hz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_1HZ));
    CANTX_DEV_SetS_EIM_1Hz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_1HZ));
    CANTX_DEV_SetS_EIM_1Hz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_1HZ));
    taskEXIT_CRITICAL();

    // K-line data
    taskENTER_CRITICAL();
    CANTX_DEV_SetS_EIM_ECM_BatteryVoltage(m_klineRef.GetBatteryVoltage());
    CANTX_DEV_SetS_EIM_ECM_EctTemp(m_klineRef.GetEctTemp().Convert(int32_t()));
    CANTX_DEV_SetS_EIM_ECM_EctVoltage(m_klineRef.GetEctVoltage());
    CANTX_DEV_SetS_EIM_ECM_IatTemp(m_klineRef.GetIatTemp().Convert(int32_t()));
    CANTX_DEV_SetS_EIM_ECM_IatVoltage(m_klineRef.GetIatVoltage());
    CANTX_DEV_SetS_EIM_ECM_MapPressure(m_klineRef.GetMapPressure().Convert(uint32_t()));
    CANTX_DEV_SetS_EIM_ECM_MapVoltage(m_klineRef.GetMapVoltage());
    CANTX_DEV_SetS_EIM_ECM_Rpm(m_klineRef.GetRpm().Convert(uint32_t()));
    CANTX_DEV_SetS_EIM_ECM_TpsAngle(m_klineRef.GetTpsAngle());
    CANTX_DEV_SetS_EIM_ECM_TpsVoltage(m_klineRef.GetTpsVoltage());
    CANTX_DEV_SetS_EIM_ECM_VehicleSpeed(m_klineRef.GetVehicleSpeed().Convert(uint32_t()));
    taskEXIT_CRITICAL();
}

} // namespace Eim
