#ifndef __KLINE_H
#define __KLINE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "usart.h"
#include "gpio.h"

void sendECUWakeupPulse(void);
void pingECU(void);
void requestECUState(void);

#ifdef __cplusplus
}
#endif

#endif