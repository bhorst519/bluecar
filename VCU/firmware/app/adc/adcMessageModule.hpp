#ifndef ADC_MESSAGE_MODULE_HPP
#define ADC_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class AdcMessageModule final : public AdcOutputInterface
{
    private:
        const AdcData_S& m_dataRef;

    public:
        constexpr AdcMessageModule(
                const AdcData_S& dataRef
            ) :
                AdcOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(AdcMessageModule);

        virtual float_q GetAdcFilt10Hz(const HalWrappers_Analog_E adc) const override
        {
            return m_dataRef.adcFilt10Hz[adc];
        }
};

} // namespace Vcu

#endif // ADC_MESSAGE_MODULE_HPP
