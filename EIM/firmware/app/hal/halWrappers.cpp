/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canReceiverHook.h"
#include "halWrappers.hpp"
#include "profiler.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

using Gpio_Id = uint16_t;
using Pwm_Ch = uint32_t;

struct HalWrappers_Gpio_Info_S
{
    Gpio_Id id;
    GPIO_TypeDef * periph;
};

struct HalWrappers_Adc_Info_S
{
    uint32_t ch;
    float scale;
    float offset;
};

struct HalWrappers_Pwm_Info_S
{
    Pwm_Ch ch;
};

struct HalWrappers_Serial_Info_S
{
    HalWrappers_Gpio_E rxPin;
    HalWrappers_Gpio_E txPin;
    void (* rxTxCompleteCallback)(UART_HandleTypeDef * huart);
};

struct HalWrappers_Can_PendingRxFilter_S
{
    uint16_t filt[HAL_WRAPPERS_FILTERS_PER_BANK];
    uint8_t currentFiltIdx;
};

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/
static void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart);
static void HalWrappersServoUartCallback(UART_HandleTypeDef *huart);

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static HalWrappers_Config_S * pHalWrappersConfig;
static float_q gAdcValues[MAX_NUM_ANALOG];
static HalWrappers_Can_PendingRxFilter_S gPendingRxFilter[MAX_NUM_CAN];
static uint32_t gCanFilterBankIdx[MAX_NUM_CAN];
static bool gCanUseFifo1[MAX_NUM_CAN];

// Peripheral info wrappers for HAL interfaces
static constexpr HalWrappers_Gpio_Info_S gGpioInfo[MAX_NUM_GPIO] = {
    // Outputs
    /* GPIO_MAIN_RELAY_EN */        {.id = GPIO_PIN_3,  .periph = GPIOF},
    /* GPIO_HEADLIGHT_RELAY_EN */   {.id = GPIO_PIN_13, .periph = GPIOE},
    /* GPIO_ENG_ON_EN */            {.id = GPIO_PIN_4,  .periph = GPIOF},
    /* GPIO_ENG_START_EN */         {.id = GPIO_PIN_5,  .periph = GPIOF},
    /* GPIO_BRAKE_LIGHT_EN */       {.id = GPIO_PIN_6,  .periph = GPIOF},
    /* GPIO_TURN_R_EN */            {.id = GPIO_PIN_9,  .periph = GPIOF},
    /* GPIO_TURN_L_EN */            {.id = GPIO_PIN_8,  .periph = GPIOF},
    /* GPIO_HIGH_BEAM_EN */         {.id = GPIO_PIN_7,  .periph = GPIOF},
    /* GPIO_HORN_EN */              {.id = GPIO_PIN_10, .periph = GPIOF},
    /* GPIO_KLINE_EN */             {.id = GPIO_PIN_2,  .periph = GPIOF},
    /* GPIO_KLINE_TX */             {.id = GPIO_PIN_9,  .periph = GPIOA},
    /* GPIO_KLINE_RX */             {.id = GPIO_PIN_10, .periph = GPIOA},
    /* GPIO_SERVO_COMM_DIR */       {.id = GPIO_PIN_4,  .periph = GPIOD},
    /* GPIO_SERVO_TX */             {.id = GPIO_PIN_5,  .periph = GPIOD},
    /* GPIO_SERVO_RX */             {.id = GPIO_PIN_6,  .periph = GPIOD},

    // Inputs
    /* GPIO_TACH */                 {.id = GPIO_PIN_12, .periph = GPIOF},
    /* GPIO_GEAR_N */               {.id = GPIO_PIN_13, .periph = GPIOF},
    /* GPIO_GEAR_1 */               {.id = GPIO_PIN_12, .periph = GPIOE},
    /* GPIO_GEAR_2 */               {.id = GPIO_PIN_11, .periph = GPIOE},
    /* GPIO_GEAR_3 */               {.id = GPIO_PIN_10, .periph = GPIOE},
    /* GPIO_GEAR_4 */               {.id = GPIO_PIN_9,  .periph = GPIOE},
    /* GPIO_GEAR_5 */               {.id = GPIO_PIN_8,  .periph = GPIOE},
    /* GPIO_GEAR_6 */               {.id = GPIO_PIN_7,  .periph = GPIOE},
    /* GPIO_TURN_R  */              {.id = GPIO_PIN_1,  .periph = GPIOG},
    /* GPIO_TURN_L  */              {.id = GPIO_PIN_0,  .periph = GPIOG},
    /* GPIO_LOW_BEAM */             {.id = GPIO_PIN_14, .periph = GPIOF},
    /* GPIO_HIGH_BEAM */            {.id = GPIO_PIN_15, .periph = GPIOF},
    /* GPIO_FAULT_IND */            {.id = GPIO_PIN_5,  .periph = GPIOC},
    /* GPIO_OIL_P_LOW */            {.id = GPIO_PIN_11, .periph = GPIOF},
};

