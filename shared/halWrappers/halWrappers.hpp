#ifndef HAL_WRAPPERS_HPP
#define HAL_WRAPPERS_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "halWrappersConfig.h"
#include "nocopy.hpp"
#include "qualifiedValTypes.hpp"
#include "stm32f4xx_hal.h"
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#ifndef FEATURE_HAL_WRAPPERS_GPIO
# define FEATURE_HAL_WRAPPERS_GPIO (0)
#endif

#ifndef FEATURE_HAL_WRAPPERS_PWM
# define FEATURE_HAL_WRAPPERS_PWM (0)
#endif

#ifndef FEATURE_HAL_WRAPPERS_ADC
# define FEATURE_HAL_WRAPPERS_ADC (0)
#endif

#ifndef FEATURE_HAL_WRAPPERS_CAN
# define FEATURE_HAL_WRAPPERS_CAN (0)
#endif

#ifndef FEATURE_HAL_WRAPPERS_UART
# define FEATURE_HAL_WRAPPERS_UART (0)
#endif

#ifndef FEATURE_HAL_WRAPPERS_TIMER
# define FEATURE_HAL_WRAPPERS_TIMER (0)
#endif

namespace Shared
{

static constexpr float ADC_REF_V {3.3F};

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
static constexpr uint32_t HAL_WRAPPERS_MAX_FILTER_BANKS {28U};
static constexpr uint32_t HAL_WRAPPERS_FILTER_BANKS_PER_BUS {HAL_WRAPPERS_MAX_FILTER_BANKS / 2U};
static constexpr uint32_t HAL_WRAPPERS_FILTERS_PER_BANK {4U};
static constexpr uint32_t HAL_WRAPPERS_FILTERS_PER_BUS {HAL_WRAPPERS_FILTERS_PER_BANK * HAL_WRAPPERS_FILTER_BANKS_PER_BUS};

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
using Gpio_Id = uint16_t;
using Pwm_Ch = uint32_t;

enum HalWrappers_Tim_Int_E
{
    TIM_INT_CH_1,
    TIM_INT_CH_2,
    TIM_INT_CH_3,
    TIM_INT_CH_4,
    MAX_NUM_TIM_INT_CH
};

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

struct HalWrappers_Uart_Info_S
{
    HalWrappers_Gpio_E rxPin;
    HalWrappers_Gpio_E txPin;
    void (* txCompleteCallback)(UART_HandleTypeDef * huart);
    void (* notifyCallback)(UART_HandleTypeDef * huart);
};

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// GPIO
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_GPIO == 1)
class HalWrappersGpio
{
    public:
        constexpr HalWrappersGpio(
                const HalWrappers_Gpio_Info_S (&gpioInfo)[MAX_NUM_GPIO]
            ) :
                m_gpioInfo(gpioInfo)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersGpio);

        void GpioSet(const HalWrappers_Gpio_E gpio, const bool level);
        void GpioToggle(const HalWrappers_Gpio_E gpio);
        bool GpioRead(const HalWrappers_Gpio_E gpio);
        void GpioInitConfigPin(const HalWrappers_Gpio_E gpio);
        void GpioDeinitConfigPin(const HalWrappers_Gpio_E gpio);

    private:
        const HalWrappers_Gpio_Info_S (&m_gpioInfo)[MAX_NUM_GPIO];
};
#endif

//--------------------------------------------------------------------------------------------------
// PWM
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_PWM == 1)
class HalWrappersPwm
{
    public:
        constexpr HalWrappersPwm(
                TIM_HandleTypeDef * pPwmTim,
                const HalWrappers_Pwm_Info_S (&pwmInfo)[MAX_NUM_PWM]
            ) :
                m_pPwmTim(pPwmTim),
                m_pwmInfo(pwmInfo)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersPwm);

        void PwmSet(const HalWrappers_Pwm_E pwm, const float dutyCycle);

    private:
        TIM_HandleTypeDef * m_pPwmTim;
        const HalWrappers_Pwm_Info_S (&m_pwmInfo)[MAX_NUM_PWM];
};
#endif

