#ifndef HAL_WRAPPERS_CONFIG_H
#define HAL_WRAPPERS_CONFIG_H

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
#define FEATURE_HAL_WRAPPERS_GPIO   (1)
#define FEATURE_HAL_WRAPPERS_ADC    (1)
#define FEATURE_HAL_WRAPPERS_CAN    (1)
#define FEATURE_HAL_WRAPPERS_TIMER  (1)

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef enum
{
    // Outputs
    GPIO_LED_DEV_G,
    GPIO_LED_DEV_B,
    GPIO_LED_DEV_R,
    GPIO_LED_R,
    GPIO_LED_G,
    // Inputs
    GPIO_ENG_ENABLE,
    GPIO_ENG_START,
    GPIO_USER_SWITCH,
    GPIO_BRAKE_SWITCH,
    MAX_NUM_GPIO
} HalWrappers_Gpio_E;

typedef enum
{
    ANALOG_APS_1,
    ANALOG_APS_2,
    MAX_NUM_ANALOG
} HalWrappers_Analog_E;

typedef enum
{
    CAN_1,
    MAX_NUM_CAN
} HalWrappers_Can_E;

typedef struct
{
    ADC_HandleTypeDef * pAdc;
    TIM_HandleTypeDef * pUsTim;
    CAN_HandleTypeDef * pCan[MAX_NUM_CAN];
} HalWrappers_Config_S;

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers_Config_S gHalWrappersConfig;

#ifdef __cplusplus
}
#endif

#endif // HAL_WRAPPERS_CONFIG_H
