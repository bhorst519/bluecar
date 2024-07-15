#ifndef __BLUECAN_H
#define __BLUECAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "can.h"

void startCAN(void);
void sendCAN_engine_gear(uint8_t gear);

#ifdef __cplusplus
}
#endif

#endif