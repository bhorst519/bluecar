#ifndef HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
#define HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.hpp"
#include "nocopy.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

using HalWrappersGpio = Shared::HalWrappersGpio;
using HalWrappersPwm = Shared::HalWrappersPwm;
using HalWrappersCan = Shared::HalWrappersCan;
using HalWrappersUart = Shared::HalWrappersUart;
using HalWrappersTimer = Shared::HalWrappersTimer;

using HalWrappers_Gpio_Info_S = Shared::HalWrappers_Gpio_Info_S;
using HalWrappers_Pwm_Info_S = Shared::HalWrappers_Pwm_Info_S;
using HalWrappers_Uart_Info_S = Shared::HalWrappers_Uart_Info_S;

class HalWrappers :   public HalWrappersGpio
                    , public HalWrappersPwm
                    , public HalWrappersCan
                    , public HalWrappersUart
                    , public HalWrappersTimer
{
    public:
        constexpr HalWrappers(
                  HalWrappers_Config_S& config
                , const HalWrappers_Gpio_Info_S (&gpioInfo)[MAX_NUM_GPIO]
                , const HalWrappers_Pwm_Info_S (&pwmInfo)[MAX_NUM_PWM]
                , const HalWrappers_Uart_Info_S (&uartInfo)[MAX_NUM_UART]
            ) :
                  HalWrappersGpio(gpioInfo)
                , HalWrappersPwm(config.pPwmTim, pwmInfo)
                , HalWrappersCan(config.pCan)
                , HalWrappersUart(config.pUart, uartInfo)
                , HalWrappersTimer(config.pUsTim)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappers);

        void Init(void);

        void UartSetGpio(const HalWrappers_Uart_E uart, const bool setToGpio)
        {
            Shared::HalWrappersUart::UartSetGpio(uart, setToGpio, *this);
        }
};

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers gHalWrappers;

} // namespace Eim

#endif // HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
