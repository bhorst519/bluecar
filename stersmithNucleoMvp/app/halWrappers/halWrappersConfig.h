#ifndef HAL_WRAPPERS_CONFIG_H
#define HAL_WRAPPERS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "stm32f4xx_hal.h"
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define FEATURE_HAL_WRAPPERS_GPIO   (1)
#define FEATURE_HAL_WRAPPERS_PWM    (1)
#define FEATURE_HAL_WRAPPERS_CAN    (1)
#define FEATURE_HAL_WRAPPERS_UART   (1)
#define FEATURE_HAL_WRAPPERS_TIMER  (1)

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef enum
{
    GPIO_LED_1,
    GPIO_LED_2,
    GPIO_SERVO_TX_EN,
    GPIO_KLINE_TX,
    GPIO_KLINE_RX,
    GPIO_SERVO_TX,
    GPIO_SERVO_RX,
    GPIO_DEBUG_1,
    GPIO_DEBUG_2,
    GPIO_DEBUG_3,
    MAX_NUM_GPIO
} HalWrappers_Gpio_E;

typedef enum
{
    PWM_LED_1,
    MAX_NUM_PWM
} HalWrappers_Pwm_E;

typedef enum
{
    CAN_1,
    MAX_NUM_CAN
} HalWrappers_Can_E;

typedef enum
{
    UART_KLINE,
    UART_SERVO,
    MAX_NUM_UART
} HalWrappers_Uart_E;

typedef struct
{
    TIM_HandleTypeDef * pPwmTim;
    TIM_HandleTypeDef * pUsTim;
    CAN_HandleTypeDef * pCan[MAX_NUM_CAN];
    UART_HandleTypeDef * pUart[MAX_NUM_UART];
} HalWrappers_Config_S;

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers_Config_S gHalWrappersConfig;

#ifdef __cplusplus
}
#endif

#endif // HAL_WRAPPERS_CONFIG_H
