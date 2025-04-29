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
namespace Vcu
{

class IoIntModule final : public Shared::ModuleBase
{
    public:
        constexpr IoIntModule(
            ) :
                ModuleBase()
        {}

        NOCOPY_NOMOVE(IoIntModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
        constexpr const IoIntData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        IoIntData_S m_outputData {};
};

} // namespace Vcu

#endif // IO_INT_MODULE_HPP
