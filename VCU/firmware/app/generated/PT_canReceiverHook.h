#ifndef CAN_RECEIVER_HOOK_H
#define CAN_RECEIVER_HOOK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"

bool CANRX_PT_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData);

#ifdef __cplusplus
}
#endif

#endif // CAN_RECEIVER_HOOK_H
