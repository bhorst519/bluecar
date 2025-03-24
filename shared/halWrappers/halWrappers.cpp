/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Shared
{

//--------------------------------------------------------------------------------------------------
// GPIO
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_GPIO == 1)
void HalWrappersGpio::GpioSet(const HalWrappers_Gpio_E gpio, const bool set)
{
    const GPIO_PinState state = set ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(m_gpioInfo[gpio].periph, m_gpioInfo[gpio].id, state);
}

void HalWrappersGpio::GpioToggle(const HalWrappers_Gpio_E gpio)
{
    HAL_GPIO_TogglePin(m_gpioInfo[gpio].periph, m_gpioInfo[gpio].id);
}

bool HalWrappersGpio::GpioRead(const HalWrappers_Gpio_E gpio)
{
    const GPIO_PinState pinState = HAL_GPIO_ReadPin(m_gpioInfo[gpio].periph, m_gpioInfo[gpio].id);
    return (pinState == GPIO_PIN_SET ? true : false);
}

void HalWrappersGpio::GpioInitConfigPin(const HalWrappers_Gpio_E gpio)
{
    GPIO_InitTypeDef GPIO_InitStruct{};
    GPIO_InitStruct.Pin = m_gpioInfo[gpio].id;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(m_gpioInfo[gpio].periph, &GPIO_InitStruct);
}

void HalWrappersGpio::GpioDeinitConfigPin(const HalWrappers_Gpio_E gpio)
{
    HAL_GPIO_DeInit(m_gpioInfo[gpio].periph, m_gpioInfo[gpio].id);
}
#endif

//--------------------------------------------------------------------------------------------------
// PWM
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_PWM == 1)
void HalWrappersPwm::PwmSet(const HalWrappers_Pwm_E pwm, const float dutyCycle)
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
    (void)HAL_TIM_PWM_ConfigChannel(m_pPwmTim, &pwmChannel, m_pwmInfo[pwm].ch);
}
#endif

//--------------------------------------------------------------------------------------------------
// ADC
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_ADC == 1)
void HalWrappersAdc::AdcTriggerStart(void)
{
    for (uint8_t i = 0U; i < static_cast<uint8_t>(MAX_NUM_ANALOG); ++i)
    {
        m_adcValues[i] = SignalStatus_E::SNA;
    }

    m_adcToPoll = static_cast<HalWrappers_Analog_E>(0U);
    AdcStartConversion(m_adcToPoll);
}

bool HalWrappersAdc::AdcGetFinished(void)
{
    return (m_adcToPoll >= MAX_NUM_ANALOG);
}

float_q HalWrappersAdc::AdcGetValue(const HalWrappers_Analog_E adc)
{
    return m_adcValues[adc];
}

void HalWrappersAdc::AdcProcessConversion(void)
{
    uint32_t resMax;
    switch (ADC_GET_RESOLUTION(m_pAdc))
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

    const uint32_t resRaw = HAL_ADC_GetValue(m_pAdc);
    const float resV = (static_cast<float>(resRaw) / static_cast<float>(resMax)) * ADC_REF_V;
    m_adcValues[m_adcToPoll] = (resV * m_adcInfo[m_adcToPoll].scale) + m_adcInfo[m_adcToPoll].offset;
    m_adcValues[m_adcToPoll] = SignalStatus_E::VALID;

    const uint32_t adcToPollInt = static_cast<uint32_t>(m_adcToPoll);
    m_adcToPoll = static_cast<HalWrappers_Analog_E>(adcToPollInt + 1U);
    if (m_adcToPoll < MAX_NUM_ANALOG)
    {
        AdcStartConversion(m_adcToPoll);
    }
}

void HalWrappersAdc::AdcStartConversion(const HalWrappers_Analog_E adc)
{
    ADC_ChannelConfTypeDef adcChannel{};
    adcChannel.Channel = m_adcInfo[adc].ch;
    adcChannel.Rank = 1;
    // adcChannel.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    adcChannel.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    if (HAL_ADC_ConfigChannel(m_pAdc, &adcChannel) == HAL_OK)
    {
        (void)HAL_ADC_Start_IT(m_pAdc);
    }
}
#endif

//--------------------------------------------------------------------------------------------------
// CAN
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_CAN == 1)
void HalWrappersCan::CanRegisterRxFilter(const HalWrappers_Can_E can, const uint32_t mid)
{
    const uint8_t currentFiltIdx = m_pendingRxFilter[can].currentFiltIdx;
    m_pendingRxFilter[can].filt[currentFiltIdx] = static_cast<uint16_t>((mid << 5U) & 0xFFFF);
    if (++m_pendingRxFilter[can].currentFiltIdx >= HAL_WRAPPERS_FILTERS_PER_BANK)
    {
        // Filled this pending filter bank - write it and clear
        CanSetRxFilters(can);
        m_pendingRxFilter[can].currentFiltIdx = 0U;
    }
}

