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
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef enum
{
    // Outputs
    GPIO_MAIN_RELAY_EN,         // To power engine controller
    GPIO_HEADLIGHT_RELAY_EN,
    GPIO_ENG_ON_EN,             // To enable engine run/crank
    GPIO_ENG_START_EN,          // To crank engine
    GPIO_BRAKE_LIGHT_EN,
    GPIO_TURN_R_EN,
    GPIO_TURN_L_EN,
    GPIO_HIGH_BEAM_EN,
    GPIO_HORN_EN,
    GPIO_KLINE_EN,
    GPIO_KLINE_TX,
    GPIO_KLINE_RX,
    GPIO_SERVO_COMM_DIR,
    GPIO_SERVO_TX,
    GPIO_SERVO_RX,
    // Inputs
    GPIO_TACH,                  // Needs PWM-in/timer to determine RPM
    GPIO_GEAR_N,
    GPIO_GEAR_1,
    GPIO_GEAR_2,
    GPIO_GEAR_3,
    GPIO_GEAR_4,
    GPIO_GEAR_5,
    GPIO_GEAR_6,
    GPIO_TURN_R,
    GPIO_TURN_L,
    GPIO_LOW_BEAM,
    GPIO_HIGH_BEAM,
    GPIO_FAULT_IND,
    GPIO_OIL_P_LOW,
    MAX_NUM_GPIO
} HalWrappers_Gpio_E;

typedef enum
{
    PWM_LED_1,
    PWM_LED_2R,
    PWM_LED_2G,
    PWM_LED_2B,
    MAX_NUM_PWM
} HalWrappers_Pwm_E;

typedef enum
{
    ANALOG_12V,
    ANALOG_SERVO_12V,
    ANALOG_ENG_12V,
    ANALOG_ENG_TEMP,
    ANALOG_FUEL_LEVEL,
    ANALOG_FUEL_LOW,
    ANALOG_EXTRA,
    ANALOG_DIE_TEMP,
    ANALOG_ENG_ON_ISENSE,
    ANALOG_ENG_START_ISENSE,
    ANALOG_BRAKE_LIGHT_ISENSE,
    ANALOG_TURN_R_ISENSE,
    ANALOG_TURN_L_ISENSE,
    ANALOG_HIGH_BEAM_ISENSE,
    ANALOG_HORN_ISENSE,
    MAX_NUM_ANALOG
} HalWrappers_Analog_E;

typedef enum
{
    CAN_1,
    CAN_2,
    MAX_NUM_CAN
} HalWrappers_Can_E;

typedef enum
{
    SERIAL_KLINE,
    SERIAL_SERVO,
    MAX_NUM_SERIAL
} HalWrappers_Serial_E;

typedef struct
{
    ADC_HandleTypeDef * pAdc;
    TIM_HandleTypeDef * pPwmTim;
    TIM_HandleTypeDef * pUsTim;
    CAN_HandleTypeDef * pCan[MAX_NUM_CAN];
    UART_HandleTypeDef * pSerial[MAX_NUM_SERIAL];
} HalWrappers_Config_S;

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers_Config_S gHalWrappersConfig;

#ifdef __cplusplus
}
#endif

#endif // HAL_WRAPPERS_CONFIG_H
