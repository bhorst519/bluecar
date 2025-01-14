#ifndef KLINE_INTERFACE_HPP
#define KLINE_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "klineData.hpp"
#include "nocopy.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class KlineOutputInterface
{
    public:
        constexpr KlineOutputInterface()
        {}

        NOCOPY_NOMOVE(KlineOutputInterface);

        virtual float_q GetBatteryVoltage(void) const = 0;
        virtual float_q GetEctTemp(void) const = 0;
        virtual float_q GetEctVoltage(void) const = 0;
        virtual float_q GetIatTemp(void) const = 0;
        virtual float_q GetIatVoltage(void) const = 0;
        virtual float_q GetMapPressure(void) const = 0;
        virtual float_q GetMapVoltage(void) const = 0;
        virtual uint16_q GetRpm(void) const = 0;
        virtual float_q GetTpsAngle(void) const = 0;
        virtual float_q GetTpsVoltage(void) const = 0;
        virtual float_q GetVehicleSpeed(void) const = 0;
};

} // namespace Eim

#endif // KLINE_INTERFACE_HPP
