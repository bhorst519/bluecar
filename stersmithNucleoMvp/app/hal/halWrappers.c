/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "SAMPLE_canReceiver.h"
#include "halWrappers.h"
#include "stdbool.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define PWM_CHANNEL (TIM_CHANNEL_1)
#define SERIAL_UART (USART3) // Info only

#define MAX_SERIAL_BUFFER_BYTES (16U)

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef uint16_t Led_Id;

typedef struct
{
    Led_Id id;
    GPIO_TypeDef * periph;
} HalWrappers_Led_Info_S;

typedef struct
{
    uint16_t filt[HAL_WRAPPERS_FILTERS_PER_BANK];
    uint8_t currentFiltIdx;
} HalWrappers_Can_PendingRxFilter_S;

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
HalWrappers_Init_S * pHalWrappersInit;
HalWrappers_Can_PendingRxFilter_S gPendingRxFilter = {0};
uint32_t gCanFilterBankIdx = 0U;
uint8_t gSerialBytesTx[MAX_SERIAL_BUFFER_BYTES];
uint8_t gSerialBytesRx[MAX_SERIAL_BUFFER_BYTES];
bool gCanUseFifo1 = false;

// Static storage for HAL interfaces
TIM_OC_InitTypeDef sConfigOC = {0};

// Peripheral info wrappers for HAL interfaces
HalWrappers_Led_Info_S gLedInfo[MAX_NUM_LEDS] = {
    /* LED_1 */     {.id = GPIO_PIN_0, .periph = GPIOB},
    /* LED_2 */     {.id = GPIO_PIN_7, .periph = GPIOB},
    /* DEBUG_1 */   {.id = GPIO_PIN_9, .periph = GPIOG},
    /* DEBUG_2 */   {.id = GPIO_PIN_14, .periph = GPIOG},
    /* DEBUG_3 */   {.id = GPIO_PIN_15, .periph = GPIOF},
};

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void HalWrappersInit(HalWrappers_Init_S * const pHalWrappersInitArg)
{
    pHalWrappersInit = pHalWrappersInitArg;

    // PWM - start, disabled
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.Pulse = 0U;
    (void)HAL_TIM_PWM_Start(pHalWrappersInit->pPwmTim, PWM_CHANNEL);

    // UART - enable receive-to-idle in interrupt mode
    (void)HAL_UARTEx_ReceiveToIdle_IT(pHalWrappersInit->pSerial, &gSerialBytesRx[0U], MAX_SERIAL_BUFFER_BYTES);
}

void HalWrappersGpioToggle(const HalWrappers_Gpio_E led)
{
    HAL_GPIO_TogglePin(gLedInfo[led].periph, gLedInfo[led].id);
}

void HalWrappersSetPwm(const float dutyCycle)
{
    // Timer is configured to reload at 56000 counts.
    // For a 48MHz clock, this sets a 1.5kHz frequency
    uint16_t pulse = (uint16_t)(dutyCycle * 56000.0F);
    sConfigOC.Pulse = pulse;
    (void)HAL_TIM_PWM_ConfigChannel(pHalWrappersInit->pPwmTim, &sConfigOC, PWM_CHANNEL);
}

void HalWrapperCanRegisterRxFilter(const uint32_t mid)
{
    const uint8_t currentFiltIdx = gPendingRxFilter.currentFiltIdx;
    gPendingRxFilter.filt[currentFiltIdx] = (uint16_t)((mid << 5U) & 0xFFFF);
    if (++gPendingRxFilter.currentFiltIdx >= HAL_WRAPPERS_FILTERS_PER_BANK)
    {
        // Filled this pending filter bank - write it and clear
        HalWrapperCanSetRxFilters();
        gPendingRxFilter.currentFiltIdx = 0U;
    }
}

void HalWrapperCanSetRxFilters(void)
{
    CAN_FilterTypeDef rxFilter = {0};
    rxFilter.SlaveStartFilterBank = (HAL_WRAPPERS_MAX_FILTER_BANKS / 2U);
    rxFilter.FilterBank = gCanFilterBankIdx;
    rxFilter.FilterScale = CAN_FILTERSCALE_16BIT;
    rxFilter.FilterMode = CAN_FILTERMODE_IDLIST;
    rxFilter.FilterFIFOAssignment = gCanUseFifo1 ? CAN_FILTER_FIFO1 : CAN_FILTER_FIFO0;
    rxFilter.FilterActivation = CAN_FILTER_ENABLE;

    const uint8_t numFilt = gPendingRxFilter.currentFiltIdx;
    rxFilter.FilterIdLow = (numFilt > 0U) ? gPendingRxFilter.filt[0U] : 0U;
    rxFilter.FilterMaskIdLow = (numFilt > 1U) ? gPendingRxFilter.filt[1U] : 0U;
    rxFilter.FilterIdHigh = (numFilt > 2U) ? gPendingRxFilter.filt[2U] : 0U;
    rxFilter.FilterMaskIdHigh = (numFilt > 3U) ? gPendingRxFilter.filt[3U] : 0U;

    (void)HAL_CAN_ConfigFilter(pHalWrappersInit->pCan, &rxFilter);
    // Filter bank has been claimed - increment
    gCanFilterBankIdx++;
    // Alternate FIFOs - this should be done with better load balancing
    gCanUseFifo1 = !gCanUseFifo1;
}

void HalWrappersCanStart(void)
{
    // CAN - enable RX interrupts, set to normal mode to begin RX/TX
    (void)HAL_CAN_ActivateNotification(pHalWrappersInit->pCan, CAN_IT_RX_FIFO0_MSG_PENDING);
    (void)HAL_CAN_ActivateNotification(pHalWrappersInit->pCan, CAN_IT_RX_FIFO1_MSG_PENDING);
    (void)HAL_CAN_Start(pHalWrappersInit->pCan);
}

void HalWrappersCanTransmit(const uint32_t mid, const uint32_t dlc, const uint8_t * const pData)
{
    HalWrappersGpioToggle(DEBUG_3);
    CAN_TxHeaderTypeDef txHeader = {0};
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = mid;
    txHeader.DLC = dlc;
    uint32_t txMailboxStorage;
    (void)HAL_CAN_AddTxMessage(pHalWrappersInit->pCan, &txHeader, pData, &txMailboxStorage);
    HalWrappersGpioToggle(DEBUG_3);
}

//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    const uint16_t numRxBytes = (Size > 16U) ? 16U : Size;

    for (uint16_t i = 0U; i < numRxBytes; i++)
    {
        gSerialBytesTx[i] = gSerialBytesRx[i];
    }

    (void)HAL_UART_Transmit_IT(huart, &gSerialBytesTx[0U], numRxBytes);

    // Prepare another RX
    (void)HAL_UARTEx_ReceiveToIdle_IT(huart, &gSerialBytesRx[0U], MAX_SERIAL_BUFFER_BYTES);
}

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
// {
// }

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HalWrappersGpioToggle(DEBUG_1);
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);
    (void)CANRX_SAMPLE_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    HalWrappersGpioToggle(DEBUG_1);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HalWrappersGpioToggle(DEBUG_1);
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 1U, &rxHeader, &data[0U]);
    (void)CANRX_SAMPLE_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    HalWrappersGpioToggle(DEBUG_1);
}
