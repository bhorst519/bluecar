#ifndef APS_MODULE_HPP
#define APS_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "apsInterface.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Vcu
{

class ApsModule final : public Shared::ModuleBase
{
    public:
        constexpr ApsModule(
                const ApsInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(ApsModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const ApsData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const ApsInputInterface& m_inputData;

        ApsData_S m_outputData {};
};

} // namespace Vcu

#endif // APS_MODULE_HPP
