#ifndef CAN_MODULE_HPP
#define CAN_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class CanModule final : public Shared::ModuleBase
{
    public:
        constexpr CanModule(
            ) :
                ModuleBase()
        {}

        NOCOPY_NOMOVE(CanModule);

        virtual void Init(void) override;
        virtual void Run(void) override;
};

} // namespace Vcu

#endif // CAN_MODULE_HPP
