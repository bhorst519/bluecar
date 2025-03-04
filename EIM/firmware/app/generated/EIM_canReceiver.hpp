#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include "EIM_canReceiverHook.h"
#include "qualifiedVal.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

using namespace ::QualifiedVal;

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_EIM_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_Relay_Enable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_Relay_Enable(const uint8_t * const pData);
uint8_t CANRX_EIM_GetSRaw_TESTER_Relay_Enable(void);
uint32_t CANRX_EIM_GetSFromFrame_TESTER_Relay_Enable(const uint8_t * const pData);
uint32_t CANRX_EIM_GetS_TESTER_Relay_Enable(void);

// TESTER_Servo_Position
uint16_t CANRX_EIM_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
uint16_t CANRX_EIM_GetSRaw_TESTER_Servo_Position(void);
float_q CANRX_EIM_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
float_q CANRX_EIM_GetS_TESTER_Servo_Position(void);

} // namespace CanGen

#endif // CAN_RECEIVER_HPP
