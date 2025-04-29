#ifndef ADC_INTERFACE_HPP
#define ADC_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "adcData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class AdcOutputInterface
{
    public:
        constexpr AdcOutputInterface()
        {}

        NOCOPY_NOMOVE(AdcOutputInterface);

        virtual float_q GetAdcFilt10Hz(const HalWrappers_Analog_E adc) const = 0;
};

} // namespace Vcu

#endif // ADC_INTERFACE_HPP
