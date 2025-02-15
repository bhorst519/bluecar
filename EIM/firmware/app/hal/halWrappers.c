/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "halWrappers.h"
#include "EIM_canReceiverHook.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef uint16_t Gpio_Id;
typedef uint32_t Pwm_Ch;

typedef struct
{
    Gpio_Id id;
    GPIO_TypeDef * periph;
} HalWrappers_Gpio_Info_S;

typedef struct
{
    Pwm_Ch ch;
} HalWrappers_Pwm_Info_S;

typedef struct
{
    HalWrappers_Gpio_E rxPin;
    HalWrappers_Gpio_E txPin;
    void (* rxTxCompleteCallback)(UART_HandleTypeDef * huart);
} HalWrappers_Serial_Info_S;

typedef struct
{
    uint16_t filt[HAL_WRAPPERS_FILTERS_PER_BANK];
    uint8_t currentFiltIdx;
} HalWrappers_Can_PendingRxFilter_S;

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/
void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart);
void HalWrappersServoUartCallback(UART_HandleTypeDef *huart);

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static HalWrappers_Init_S * pHalWrappersInit;
static HalWrappers_Can_PendingRxFilter_S gPendingRxFilter[MAX_NUM_CAN] = {0};
static uint32_t gCanFilterBankIdx[MAX_NUM_CAN] = {0U};
static bool gCanUseFifo1[MAX_NUM_CAN] = {false};

// Static storage for HAL interfaces
static TIM_OC_InitTypeDef sConfigOC[MAX_NUM_PWM] = {0};

// Peripheral info wrappers for HAL interfaces
static const HalWrappers_Gpio_Info_S gGpioInfo[MAX_NUM_GPIO] = {
    /* GPIO_KLINE_TX */     {.id = GPIO_PIN_9,  .periph = GPIOA},
    /* GPIO_KLINE_RX */     {.id = GPIO_PIN_10, .periph = GPIOA},
    /* GPIO_SERVO_TX */     {.id = GPIO_PIN_5,  .periph = GPIOD},
    /* GPIO_SERVO_RX */     {.id = GPIO_PIN_6,  .periph = GPIOD},
};

static const HalWrappers_Pwm_Info_S gPwmInfo[MAX_NUM_PWM] = {
    /* PWM_LED_1 */         {.ch = TIM_CHANNEL_3},
    /* PWM_LED_2R */        {.ch = TIM_CHANNEL_1},
    /* PWM_LED_2G */        {.ch = TIM_CHANNEL_2},
    /* PWM_LED_2B */        {.ch = TIM_CHANNEL_4},
};

static const HalWrappers_Serial_Info_S gSerialInfo[MAX_NUM_SERIAL] = {
    /* SERIAL_KLINE */      {.rxPin = GPIO_KLINE_RX, .txPin = GPIO_KLINE_TX, .rxTxCompleteCallback = HalWrappersKlineUartCallback},
    /* SERIAL_SERVO */      {.rxPin = GPIO_SERVO_RX, .txPin = GPIO_SERVO_TX, .rxTxCompleteCallback = HalWrappersServoUartCallback},
};
static osThreadId gSerialTaskToNotify[MAX_NUM_SERIAL] = {0};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart)
{
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_RX_COMPLETE_CB_ID);

    // Task notify
    if (NULL != gSerialTaskToNotify[SERIAL_KLINE])
    {
        (void)osSignalSet(gSerialTaskToNotify[SERIAL_KLINE], 0);
    }

    // Yield if no task assigned
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HalWrappersServoUartCallback(UART_HandleTypeDef *huart)
{
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_RX_COMPLETE_CB_ID);

    // Task notify
    if (NULL != gSerialTaskToNotify[SERIAL_SERVO])
    {
        (void)osSignalSet(gSerialTaskToNotify[SERIAL_SERVO], 0);
    }

    // Yield if no task assigned
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// GPIO
//--------------------------------------------------------------------------------------------------
void HalWrappersInit(HalWrappers_Init_S * const pHalWrappersInitArg)
{
    pHalWrappersInit = pHalWrappersInitArg;

    // PWM - start, disabled
    for (uint8_t i = 0U; i < (uint8_t)MAX_NUM_PWM; ++i)
    {
        sConfigOC[i].OCMode = TIM_OCMODE_PWM1;
        sConfigOC[i].OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC[i].OCFastMode = TIM_OCFAST_DISABLE;
        sConfigOC[i].Pulse = 0U;
        (void)HAL_TIM_PWM_Start(pHalWrappersInit->pPwmTim, gPwmInfo[i].ch);
    }
    (void)HAL_TIM_Base_Start(pHalWrappersInit->pUsTim);
}

