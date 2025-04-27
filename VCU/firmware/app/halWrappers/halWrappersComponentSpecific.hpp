#ifndef HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
#define HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.hpp"
#include "nocopy.hpp"
#include "profiler.h"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Vcu
{

using HalWrappersGpio = Shared::HalWrappersGpio;
using HalWrappersAdc = Shared::HalWrappersAdc;
using HalWrappersCan = Shared::HalWrappersCan;
using HalWrappersTimer = Shared::HalWrappersTimer;

using HalWrappers_Tim_Int_E = Shared::HalWrappers_Tim_Int_E;
using HalWrappers_Gpio_Info_S = Shared::HalWrappers_Gpio_Info_S;
using HalWrappers_Adc_Info_S = Shared::HalWrappers_Adc_Info_S;

class HalWrappers :   public HalWrappersGpio
                    , public HalWrappersAdc
                    , public HalWrappersCan
                    , public HalWrappersTimer
{
    public:
        constexpr HalWrappers(
                  HalWrappers_Config_S& config
                , const HalWrappers_Gpio_Info_S (&gpioInfo)[MAX_NUM_GPIO]
                , const HalWrappers_Adc_Info_S (&adcInfo)[MAX_NUM_ANALOG]
            ) :
                  HalWrappersGpio(gpioInfo)
                , HalWrappersAdc(config.pAdc, adcInfo)
                , HalWrappersCan(config.pCan)
                , HalWrappersTimer(config.pUsTim)
        {}

        NODEFAULT_NOCOPY_NOMOVE(HalWrappers);

        void Init(void);

        void AdcTriggerStart(void)
        {
            ProfilerCheckIn(PROFILER_ADC_CONV);
            Shared::HalWrappersAdc::AdcTriggerStart();
        }
};

/***************************************************************************************************
*                          P U B L I C   D A T A   D E F I N I T I O N S                           *
***************************************************************************************************/
extern HalWrappers gHalWrappers;

} // namespace Vcu

#endif // HAL_WRAPPERS_COMPONENT_SPECIFIC_HPP
