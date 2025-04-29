/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canTransmitter.hpp"
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
namespace Vcu
{

using namespace CanGen;

void TxNoneModule::Transmit(void)
{
    // Nothing to do
}

void Tx100HzModule::Transmit(void)
{
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_PCBA_DieTemp(m_adcRef.GetAdcFilt10Hz(ANALOG_DIE_TEMP).Convert(int32_t()));
    CANTX_EIM_SetS_VCU_PCBA_Aps1V(m_adcRef.GetAdcFilt10Hz(ANALOG_APS_1));
    CANTX_EIM_SetS_VCU_PCBA_Aps2V(m_adcRef.GetAdcFilt10Hz(ANALOG_APS_2));
    taskEXIT_CRITICAL();

    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_PCBA_EngEnable(static_cast<uint32_t>(m_ioIntRef.GetEngineEnable()));
    CANTX_EIM_SetS_VCU_PCBA_EngStart(static_cast<uint32_t>(m_ioIntRef.GetEngineStart()));
    CANTX_EIM_SetS_VCU_PCBA_BrakeSwitch(static_cast<uint32_t>(m_ioIntRef.GetBrakeSwitch()));
    CANTX_EIM_SetS_VCU_PCBA_UserSwitch(static_cast<uint32_t>(m_ioIntRef.GetUserSwitch()));
    taskEXIT_CRITICAL();

    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_PCBA_Aps1Pct(m_apsRef.GetAps1Frac() * 100.0F);
    CANTX_EIM_SetS_VCU_PCBA_Aps2Pct(m_apsRef.GetAps2Frac() * 100.0F);
    taskEXIT_CRITICAL();
}

void Tx1HzModule::Transmit(void)
{
    // CPU load
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_CPU_Load(ProfilerGetTotalLoad() * 100.0F);
    CANTX_EIM_SetS_VCU_1kHz_Load(ProfilerGetLoad(PROFILER_TASK_1KHZ) * 100.0F);
    CANTX_EIM_SetS_VCU_100Hz_Load(ProfilerGetLoad(PROFILER_TASK_100HZ) * 100.0F);
    CANTX_EIM_SetS_VCU_10Hz_Load(ProfilerGetLoad(PROFILER_TASK_10HZ) * 100.0F);
    CANTX_EIM_SetS_VCU_1Hz_Load(ProfilerGetLoad(PROFILER_TASK_1HZ) * 100.0F);
    taskEXIT_CRITICAL();

    // 1kHz task data
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_1kHz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_1KHZ));
    CANTX_EIM_SetS_VCU_1kHz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_1KHZ));
    CANTX_EIM_SetS_VCU_1kHz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_1KHZ));
    taskEXIT_CRITICAL();

    // 100Hz task data
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_100Hz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_100HZ));
    CANTX_EIM_SetS_VCU_100Hz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_100HZ));
    CANTX_EIM_SetS_VCU_100Hz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_100HZ));
    taskEXIT_CRITICAL();

    // 10Hz task data
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_10Hz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_10HZ));
    CANTX_EIM_SetS_VCU_10Hz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_10HZ));
    CANTX_EIM_SetS_VCU_10Hz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_10HZ));
    taskEXIT_CRITICAL();

    // 1Hz task data
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_1Hz_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_TASK_1HZ));
    CANTX_EIM_SetS_VCU_1Hz_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_TASK_1HZ));
    CANTX_EIM_SetS_VCU_1Hz_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_TASK_1HZ));
    taskEXIT_CRITICAL();

    // ADC conversion data
    taskENTER_CRITICAL();
    CANTX_EIM_SetS_VCU_ADC_AvgPeriod(ProfilerGetAvgPeriodMs(PROFILER_ADC_CONV));
    CANTX_EIM_SetS_VCU_ADC_MinPeriod(ProfilerGetMinPeriodMs(PROFILER_ADC_CONV));
    CANTX_EIM_SetS_VCU_ADC_MaxPeriod(ProfilerGetMaxPeriodMs(PROFILER_ADC_CONV));
    taskEXIT_CRITICAL();
}

} // namespace Vcu