void HalWrappersGpioSet(const HalWrappers_Gpio_E gpio, const bool set)
{
    const GPIO_PinState state = set ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(gGpioInfo[gpio].periph, gGpioInfo[gpio].id, state);
}

void HalWrappersGpioToggle(const HalWrappers_Gpio_E gpio)
{
    HAL_GPIO_TogglePin(gGpioInfo[gpio].periph, gGpioInfo[gpio].id);
}

void HalWrappersSetPwm(const HalWrappers_Pwm_E pwm, const float dutyCycle)
{
    // Timer is configured to reload at 8000 counts.
    // For a 16MHz clock, this sets a 2.0kHz frequency
    uint16_t pulse = (uint16_t)(dutyCycle * 8000.0F);
    sConfigOC[pwm].Pulse = pulse;
    (void)HAL_TIM_PWM_ConfigChannel(pHalWrappersInit->pPwmTim, &sConfigOC[pwm], gPwmInfo[pwm].ch);
}

//--------------------------------------------------------------------------------------------------
// CAN
//--------------------------------------------------------------------------------------------------
void HalWrappersCanRegisterRxFilter(const HalWrappers_Can_E can, const uint32_t mid)
{
    const uint8_t currentFiltIdx = gPendingRxFilter[can].currentFiltIdx;
    gPendingRxFilter[can].filt[currentFiltIdx] = (uint16_t)((mid << 5U) & 0xFFFF);
    if (++gPendingRxFilter[can].currentFiltIdx >= HAL_WRAPPERS_FILTERS_PER_BANK)
    {
        // Filled this pending filter bank - write it and clear
        HalWrappersCanSetRxFilters(can);
        gPendingRxFilter[can].currentFiltIdx = 0U;
    }
}

void HalWrappersCanSetRxFilters(const HalWrappers_Can_E can)
{
    CAN_FilterTypeDef rxFilter = {0};
    rxFilter.SlaveStartFilterBank = (HAL_WRAPPERS_MAX_FILTER_BANKS / 2U);
    rxFilter.FilterBank = gCanFilterBankIdx[can];
    rxFilter.FilterScale = CAN_FILTERSCALE_16BIT;
    rxFilter.FilterMode = CAN_FILTERMODE_IDLIST;
    rxFilter.FilterFIFOAssignment = gCanUseFifo1[can] ? CAN_FILTER_FIFO1 : CAN_FILTER_FIFO0;
    rxFilter.FilterActivation = CAN_FILTER_ENABLE;

    const uint8_t numFilt = gPendingRxFilter[can].currentFiltIdx;
    rxFilter.FilterIdLow = (numFilt > 0U) ? gPendingRxFilter[can].filt[0U] : 0U;
    rxFilter.FilterMaskIdLow = (numFilt > 1U) ? gPendingRxFilter[can].filt[1U] : 0U;
    rxFilter.FilterIdHigh = (numFilt > 2U) ? gPendingRxFilter[can].filt[2U] : 0U;
    rxFilter.FilterMaskIdHigh = (numFilt > 3U) ? gPendingRxFilter[can].filt[3U] : 0U;

    (void)HAL_CAN_ConfigFilter(pHalWrappersInit->pCan[can], &rxFilter);
    // Filter bank has been claimed - increment
    gCanFilterBankIdx[can]++;
    // Alternate FIFOs - this should be done with better load balancing
    gCanUseFifo1[can] = !gCanUseFifo1[can];
}

void HalWrappersCanStart(const HalWrappers_Can_E can)
{
    // CAN - enable RX interrupts, set to normal mode to begin RX/TX
    (void)HAL_CAN_ActivateNotification(pHalWrappersInit->pCan[can], CAN_IT_RX_FIFO0_MSG_PENDING);
    (void)HAL_CAN_ActivateNotification(pHalWrappersInit->pCan[can], CAN_IT_RX_FIFO1_MSG_PENDING);
    (void)HAL_CAN_Start(pHalWrappersInit->pCan[can]);
}

