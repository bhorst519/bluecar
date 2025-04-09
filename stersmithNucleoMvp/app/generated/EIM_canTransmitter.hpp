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
uint8_t * CANTX_EIM_GetTxStorage_EIM_PcbaVitals(const uint32_t muxIdx);
uint8_t * CANTX_EIM_GetTxStorage_EIM_CpuStats(const uint32_t muxIdx);
uint8_t * CANTX_EIM_GetTxStorage_EIM_ServoStatus(const uint32_t muxIdx);
uint8_t * CANTX_EIM_GetTxStorage_EIM_EngineStatus(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_PcbaVitals(const uint32_t muxIdx);
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_CpuStats(const uint32_t muxIdx);
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_ServoStatus(const uint32_t muxIdx);
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_EngineStatus(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// EIM_PcbaVitalsMux
void CANTX_EIM_SetSRawFromFrame_EIM_PcbaVitalsMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_EIM_PcbaVitalsMux(const uint32_t converted, uint8_t * const pData);

// EIM_PCBA_GearSelect
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_GearSelect(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_GearSelect(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_GearSelect(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_GearSelect(const uint32_t converted);

// EIM_PCBA_GearN
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_GearN(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_GearN(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_GearN(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_GearN(const uint32_t converted);

// EIM_PCBA_Gear1
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear1(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear1(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear1(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear1(const uint32_t converted);

// EIM_PCBA_Gear2
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear2(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear2(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear2(const uint32_t converted);

// EIM_PCBA_Gear3
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear3(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear3(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear3(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear3(const uint32_t converted);

// EIM_PCBA_Gear4
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear4(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear4(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear4(const uint32_t converted);

// EIM_PCBA_Gear5
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear5(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear5(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear5(const uint32_t converted);

// EIM_PCBA_Gear6
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Gear6(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Gear6(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Gear6(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Gear6(const uint32_t converted);

// EIM_PCBA_FuelLevelV
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_FuelLevelV(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_FuelLevelV(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_FuelLevelV(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_FuelLevelV(const float_q converted);

// EIM_PCBA_FuelLowV
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_FuelLowV(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_FuelLowV(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_FuelLowV(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_FuelLowV(const float_q converted);

// EIM_PCBA_DieTemp
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_DieTemp(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_DieTemp(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_DieTemp(const int32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_DieTemp(const int32_q converted);

// EIM_PCBA_12V
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_12V(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_12V(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_12V(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_12V(const float_q converted);

// EIM_PCBA_Servo12V
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Servo12V(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Servo12V(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Servo12V(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Servo12V(const float_q converted);

// EIM_PCBA_Eng12V
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_Eng12V(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_Eng12V(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_Eng12V(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_Eng12V(const float_q converted);

// EIM_PCBA_EngTempV
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_EngTempV(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_EngTempV(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_EngTempV(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_EngTempV(const float_q converted);

// EIM_PCBA_EngOnCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_EngOnCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_EngOnCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_EngOnCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_EngOnCurrent(const float_q converted);

// EIM_PCBA_EngStartCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_EngStartCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_EngStartCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_EngStartCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_EngStartCurrent(const float_q converted);

// EIM_PCBA_BrakeLightCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_BrakeLightCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_BrakeLightCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_BrakeLightCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_BrakeLightCurrent(const float_q converted);

// EIM_PCBA_TurnRCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_TurnRCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_TurnRCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_TurnRCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_TurnRCurrent(const float_q converted);

// EIM_PCBA_TurnLCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_TurnLCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_TurnLCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_TurnLCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_TurnLCurrent(const float_q converted);

// EIM_PCBA_HighBeamCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_HighBeamCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_HighBeamCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_HighBeamCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_HighBeamCurrent(const float_q converted);

// EIM_PCBA_HornCurrent
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_HornCurrent(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_PCBA_HornCurrent(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_PCBA_HornCurrent(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_PCBA_HornCurrent(const float_q converted);

// EIM_CpuStatsMux
void CANTX_EIM_SetSRawFromFrame_EIM_CpuStatsMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(const uint32_t converted, uint8_t * const pData);

// EIM_CPU_Load
void CANTX_EIM_SetSRawFromFrame_EIM_CPU_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_CPU_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_CPU_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_CPU_Load(const float converted);

// EIM_1kHz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1kHz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1kHz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1kHz_Load(const float converted);

// EIM_100Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_100Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_100Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_100Hz_Load(const float converted);

// EIM_10Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_10Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_10Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_10Hz_Load(const float converted);

// EIM_1Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_Load(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1Hz_Load(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1Hz_Load(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1Hz_Load(const float converted);

// EIM_1kHz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1kHz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1kHz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1kHz_AvgPeriod(const float converted);

// EIM_1kHz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1kHz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1kHz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1kHz_MinPeriod(const float converted);

// EIM_1kHz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1kHz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1kHz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1kHz_MaxPeriod(const float converted);

// EIM_100Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_100Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_100Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_100Hz_AvgPeriod(const float converted);

// EIM_100Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_100Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_100Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_100Hz_MinPeriod(const float converted);

// EIM_100Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_100Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_100Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_100Hz_MaxPeriod(const float converted);

// EIM_10Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_10Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_10Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_10Hz_AvgPeriod(const float converted);

// EIM_10Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_10Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_10Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_10Hz_MinPeriod(const float converted);

// EIM_10Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_10Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_10Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_10Hz_MaxPeriod(const float converted);

// EIM_1Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1Hz_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1Hz_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1Hz_AvgPeriod(const float converted);

// EIM_1Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1Hz_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1Hz_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1Hz_MaxPeriod(const float converted);

// EIM_1Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_1Hz_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_1Hz_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_1Hz_MinPeriod(const float converted);

// EIM_ADC_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_AvgPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ADC_AvgPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ADC_AvgPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ADC_AvgPeriod(const float converted);

// EIM_ADC_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_MaxPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ADC_MaxPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ADC_MaxPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ADC_MaxPeriod(const float converted);

// EIM_ADC_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_MinPeriod(const uint32_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ADC_MinPeriod(const uint32_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ADC_MinPeriod(const float converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ADC_MinPeriod(const float converted);

// EIM_ServoStatusMux
void CANTX_EIM_SetSRawFromFrame_EIM_ServoStatusMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_EIM_ServoStatusMux(const uint32_t converted, uint8_t * const pData);

// EIM_Servo_Id
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Id(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_Id(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_Id(const uint32_t converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_Id(const uint32_t converted);

// EIM_Servo_Position
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Position(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_Position(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_Position(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_Position(const float_q converted);

// EIM_Servo_LossOfCommPosition
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_LossOfCommPosition(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommPosition(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_LossOfCommPosition(const float_q converted);

// EIM_Servo_LossOfCommTimeout
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommTimeout(const uint32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_LossOfCommTimeout(const uint32_q converted);

// EIM_Servo_Current
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Current(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_Current(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_Current(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_Current(const float_q converted);

// EIM_Servo_Temp
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Temp(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_Temp(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_Temp(const int32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_Temp(const int32_q converted);

// EIM_Servo_Voltage
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Voltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_Servo_Voltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_Servo_Voltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_Servo_Voltage(const float_q converted);

// EIM_EngineStatusMux
void CANTX_EIM_SetSRawFromFrame_EIM_EngineStatusMux(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSFromFrame_EIM_EngineStatusMux(const uint32_t converted, uint8_t * const pData);

// EIM_ECM_Rpm
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_Rpm(const uint16_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_Rpm(const uint16_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_Rpm(const uint32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_Rpm(const uint32_q converted);

// EIM_ECM_VehicleSpeed
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_VehicleSpeed(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_VehicleSpeed(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_VehicleSpeed(const uint32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_VehicleSpeed(const uint32_q converted);

// EIM_ECM_BatteryVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_BatteryVoltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_BatteryVoltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_BatteryVoltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_BatteryVoltage(const float_q converted);

// EIM_ECM_EctVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctVoltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_EctVoltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctVoltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_EctVoltage(const float_q converted);

// EIM_ECM_EctTemp
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctTemp(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_EctTemp(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctTemp(const int32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_EctTemp(const int32_q converted);

// EIM_ECM_IatVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatVoltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_IatVoltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatVoltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_IatVoltage(const float_q converted);

// EIM_ECM_IatTemp
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatTemp(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_IatTemp(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatTemp(const int32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_IatTemp(const int32_q converted);

// EIM_ECM_MapVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapVoltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_MapVoltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapVoltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_MapVoltage(const float_q converted);

// EIM_ECM_MapPressure
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapPressure(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_MapPressure(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapPressure(const uint32_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_MapPressure(const uint32_q converted);

// EIM_ECM_TpsVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsVoltage(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_TpsVoltage(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsVoltage(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_TpsVoltage(const float_q converted);

// EIM_ECM_TpsAngle
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsAngle(const uint8_t rawVal, uint8_t * const pData);
void CANTX_EIM_SetSRaw_EIM_ECM_TpsAngle(const uint8_t rawVal);
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsAngle(const float_q converted, uint8_t * const pData);
void CANTX_EIM_SetS_EIM_ECM_TpsAngle(const float_q converted);

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_EIM_Init(void);

} // namespace CanGen

#endif // CAN_TRANSMITTER_HPP
