#ifndef IO_INT_INTERFACE_HPP
#define IO_INT_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntData.hpp"
#include "nocopy.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class IoIntInputInterface
{
    public:
        constexpr IoIntInputInterface()
        {}

        NOCOPY_NOMOVE(IoIntInputInterface);

        virtual uint8_q GetBrakeLightEn(void) const = 0;
        virtual uint8_q GetHeadlightEn(void) const = 0;
        virtual uint8_q GetHighBeamEn(void) const = 0;
        virtual uint8_q GetHornEn(void) const = 0;
        virtual uint8_q GetMainRelayEn(void) const = 0;
        virtual uint8_q GetTurnLeftEn(void) const = 0;
        virtual uint8_q GetTurnRightEn(void) const = 0;
};

class IoIntOutputInterface
{
    public:
        constexpr IoIntOutputInterface()
        {}

        NOCOPY_NOMOVE(IoIntOutputInterface);

        virtual bool GetGearN(void) const = 0;
        virtual bool GetGear1(void) const = 0;
        virtual bool GetGear2(void) const = 0;
        virtual bool GetGear3(void) const = 0;
        virtual bool GetGear4(void) const = 0;
        virtual bool GetGear5(void) const = 0;
        virtual bool GetGear6(void) const = 0;
        virtual GearSelect_E GetGearSelect(void) const = 0;
};

} // namespace Eim

#endif // IO_INT_INTERFACE_HPP
