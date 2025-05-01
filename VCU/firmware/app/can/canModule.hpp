#ifndef CAN_MODULE_HPP
#define CAN_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "moduleBase.hpp"
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Vcu
{

struct CanModule_Mux_Transmitter_S
{
    uint32_t periodMs;
    uint32_t numMuxes;
    uint32_t counter;
};

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
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

    private:
        CanModule_Mux_Transmitter_S m_muxTransmit_VCU_CpuStats {};
        CanModule_Mux_Transmitter_S m_muxTransmit_VCU_PcbaVitals {};

        bool ShouldTransmitMuxNow(CanModule_Mux_Transmitter_S& mux, uint32_t& muxIdx) const;
};

} // namespace Vcu

#endif // CAN_MODULE_HPP