void HalWrappersCanTransmit(const HalWrappers_Can_E can, const uint32_t mid, const uint32_t dlc, const uint8_t * const pData)
{
    CAN_TxHeaderTypeDef txHeader = {0};
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = mid;
    txHeader.DLC = dlc;
    uint32_t txMailboxStorage;
    (void)HAL_CAN_AddTxMessage(pHalWrappersInit->pCan[can], &txHeader, pData, &txMailboxStorage);
}

//--------------------------------------------------------------------------------------------------
// Serial
//--------------------------------------------------------------------------------------------------
void HalWrappersSetUartGpio(const HalWrappers_Serial_E serial, const bool setToGpio)
{
    const HalWrappers_Gpio_E rxPin = gSerialInfo[serial].rxPin;
    const HalWrappers_Gpio_E txPin = gSerialInfo[serial].txPin;

    if (setToGpio)
    {
        HAL_UART_MspDeInit(pHalWrappersInit->pSerial[serial]);
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = gGpioInfo[txPin].id;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(gGpioInfo[txPin].periph, &GPIO_InitStruct);
    }
    else
    {
        HAL_GPIO_DeInit(gGpioInfo[rxPin].periph, gGpioInfo[rxPin].id);
        HAL_GPIO_DeInit(gGpioInfo[txPin].periph, gGpioInfo[txPin].id);
        HAL_UART_MspInit(pHalWrappersInit->pSerial[serial]);
    }
}

bool HalWrappersUartTransmit(const HalWrappers_Serial_E serial, const uint8_t * const pTx, const uint32_t numBytes, const bool notify)
{
    HAL_StatusTypeDef status = HAL_OK;

    // Start receive
    if ((status == HAL_OK) && notify)
    {
        status = HAL_UART_RegisterCallback(pHalWrappersInit->pSerial[serial],
                                           HAL_UART_TX_COMPLETE_CB_ID,
                                           gSerialInfo[serial].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Transmit_IT(pHalWrappersInit->pSerial[serial], pTx, numBytes);
    }

    const bool success = (status == HAL_OK);
    if (!success)
    {
        HalWrappersUartAbort(serial);
    }
    return success;
}

bool HalWrappersUartReceive(const HalWrappers_Serial_E serial, uint8_t * const pRx, const uint32_t numBytes)
{
    HAL_StatusTypeDef status = HAL_OK;

    // Start receive
    if (status == HAL_OK)
    {
        status = HAL_UART_RegisterCallback(pHalWrappersInit->pSerial[serial],
                                           HAL_UART_RX_COMPLETE_CB_ID,
                                           gSerialInfo[serial].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Receive_IT(pHalWrappersInit->pSerial[serial], pRx, numBytes);
    }

    const bool success = (status == HAL_OK);
    if (!success)
    {
        HalWrappersUartAbort(serial);
    }
    return success;
}

bool HalWrappersUartWait(const HalWrappers_Serial_E serial, const uint32_t waitMs)
{
    // Wait for notification
    gSerialTaskToNotify[serial] = osThreadGetId();
    const osEvent result = osSignalWait(0, waitMs);
    gSerialTaskToNotify[serial] = NULL;

    const bool success = ((result.status == osOK) || (result.status == osEventSignal));
    if (!success)
    {
        HalWrappersUartAbort(serial);
    }
    return success;
}

void HalWrappersUartAbort(const HalWrappers_Serial_E serial)
{
    (void)HAL_UART_Abort_IT(pHalWrappersInit->pSerial[serial]);
    (void)HAL_UART_UnRegisterCallback(pHalWrappersInit->pSerial[serial], HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(pHalWrappersInit->pSerial[serial], HAL_UART_RX_COMPLETE_CB_ID);
}

//--------------------------------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------------------------------
void HalWrappersClearTimerUs(void)
{
    __HAL_TIM_SET_COUNTER(pHalWrappersInit->pUsTim, 0U);
}

uint32_t HalWrappersGetTimerUs(void)
{
    return __HAL_TIM_GET_COUNTER(pHalWrappersInit->pUsTim);
}

//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == pHalWrappersInit->pCan[CAN_1])
    {
        (void)CANRX_EIM_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == pHalWrappersInit->pCan[CAN_1])
    {
        (void)CANRX_EIM_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }
}
