#ifndef IO_INT_MODULE_HPP
#define IO_INT_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntInterface.hpp"
#include "moduleBase.hpp"
#include "nocopy.hpp"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

class IoIntModule final : public Shared::ModuleBase
{
    public:
        constexpr IoIntModule(
                const IoIntInputInterface& inputRef
            ) :
                ModuleBase(),
                m_inputData(inputRef)
        {}

        NOCOPY_NOMOVE(IoIntModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const IoIntData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        const IoIntInputInterface& m_inputData;

        IoIntData_S m_outputData {};
};

} // namespace Eim

#endif // IO_INT_MODULE_HPP
