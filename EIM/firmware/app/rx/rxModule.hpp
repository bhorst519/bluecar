#ifndef RX_MODULE_HPP
#define RX_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "rxInterface.hpp"
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

class Rx100HzModule final : public Shared::RxModuleBase
{
    public:
        constexpr Rx100HzModule(
            ) :
                RxModuleBase()
        {}

        NOCOPY_NOMOVE(Rx100HzModule);

        virtual void Receive(void) override;
        constexpr const Rx100HzData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        Rx100HzData_S m_outputData {};
};

class Rx10HzModule final : public Shared::RxModuleBase
{
    public:
        constexpr Rx10HzModule(
            ) :
                RxModuleBase()
        {}

        NOCOPY_NOMOVE(Rx10HzModule);

        virtual void Receive(void) override;
        constexpr const Rx10HzData_S& GetOutputDataReference(void) const { return m_outputData; };

    private:
        Rx10HzData_S m_outputData {};
};

} // namespace Eim

#endif // RX_MODULE_HPP
