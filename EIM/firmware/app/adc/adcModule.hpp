#ifndef ADC_MODULE_HPP
#define ADC_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcInterface.hpp"
#include "filter.hpp"
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "qualifiedValTypes.hpp"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

using Lpf1stFloat = Filter::Lpf1st<float, float>;

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
class AdcModule final : public Shared::ModuleBase
{
    public:
        constexpr AdcModule(
            ) :
                ModuleBase()
        {}

        NOCOPY_NOMOVE(AdcModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const AdcData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        AdcData_S m_outputData {};

        // Time constant of 0.05s with sampling of 0.01s
        Filter::Arr<Lpf1stFloat, NUM_ADC> m_adcFilt10Hz {
            Lpf1stFloat::ComputeCoeffs(0.05F, 0.01F)
        };
};

} // namespace Eim

#endif // ADC_MODULE_HPP