void HalWrappersCan::CanSetRxFilters(const HalWrappers_Can_E can)
{
    CAN_FilterTypeDef rxFilter{};
    rxFilter.SlaveStartFilterBank = (HAL_WRAPPERS_MAX_FILTER_BANKS / 2U);
    rxFilter.FilterBank = m_filterBankIdx[can];
    rxFilter.FilterScale = CAN_FILTERSCALE_16BIT;
    rxFilter.FilterMode = CAN_FILTERMODE_IDLIST;
    rxFilter.FilterFIFOAssignment = m_useFifo1[can] ? CAN_FILTER_FIFO1 : CAN_FILTER_FIFO0;
    rxFilter.FilterActivation = CAN_FILTER_ENABLE;

    const uint8_t numFilt = m_pendingRxFilter[can].currentFiltIdx;
    rxFilter.FilterIdLow = (numFilt > 0U) ? m_pendingRxFilter[can].filt[0U] : 0U;
    rxFilter.FilterMaskIdLow = (numFilt > 1U) ? m_pendingRxFilter[can].filt[1U] : 0U;
    rxFilter.FilterIdHigh = (numFilt > 2U) ? m_pendingRxFilter[can].filt[2U] : 0U;
    rxFilter.FilterMaskIdHigh = (numFilt > 3U) ? m_pendingRxFilter[can].filt[3U] : 0U;

    (void)HAL_CAN_ConfigFilter(m_pCan[can], &rxFilter);
    // Filter bank has been claimed - increment
    m_filterBankIdx[can]++;
    // Alternate FIFOs - this should be done with better load balancing
    m_useFifo1[can] = !m_useFifo1[can];
}

void HalWrappersCan::CanStart(const HalWrappers_Can_E can)
{
    // CAN - enable RX interrupts, set to normal mode to begin RX/TX
    (void)HAL_CAN_ActivateNotification(m_pCan[can], CAN_IT_RX_FIFO0_MSG_PENDING);
    (void)HAL_CAN_ActivateNotification(m_pCan[can], CAN_IT_RX_FIFO1_MSG_PENDING);
    (void)HAL_CAN_Start(m_pCan[can]);
}

void HalWrappersCan::CanTransmit(const HalWrappers_Can_E can, const uint32_t mid, const uint32_t dlc, const uint8_t * const pData)
{
    CAN_TxHeaderTypeDef txHeader{};
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.StdId = mid;
    txHeader.DLC = dlc;
    uint32_t txMailboxStorage;
    (void)HAL_CAN_AddTxMessage(m_pCan[can], &txHeader, pData, &txMailboxStorage);
}
#endif

//--------------------------------------------------------------------------------------------------
// UART
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_UART == 1)
void HalWrappersUart::UartSetGpio(const HalWrappers_Uart_E uart, const bool setToGpio, HalWrappersGpio& halGpio)
{
    const HalWrappers_Gpio_E rxPin = m_uartInfo[uart].rxPin;
    const HalWrappers_Gpio_E txPin = m_uartInfo[uart].txPin;

    if (setToGpio)
    {
        HAL_UART_MspDeInit(m_pUart[uart]);
        halGpio.GpioInitConfigPin(txPin);
    }
    else
    {
        halGpio.GpioDeinitConfigPin(rxPin);
        halGpio.GpioDeinitConfigPin(txPin);
        HAL_UART_MspInit(m_pUart[uart]);
    }
}

bool HalWrappersUart::UartTransmit(const HalWrappers_Uart_E uart, const uint8_t * const pTx, const uint32_t numBytes, const bool notify)
{
    HAL_StatusTypeDef status = HAL_OK;

    // Start receive
    if ((status == HAL_OK) && notify)
    {
        status = HAL_UART_RegisterCallback(m_pUart[uart],
                                           HAL_UART_TX_COMPLETE_CB_ID,
                                           m_uartInfo[uart].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Transmit_IT(m_pUart[uart], pTx, numBytes);
    }

    const bool success = (status == HAL_OK);
    if (!success)
    {
        UartAbort(uart);
    }
    return success;
}

bool HalWrappersUart::UartReceive(const HalWrappers_Uart_E uart, uint8_t * const pRx, const uint32_t numBytes)
{
    HAL_StatusTypeDef status = HAL_OK;

    // Start receive
    if (status == HAL_OK)
    {
        status = HAL_UART_RegisterCallback(m_pUart[uart],
                                           HAL_UART_RX_COMPLETE_CB_ID,
                                           m_uartInfo[uart].rxTxCompleteCallback);
    }

    if (status == HAL_OK)
    {
        status = HAL_UART_Receive_IT(m_pUart[uart], pRx, numBytes);
    }

    const bool success = (status == HAL_OK);
    if (!success)
    {
        UartAbort(uart);
    }
    return success;
}

bool HalWrappersUart::UartWait(const HalWrappers_Uart_E uart, const uint32_t waitMs)
{
    // Wait for notification
    m_taskToNotify[uart] = osThreadGetId();
    const osEvent result = osSignalWait(0, waitMs);
    m_taskToNotify[uart] = NULL;

    const bool success = ((result.status == osOK) || (result.status == osEventSignal));
    if (!success)
    {
        UartAbort(uart);
    }
    return success;
}

void HalWrappersUart::UartAbort(const HalWrappers_Uart_E uart)
{
    (void)HAL_UART_Abort_IT(m_pUart[uart]);
    (void)HAL_UART_UnRegisterCallback(m_pUart[uart], HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(m_pUart[uart], HAL_UART_RX_COMPLETE_CB_ID);
}
#endif

//--------------------------------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_TIMER == 1)
void HalWrappersTimer::TimerClearUs(void)
{
    __HAL_TIM_SET_COUNTER(m_pUsTim, 0U);
}

uint32_t HalWrappersTimer::TimerGetUs(void)
{
    return __HAL_TIM_GET_COUNTER(m_pUsTim);
}
#endif

} // namespace Eim
