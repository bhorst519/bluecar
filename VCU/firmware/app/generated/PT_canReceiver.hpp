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
//--------------------------------------------------------------------------------------------------
// Message receive init and run
//--------------------------------------------------------------------------------------------------
bool CANRX_PT_Init(void);
void CANRX_PT_Run1ms(void);

} // namespace CanGen

#endif // CAN_RECEIVER_HPP
