#ifndef RX_INTERFACE_HPP
#define RX_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "rxData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class Rx100HzOutputInterface
{
    public:
        constexpr Rx100HzOutputInterface()
        {}

        NOCOPY_NOMOVE(Rx100HzOutputInterface);

        virtual uint8_q GetBrakeLightEn(void) const = 0;
        virtual uint8_q GetEngineOnEn(void) const = 0;
        virtual uint8_q GetEngineStartEn(void) const = 0;
        virtual uint8_q GetHeadlightEn(void) const = 0;
        virtual uint8_q GetHighBeamEn(void) const = 0;
        virtual uint8_q GetMainRelayEn(void) const = 0;
        virtual uint8_q GetHornEn(void) const = 0;
        virtual uint8_q GetTurnLeftEn(void) const = 0;
        virtual uint8_q GetTurnRightEn(void) const = 0;
};

class Rx10HzOutputInterface
{
    public:
        constexpr Rx10HzOutputInterface()
        {}

        NOCOPY_NOMOVE(Rx10HzOutputInterface);

        virtual float_q GetApsFrac(void) const = 0;
        virtual float_q GetServoPositionRequest(void) const = 0;
};

} // namespace Eim

#endif // RX_INTERFACE_HPP
