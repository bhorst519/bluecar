#ifndef CAN_TRANSMITTER_HPP
#define CAN_TRANSMITTER_HPP

#include "qualifiedVal.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

using namespace ::QualifiedVal;

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_EIM_GetTxStorage_VCU_CpuStats(const uint32_t muxIdx);
uint8_t * CANTX_EIM_GetTxStorage_VCU_PcbaVitals(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANTX_EIM_GetMuxFromIdx_VCU_CpuStats(const uint32_t muxIdx);
uint32_t CANTX_EIM_GetMuxFromIdx_VCU_PcbaVitals(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// VCU_100Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_100Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_100Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_100Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_100Hz_AvgPeriod(const float converted);

// VCU_100Hz_Load
void CANTX_EIM_SetSRawFromFrame_VCU_100Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_100Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_100Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_100Hz_Load(const float converted);

// VCU_100Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_100Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_100Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_100Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_100Hz_MaxPeriod(const float converted);

// VCU_100Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_100Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_100Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_100Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_100Hz_MinPeriod(const float converted);

// VCU_10Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_10Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_10Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_10Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_10Hz_AvgPeriod(const float converted);

// VCU_10Hz_Load
void CANTX_EIM_SetSRawFromFrame_VCU_10Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_10Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_10Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_10Hz_Load(const float converted);

// VCU_10Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_10Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_10Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_10Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_10Hz_MaxPeriod(const float converted);

// VCU_10Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_10Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_10Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_10Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_10Hz_MinPeriod(const float converted);

// VCU_1Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1Hz_AvgPeriod(const float converted);

// VCU_1Hz_Load
void CANTX_EIM_SetSRawFromFrame_VCU_1Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1Hz_Load(const float converted);

// VCU_1Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1Hz_MaxPeriod(const float converted);

// VCU_1Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1Hz_MinPeriod(const float converted);

// VCU_1kHz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1kHz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1kHz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1kHz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1kHz_AvgPeriod(const float converted);

// VCU_1kHz_Load
void CANTX_EIM_SetSRawFromFrame_VCU_1kHz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1kHz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1kHz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1kHz_Load(const float converted);

// VCU_1kHz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1kHz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1kHz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1kHz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1kHz_MaxPeriod(const float converted);

// VCU_1kHz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_1kHz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_1kHz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_1kHz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_1kHz_MinPeriod(const float converted);

// VCU_ADC_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_ADC_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_ADC_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_ADC_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_ADC_AvgPeriod(const float converted);

// VCU_ADC_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_ADC_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_ADC_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_ADC_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_ADC_MaxPeriod(const float converted);

// VCU_ADC_MinPeriod
void CANTX_EIM_SetSRawFromFrame_VCU_ADC_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_ADC_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_ADC_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_ADC_MinPeriod(const float converted);

// VCU_CPU_Load
void CANTX_EIM_SetSRawFromFrame_VCU_CPU_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_CPU_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_CPU_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_CPU_Load(const float converted);

// VCU_CpuStatsMux
void CANTX_EIM_SetSRawFromFrame_VCU_CpuStatsMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_VCU_CpuStatsMux(const uint32_t converted, uint8_t * const pData);

// VCU_PCBA_Aps1Pct
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_Aps1Pct(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_Aps1Pct(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_Aps1Pct(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_Aps1Pct(const float_q converted);

// VCU_PCBA_Aps1V
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_Aps1V(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_Aps1V(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_Aps1V(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_Aps1V(const float_q converted);

// VCU_PCBA_Aps2Pct
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_Aps2Pct(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_Aps2Pct(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_Aps2Pct(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_Aps2Pct(const float_q converted);

// VCU_PCBA_Aps2V
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_Aps2V(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_Aps2V(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_Aps2V(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_Aps2V(const float_q converted);

// VCU_PCBA_BrakeSwitch
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_BrakeSwitch(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_BrakeSwitch(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_BrakeSwitch(const uint32_t converted);

// VCU_PCBA_DieTemp
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_DieTemp(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_DieTemp(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_DieTemp(const int32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_DieTemp(const int32_q converted);

// VCU_PCBA_EngEnable
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_EngEnable(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_EngEnable(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_EngEnable(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_EngEnable(const uint32_t converted);

// VCU_PCBA_EngStart
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_EngStart(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_EngStart(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_EngStart(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_EngStart(const uint32_t converted);

// VCU_PCBA_UserSwitch
void CANTX_EIM_SetSRawFromFrame_VCU_PCBA_UserSwitch(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_VCU_PCBA_UserSwitch(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_VCU_PCBA_UserSwitch(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_VCU_PCBA_UserSwitch(const uint32_t converted);

// VCU_PcbaVitalsMux
void CANTX_EIM_SetSRawFromFrame_VCU_PcbaVitalsMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_VCU_PcbaVitalsMux(const uint32_t converted, uint8_t * const pData);

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_EIM_Init(void);

} // namespace CanGen

#endif // CAN_TRANSMITTER_HPP
