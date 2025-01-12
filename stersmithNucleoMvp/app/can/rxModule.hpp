#ifndef RX_MODULE_HPP
#define RX_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class RxNoneModule final : public Shared::RxModuleBase
{
    public:
        constexpr RxNoneModule(
            ) :
                RxModuleBase()
        {}

        NOCOPY_NOMOVE(RxNoneModule);

        virtual void Receive(void) override;
};

} // namespace Eim

#endif // RX_MODULE_HPP
