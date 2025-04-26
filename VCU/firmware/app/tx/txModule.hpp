#ifndef TX_MODULE_HPP
#define TX_MODULE_HPP

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

class TxNoneModule final : public Shared::TxModuleBase
{
    public:
        constexpr TxNoneModule(
            ) :
                TxModuleBase()
        {}

        NOCOPY_NOMOVE(TxNoneModule);

        virtual void Transmit(void) override;
};

} // namespace Vcu

#endif // TX_MODULE_HPP
