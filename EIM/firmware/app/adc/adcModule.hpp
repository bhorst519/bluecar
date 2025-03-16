#ifndef ADC_MODULE_HPP
#define ADC_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcInterface.hpp"
#include "moduleBase.hpp"
#include "nocopy.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

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
};

} // namespace Eim

#endif // ADC_MODULE_HPP
