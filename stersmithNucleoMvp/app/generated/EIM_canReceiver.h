#ifndef CAN_RECEIVER_H
#define CAN_RECEIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_EIM_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
bool CANRX_EIM_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData);

#ifdef __cplusplus
}
#endif

#endif // CAN_RECEIVER_H
