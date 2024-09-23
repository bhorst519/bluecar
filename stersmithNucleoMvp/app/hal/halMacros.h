#ifndef HAL_MACROS_H
#define HAL_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "stm32f4xx_hal.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define LED_1_PERIPH (GPIOB)
#define LED_1_PIN (GPIO_PIN_0)

#define LED_2_PERIPH (GPIOB)
#define LED_2_PIN (GPIO_PIN_7)

#define SERIAL_UART (USART3)

#define PWM_CHANNEL (TIM_CHANNEL_1)

#ifdef __cplusplus
}
#endif

#endif // HAL_MACROS_H
