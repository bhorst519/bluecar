#ifndef HAL_WRAPPERS_H
#define HAL_WRAPPERS_H

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
typedef struct
{
    UART_HandleTypeDef * pSerial;
    TIM_HandleTypeDef * pPwmTim;
    CAN_HandleTypeDef * pCan;
} HalWrappers_Init_S;

typedef enum
{
    LED_1,
    LED_2,
    DEBUG_1,
    DEBUG_2,
    DEBUG_3,
    MAX_NUM_LEDS
} HalWrappers_Gpio_E;

/**************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                     *
**************************************************************************************************/
void HalWrappersInit(HalWrappers_Init_S * const pHalWrappersInitArg);

void HalWrappersGpioToggle(const HalWrappers_Gpio_E led);
void HalWrappersSetPwm(const float dutyCycle);
void HalWrapperCanRegisterRxFilter(const uint32_t mid);
void HalWrapperCanSetRxFilters(void);
void HalWrappersCanStart(void);
void HalWrappersCanTransmit(const uint32_t mid, const uint32_t dlc, const uint8_t * const pData);

#ifdef __cplusplus
}
#endif

#endif // HAL_WRAPPERS_H