//--------------------------------------------------------------------------------------------------
// ADC
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_ADC == 1)
class HalWrappersAdc
{
    public:
        constexpr HalWrappersAdc(
                ADC_HandleTypeDef * pAdc,
                const HalWrappers_Adc_Info_S (&adcInfo)[MAX_NUM_ANALOG]
            ) :
                m_pAdc(pAdc),
                m_adcInfo(adcInfo)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersAdc);

        void AdcTriggerStart(void);
        bool AdcGetFinished(void);
        float_q AdcGetValue(const HalWrappers_Analog_E adc);
        void AdcProcessConversion(void);

    private:
        ADC_HandleTypeDef * m_pAdc;
        const HalWrappers_Adc_Info_S (&m_adcInfo)[MAX_NUM_ANALOG];

        float_q m_adcValues[MAX_NUM_ANALOG] {};
        HalWrappers_Analog_E m_adcToPoll {MAX_NUM_ANALOG};

        void AdcStartConversion(const HalWrappers_Analog_E adc);
};
#endif

//--------------------------------------------------------------------------------------------------
// CAN
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_CAN == 1)
class HalWrappersCan
{
    public:
        constexpr HalWrappersCan(
                CAN_HandleTypeDef * (&pCan)[MAX_NUM_CAN]
            ) :
                m_pCan(pCan)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersCan);

        void CanRegisterRxFilter(const HalWrappers_Can_E can, const uint32_t mid);
        void CanSetRxFilters(const HalWrappers_Can_E can);
        void CanStart(const HalWrappers_Can_E can);
        void CanTransmit(const HalWrappers_Can_E can, const uint32_t mid, const uint32_t dlc, const uint8_t * const pData);

    private:
        struct HalWrappers_Can_PendingRxFilter_S
        {
            uint16_t filt[HAL_WRAPPERS_FILTERS_PER_BANK];
            uint8_t currentFiltIdx;
        };

        CAN_HandleTypeDef * (&m_pCan)[MAX_NUM_CAN];

        HalWrappers_Can_PendingRxFilter_S m_pendingRxFilter[MAX_NUM_CAN] {};
        uint32_t m_filterBankIdx[MAX_NUM_CAN] {};
        bool m_useFifo1[MAX_NUM_CAN] {};
};
#endif

//--------------------------------------------------------------------------------------------------
// UART
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_UART == 1)
class HalWrappersUart
{
    public:
        constexpr HalWrappersUart(
                UART_HandleTypeDef * (&pUart)[MAX_NUM_UART],
                const HalWrappers_Uart_Info_S (&uartInfo)[MAX_NUM_UART]
            ) :
                m_pUart(pUart),
                m_uartInfo(uartInfo)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersUart);

        void UartSetGpio(const HalWrappers_Uart_E uart, const bool setToGpio, HalWrappersGpio& halGpio);
        bool UartTransmit(const HalWrappers_Uart_E uart, const uint8_t * const pTx, const uint32_t numBytes, const bool notify);
        bool UartReceive(const HalWrappers_Uart_E uart, uint8_t * const pRx, const uint32_t numBytes);
        bool UartWait(const HalWrappers_Uart_E uart, const uint32_t waitMs);
        void UartAbort(const HalWrappers_Uart_E uart);

        osThreadId UartGetTaskToNotify(const HalWrappers_Uart_E uart) { return m_taskToNotify[uart]; }

    private:
        UART_HandleTypeDef * (&m_pUart)[MAX_NUM_UART];
        const HalWrappers_Uart_Info_S (&m_uartInfo)[MAX_NUM_UART];

        osThreadId m_taskToNotify[MAX_NUM_UART] {};
};
#endif

//--------------------------------------------------------------------------------------------------
// Timer
//--------------------------------------------------------------------------------------------------
#if (FEATURE_HAL_WRAPPERS_TIMER == 1)
class HalWrappersTimer
{
    public:
        constexpr HalWrappersTimer(
                TIM_HandleTypeDef * pUsTim
            ) :
                m_pUsTim(pUsTim)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappersTimer);

        void TimerClearUs(void);
        uint32_t TimerGetUs(void);
        void TimerScheduleInt(HalWrappers_Tim_Int_E timInt, const uint32_t timeUs, void (* callback)(void));
        void TimerIrq(TIM_HandleTypeDef * htim);

    private:
        TIM_HandleTypeDef * m_pUsTim;
        void (* m_callback[MAX_NUM_TIM_INT_CH])(void);
};
#endif

} // namespace Shared

#endif // HAL_WRAPPERS_HPP
