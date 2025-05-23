#ifndef HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
#define HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.hpp"
#include "klineInterface.hpp"
#include "nocopy.hpp"
#include "profiler.h"
#include "servoInterface.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

using HalWrappersGpio = Shared::HalWrappersGpio;
using HalWrappersPwm = Shared::HalWrappersPwm;
using HalWrappersAdc = Shared::HalWrappersAdc;
using HalWrappersCan = Shared::HalWrappersCan;
using HalWrappersUart = Shared::HalWrappersUart;
using HalWrappersTimer = Shared::HalWrappersTimer;

using HalWrappers_Tim_Int_E = Shared::HalWrappers_Tim_Int_E;
using HalWrappers_Gpio_Info_S = Shared::HalWrappers_Gpio_Info_S;
using HalWrappers_Pwm_Info_S = Shared::HalWrappers_Pwm_Info_S;
using HalWrappers_Adc_Info_S = Shared::HalWrappers_Adc_Info_S;
using HalWrappers_Uart_Info_S = Shared::HalWrappers_Uart_Info_S;

using KlineIoInterface = Shared::KlineIoInterface;
using ServoIoInterface = Shared::ServoIoInterface;

class HalWrappers :   public HalWrappersGpio
                    , public HalWrappersPwm
                    , public HalWrappersAdc
                    , public HalWrappersCan
                    , public HalWrappersUart
                    , public HalWrappersTimer
                    , public KlineIoInterface
                    , public ServoIoInterface
{
    public:
        constexpr HalWrappers(
                  HalWrappers_Config_S& config
                , const HalWrappers_Gpio_Info_S (&gpioInfo)[MAX_NUM_GPIO]
                , const HalWrappers_Pwm_Info_S (&pwmInfo)[MAX_NUM_PWM]
                , const HalWrappers_Adc_Info_S (&adcInfo)[MAX_NUM_ANALOG]
                , const HalWrappers_Uart_Info_S (&uartInfo)[MAX_NUM_UART]
            ) :
                  HalWrappersGpio(gpioInfo)
                , HalWrappersPwm(config.pPwmTim, pwmInfo)
                , HalWrappersAdc(config.pAdc, adcInfo)
                , HalWrappersCan(config.pCan)
                , HalWrappersUart(config.pUart, uartInfo)
                , HalWrappersTimer(config.pUsTim)
                , KlineIoInterface()
                , ServoIoInterface()
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappers);

        void Init(void);

        void AdcTriggerStart(void)
        {
            ProfilerCheckIn(PROFILER_ADC_CONV);
            Shared::HalWrappersAdc::AdcTriggerStart();
        }

        void UartSetGpio(const HalWrappers_Uart_E uart, const bool setToGpio)
        {
            Shared::HalWrappersUart::UartSetGpio(uart, setToGpio, *this);
        }

        // KlineIoInterface
        virtual HalWrappers_Uart_E GetKlineUart(void) const override
        {
            return UART_KLINE;
        }

        virtual void SetKlineTxPin(const bool level) override
        {
            GpioSet(GPIO_KLINE_TX, level);
        }

        virtual void SetKlineUartGpio(const bool setToGpio) override
        {
            UartSetGpio(UART_KLINE, setToGpio);
        }

        virtual void UartEnableKlineTransmit(void) override
        {
            GpioSet(GPIO_KLINE_EN, true);
        }

        // ServoIoInterface
        virtual HalWrappers_Uart_E GetServoUart(void) const override
        {
            return UART_SERVO;
        }

        virtual void UartEnableServoTransmit(void) override
        {
            GpioSet(GPIO_SERVO_COMM_DIR, true);
        }
};

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers gHalWrappers;

} // namespace Eim

#endif // HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
