#ifndef HAL_WRAPPERS_H
#define HAL_WRAPPERS_H

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
// Each pair of CAN peripherals has 28 filter banks - e.g. CAN1 and CAN2 share 28.
// For an isolated CAN peripheral, it has 14 banks - e.g. CAN3 has 14.
// Each filter bank contains 2 32-bit registers for filter configuration.
// These can be configured in 1 of 4 ways depending on the combo of 2 configs:
//      * Mask or ID list mode
//      * 32-bit or 16-bit mode
// 1. Mask + 32-bit mode: one register for ext ID, one for masking (1 must-match, or 0 don't-care)
// 2. Mask + 16-bit mode: two pairs of - one register for std ID, one for masking (1 must-match, or 0 don't-care)
// 3. List + 32-bit mode: two registers for ext ID
// 4. List + 16-bit mode: four registers for std ID
// For simplicity, assume we don't need ext ID and use mode 4
#define HAL_WRAPPERS_MAX_FILTER_BANKS (28U)
#define HAL_WRAPPERS_FILTER_BANKS_PER_BUS (HAL_WRAPPERS_MAX_FILTER_BANKS / 2U)
#define HAL_WRAPPERS_FILTERS_PER_BANK (4U)
#define HAL_WRAPPERS_FILTERS_PER_BUS (HAL_WRAPPERS_FILTERS_PER_BANK * HAL_WRAPPERS_FILTER_BANKS_PER_BUS)

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
    MAX_NUM_ANALOG
} HalWrappers_Analog_E; // TODO

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
    UART_HandleTypeDef * pSerial[MAX_NUM_SERIAL];
    TIM_HandleTypeDef * pPwmTim;
    TIM_HandleTypeDef * pUsTim;
    CAN_HandleTypeDef * pCan[MAX_NUM_CAN];
} HalWrappers_Init_S;

/**************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                     *
**************************************************************************************************/
void HalWrappersInit(HalWrappers_Init_S * const pHalWrappersInitArg);

// GPIO
void HalWrappersGpioSet(const HalWrappers_Gpio_E gpio, const bool level);
void HalWrappersGpioToggle(const HalWrappers_Gpio_E gpio);
void HalWrappersSetPwm(const HalWrappers_Pwm_E pwm, const float dutyCycle);

// CAN
void HalWrappersCanRegisterRxFilter(const HalWrappers_Can_E can, const uint32_t mid);
void HalWrappersCanSetRxFilters(const HalWrappers_Can_E can);
void HalWrappersCanStart(const HalWrappers_Can_E can);
void HalWrappersCanTransmit(const HalWrappers_Can_E can, const uint32_t mid, const uint32_t dlc, const uint8_t * const pData);

// Serial
void HalWrappersSetUartGpio(const HalWrappers_Serial_E serial, const bool setToGpio);
bool HalWrappersUartTransmit(const HalWrappers_Serial_E serial, const uint8_t * const pTx, const uint32_t numBytes, const bool notify);
bool HalWrappersUartReceive(const HalWrappers_Serial_E serial, uint8_t * const pRx, const uint32_t numBytes);
bool HalWrappersUartWait(const HalWrappers_Serial_E serial, const uint32_t waitMs);
void HalWrappersUartAbort(const HalWrappers_Serial_E serial);

// Timer
void HalWrappersClearTimerUs(void);
uint32_t HalWrappersGetTimerUs(void);

#ifdef __cplusplus
}
#endif

#endif // HAL_WRAPPERS_H
