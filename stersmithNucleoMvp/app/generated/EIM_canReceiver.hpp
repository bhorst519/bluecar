#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include "EIM_canReceiverHook.h"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_EIM_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
} // namespace CanGen

#endif // CAN_RECEIVER_HPP