static constexpr HalWrappers_Pwm_Info_S gPwmInfo[MAX_NUM_PWM] = {
    /* PWM_LED_1 */         {.ch = TIM_CHANNEL_3},
    /* PWM_LED_2R */        {.ch = TIM_CHANNEL_1},
    /* PWM_LED_2G */        {.ch = TIM_CHANNEL_2},
    /* PWM_LED_2B */        {.ch = TIM_CHANNEL_4},
};

static constexpr HalWrappers_Adc_Info_S gAdcInfo[MAX_NUM_ANALOG] = {
    /* ANALOG_12V                */ {.ch = ADC_CHANNEL_9,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_SERVO_12V          */ {.ch = ADC_CHANNEL_7,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_ENG_12V            */ {.ch = ADC_CHANNEL_3,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_ENG_TEMP           */ {.ch = ADC_CHANNEL_6,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_FUEL_LEVEL         */ {.ch = ADC_CHANNEL_4,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_FUEL_LOW           */ {.ch = ADC_CHANNEL_5,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_EXTRA              */ {.ch = ADC_CHANNEL_8,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_DIE_TEMP           */ {.ch = ADC_CHANNEL_TEMPSENSOR, .scale = 400.0F, .offset = -279.0F}, // 2.5mV / degC, .76V @ 25degC
    /* ANALOG_ENG_ON_ISENSE      */ {.ch = ADC_CHANNEL_10,         .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_ENG_START_ISENSE   */ {.ch = ADC_CHANNEL_2,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_BRAKE_LIGHT_ISENSE */ {.ch = ADC_CHANNEL_1,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_TURN_R_ISENSE      */ {.ch = ADC_CHANNEL_12,         .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_TURN_L_ISENSE      */ {.ch = ADC_CHANNEL_13,         .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_HIGH_BEAM_ISENSE   */ {.ch = ADC_CHANNEL_0,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_HORN_ISENSE        */ {.ch = ADC_CHANNEL_11,         .scale = 1.0F, .offset = 0.0F},

};
static HalWrappers_Analog_E gAdcToPoll = MAX_NUM_ANALOG;

static constexpr HalWrappers_Serial_Info_S gSerialInfo[MAX_NUM_SERIAL] = {
    /* SERIAL_KLINE */ {.rxPin = GPIO_KLINE_RX, .txPin = GPIO_KLINE_TX, .rxTxCompleteCallback = HalWrappersKlineUartCallback},
    /* SERIAL_SERVO */ {.rxPin = GPIO_SERVO_RX, .txPin = GPIO_SERVO_TX, .rxTxCompleteCallback = HalWrappersServoUartCallback},
};
static osThreadId gSerialTaskToNotify[MAX_NUM_SERIAL];

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
static void HalWrappersAdcStartConversion(const HalWrappers_Analog_E adc)
{
    ADC_ChannelConfTypeDef adcChannel{};
    adcChannel.Channel = gAdcInfo[adc].ch;
    adcChannel.Rank = 1;
    // adcChannel.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    adcChannel.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    if (HAL_ADC_ConfigChannel(pHalWrappersConfig->pAdc, &adcChannel) == HAL_OK)
    {
        (void)HAL_ADC_Start_IT(pHalWrappersConfig->pAdc);
    }
}

static void HalWrappersAdcProcessConversion(const HalWrappers_Analog_E adc)
{
    uint32_t resMax;
    switch (ADC_GET_RESOLUTION(pHalWrappersConfig->pAdc))
    {
        case ADC_RESOLUTION_6B:
            resMax = BIT_U32(6U) - 1U;
            break;
        case ADC_RESOLUTION_8B:
            resMax = BIT_U32(8) - 1;
            break;
        case ADC_RESOLUTION_10B:
            resMax = BIT_U32(10) - 1;
            break;
        case ADC_RESOLUTION_12B:
        default:
            resMax = BIT_U32(12) - 1;
            break;
    }

    const uint32_t resRaw = HAL_ADC_GetValue(pHalWrappersConfig->pAdc);
    const float resV = (static_cast<float>(resRaw) / static_cast<float>(resMax)) * ADC_REF_V;
    gAdcValues[adc] = (resV * gAdcInfo[adc].scale) + gAdcInfo[adc].offset;
    gAdcValues[adc] = SignalStatus_E::VALID;
}

static void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart)
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

static void HalWrappersServoUartCallback(UART_HandleTypeDef *huart)
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
void HalWrappersInit(HalWrappers_Config_S * const pHalWrappersConfigArg)
{
    pHalWrappersConfig = pHalWrappersConfigArg;

    // PWM - start, disabled
    for (uint8_t i = 0U; i < static_cast<uint8_t>(MAX_NUM_PWM); ++i)
    {
        (void)HAL_TIM_PWM_Start(pHalWrappersConfig->pPwmTim, gPwmInfo[i].ch);
    }
    (void)HAL_TIM_Base_Start(pHalWrappersConfig->pUsTim);
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
    // Timer is configured to reload at 45000 counts.
    // For a 90MHz clock, this sets a 2.0kHz frequency
    const float dutyCycleToUse = SATURATE(dutyCycle, 0.0F, 1.0F);
    uint16_t pulse = static_cast<uint16_t>(dutyCycleToUse * 45000.0F);

    TIM_OC_InitTypeDef pwmChannel{};
    pwmChannel.OCMode = TIM_OCMODE_PWM1;
    pwmChannel.OCPolarity = TIM_OCPOLARITY_HIGH;
    pwmChannel.OCFastMode = TIM_OCFAST_DISABLE;
    pwmChannel.Pulse = pulse;
    (void)HAL_TIM_PWM_ConfigChannel(pHalWrappersConfig->pPwmTim, &pwmChannel, gPwmInfo[pwm].ch);
}

//--------------------------------------------------------------------------------------------------
// ADC
//--------------------------------------------------------------------------------------------------
void HalWrappersAdcTriggerStart(void)
{
    ProfilerCheckIn(PROFILER_ADC_CONV);
    for (uint8_t i = 0U; i < static_cast<uint8_t>(MAX_NUM_ANALOG); ++i)
    {
        gAdcValues[i] = SignalStatus_E::SNA;
    }

    gAdcToPoll = static_cast<HalWrappers_Analog_E>(0U);
    HalWrappersAdcStartConversion(gAdcToPoll);
}

bool HalWrappersAdcGetFinished(void)
{
    return (gAdcToPoll >= MAX_NUM_ANALOG);
}

float_q HalWrappersAdcGetValue(const HalWrappers_Analog_E adc)
{
    return gAdcValues[adc];
}

//--------------------------------------------------------------------------------------------------
// CAN
//--------------------------------------------------------------------------------------------------
void HalWrappersCanRegisterRxFilter(const HalWrappers_Can_E can, const uint32_t mid)
{
    const uint8_t currentFiltIdx = gPendingRxFilter[can].currentFiltIdx;
    gPendingRxFilter[can].filt[currentFiltIdx] = static_cast<uint16_t>((mid << 5U) & 0xFFFF);
    if (++gPendingRxFilter[can].currentFiltIdx >= HAL_WRAPPERS_FILTERS_PER_BANK)
    {
        // Filled this pending filter bank - write it and clear
        HalWrappersCanSetRxFilters(can);
        gPendingRxFilter[can].currentFiltIdx = 0U;
    }
}

void HalWrappersCanSetRxFilters(const HalWrappers_Can_E can)
{
    CAN_FilterTypeDef rxFilter{};
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

    (void)HAL_CAN_ConfigFilter(pHalWrappersConfig->pCan[can], &rxFilter);
    // Filter bank has been claimed - increment
    gCanFilterBankIdx[can]++;
    // Alternate FIFOs - this should be done with better load balancing
    gCanUseFifo1[can] = !gCanUseFifo1[can];
}

void HalWrappersCanStart(const HalWrappers_Can_E can)
{
    // CAN - enable RX interrupts, set to normal mode to begin RX/TX
    (void)HAL_CAN_ActivateNotification(pHalWrappersConfig->pCan[can], CAN_IT_RX_FIFO0_MSG_PENDING);
    (void)HAL_CAN_ActivateNotification(pHalWrappersConfig->pCan[can], CAN_IT_RX_FIFO1_MSG_PENDING);
    (void)HAL_CAN_Start(pHalWrappersConfig->pCan[can]);
}

void HalWrappersCanTransmit(const HalWrappers_Can_E can, const uint32_t mid, const uint32_t dlc, const uint8_t * const pData)
{
    CAN_TxHeaderTypeDef txHeader{};
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = mid;
    txHeader.DLC = dlc;
    uint32_t txMailboxStorage;
    (void)HAL_CAN_AddTxMessage(pHalWrappersConfig->pCan[can], &txHeader, pData, &txMailboxStorage);
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
        HAL_UART_MspDeInit(pHalWrappersConfig->pSerial[serial]);
        GPIO_InitTypeDef GPIO_InitStruct{};
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
        HAL_UART_MspInit(pHalWrappersConfig->pSerial[serial]);
    }
}

bool HalWrappersUartTransmit(const HalWrappers_Serial_E serial, const uint8_t * const pTx, const uint32_t numBytes, const bool notify)
{
    HAL_StatusTypeDef status = HAL_OK;

    // Start receive
    if ((status == HAL_OK) && notify)
    {
        status = HAL_UART_RegisterCallback(pHalWrappersConfig->pSerial[serial],
                                           HAL_UART_TX_COMPLETE_CB_ID,
                                           gSerialInfo[serial].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Transmit_IT(pHalWrappersConfig->pSerial[serial], pTx, numBytes);
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
        status = HAL_UART_RegisterCallback(pHalWrappersConfig->pSerial[serial],
                                           HAL_UART_RX_COMPLETE_CB_ID,
                                           gSerialInfo[serial].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Receive_IT(pHalWrappersConfig->pSerial[serial], pRx, numBytes);
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
    (void)HAL_UART_Abort_IT(pHalWrappersConfig->pSerial[serial]);
    (void)HAL_UART_UnRegisterCallback(pHalWrappersConfig->pSerial[serial], HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(pHalWrappersConfig->pSerial[serial], HAL_UART_RX_COMPLETE_CB_ID);
}

//--------------------------------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------------------------------
void HalWrappersClearTimerUs(void)
{
    __HAL_TIM_SET_COUNTER(pHalWrappersConfig->pUsTim, 0U);
}

uint32_t HalWrappersGetTimerUs(void)
{
    return __HAL_TIM_GET_COUNTER(pHalWrappersConfig->pUsTim);
}

} // namespace Eim

//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
extern "C" {

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == Eim::pHalWrappersConfig->pCan[CAN_1])
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

    if (hcan == Eim::pHalWrappersConfig->pCan[CAN_1])
    {
        (void)CANRX_EIM_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    (void)hadc;
    Eim::HalWrappersAdcProcessConversion(Eim::gAdcToPoll);

    const uint32_t adcToPollInt = static_cast<uint32_t>(Eim::gAdcToPoll);
    Eim::gAdcToPoll = static_cast<HalWrappers_Analog_E>(adcToPollInt + 1U);
    if (Eim::gAdcToPoll < MAX_NUM_ANALOG)
    {
        Eim::HalWrappersAdcStartConversion(Eim::gAdcToPoll);
    }
    else
    {
        ProfilerCheckOut(PROFILER_ADC_CONV, true);
    }
}

} // extern "C"
