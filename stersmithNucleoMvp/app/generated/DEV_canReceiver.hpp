#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include "DEV_canReceiverHook.h"
#include "qualifiedVal.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

using namespace ::QualifiedVal;

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_DEV_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_Servo_Position
uint16_t CANRX_DEV_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
uint16_t CANRX_DEV_GetSRaw_TESTER_Servo_Position(void);
float_q CANRX_DEV_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData);
float_q CANRX_DEV_GetS_TESTER_Servo_Position(void);

} // namespace CanGen

#endif // CAN_RECEIVER_HPP
