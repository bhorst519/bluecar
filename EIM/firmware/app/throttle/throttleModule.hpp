#ifndef THROTTLE_MODULE_HPP
#define THROTTLE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "nocopy.hpp"
#include "throttleInterface.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class ThrottleModule final : public Shared::ModuleBase
{
    public:
        constexpr ThrottleModule(
                const ThrottleInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(ThrottleModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const ThrottleData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const ThrottleInputInterface& m_inputData;

        ThrottleData_S m_outputData {};
};

} // namespace Eim

#endif // THROTTLE_MODULE_HPP
