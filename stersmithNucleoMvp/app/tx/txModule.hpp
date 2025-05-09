#ifndef TX_MODULE_HPP
#define TX_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "klineInterface.hpp"
#include "moduleBase.hpp"
#include "servoInterface.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
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

class Tx10HzModule final : public Shared::TxModuleBase
{
    using ServoOutputInterface = Shared::ServoOutputInterface;

    public:
        constexpr Tx10HzModule(
                const ServoOutputInterface& servoRef
            ) :
                TxModuleBase(),
                m_servoRef(servoRef)
        {}

        NOCOPY_NOMOVE(Tx10HzModule);

        virtual void Transmit(void) override;

    private:
        const ServoOutputInterface& m_servoRef;
};

class Tx1HzModule final : public Shared::TxModuleBase
{
    using KlineOutputInterface = Shared::KlineOutputInterface;

    public:
        constexpr Tx1HzModule(
                const KlineOutputInterface& klineRef
            ) :
                TxModuleBase(),
                m_klineRef(klineRef)
        {}

        NOCOPY_NOMOVE(Tx1HzModule);

        virtual void Transmit(void) override;

    private:
        const KlineOutputInterface& m_klineRef;
};

} // namespace Eim

#endif // TX_MODULE_HPP
