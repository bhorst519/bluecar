#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include "PT_canReceiverHook.h"
#include "qualifiedVal.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

using namespace ::QualifiedVal;

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_PT_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_BrakeLightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_BrakeLightEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_BrakeLightEnable(void);

// TESTER_HeadlightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_HeadlightEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_HeadlightEnable(void);

// TESTER_HighBeamEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_HighBeamEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_HighBeamEnable(void);

// TESTER_HornEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HornEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_HornEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_HornEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_HornEnable(void);

// TESTER_MainRelayEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_MainRelayEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_MainRelayEnable(void);

// TESTER_Servo_Position
uint16_t CANRX_PT_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
uint16_t CANRX_PT_GetSRaw_TESTER_Servo_Position(void);
float_q CANRX_PT_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
float_q CANRX_PT_GetS_TESTER_Servo_Position(void);

// TESTER_TurnLeftEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_TurnLeftEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_TurnLeftEnable(void);

// TESTER_TurnRightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_TESTER_TurnRightEnable(void);
uint32_q CANRX_PT_GetSFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_TESTER_TurnRightEnable(void);

// VCU_PCBA_Aps1Pct
uint16_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_Aps1Pct(const uint8_t * const pData);
uint16_t CANRX_PT_GetSRaw_VCU_PCBA_Aps1Pct(void);
float_q CANRX_PT_GetSFromFrame_VCU_PCBA_Aps1Pct(const uint8_t * const pData);
float_q CANRX_PT_GetS_VCU_PCBA_Aps1Pct(void);

// VCU_PCBA_BrakeSwitch
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_BrakeSwitch(void);
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_VCU_PCBA_BrakeSwitch(void);

// VCU_PCBA_EngEnable
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngEnable(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_EngEnable(void);
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_EngEnable(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_VCU_PCBA_EngEnable(void);

// VCU_PCBA_EngStart
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngStart(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_EngStart(void);
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_EngStart(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_VCU_PCBA_EngStart(void);

// VCU_PcbaVitalsMux
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PcbaVitalsMux(const uint8_t * const pData);
uint8_t CANRX_PT_GetSRaw_VCU_PcbaVitalsMux(void);
uint32_q CANRX_PT_GetSFromFrame_VCU_PcbaVitalsMux(const uint8_t * const pData);
uint32_q CANRX_PT_GetS_VCU_PcbaVitalsMux(void);

//--------------------------------------------------------------------------------------------------
// Message receive init and run
//--------------------------------------------------------------------------------------------------
bool CANRX_PT_Init(void);
void CANRX_PT_Run1ms(void);

} // namespace CanGen

#endif // CAN_RECEIVER_HPP
