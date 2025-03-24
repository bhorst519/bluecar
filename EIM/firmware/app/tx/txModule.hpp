#ifndef TX_MODULE_HPP
#define TX_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcInterface.hpp"
#include "ioIntInterface.hpp"
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

class Tx100HzModule final : public Shared::TxModuleBase
{
    public:
        constexpr Tx100HzModule(
                const AdcOutputInterface& adcRef,
                const IoIntOutputInterface& ioIntRef
            ) :
                TxModuleBase(),
                m_adcRef(adcRef),
                m_ioIntRef(ioIntRef)
        {}

        NOCOPY_NOMOVE(Tx100HzModule);

        virtual void Transmit(void) override;

    private:
        const AdcOutputInterface& m_adcRef;
        const IoIntOutputInterface& m_ioIntRef;
};

class Tx10HzModule final : public Shared::TxModuleBase
{
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
