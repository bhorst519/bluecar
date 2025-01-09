#ifndef KLINE_INTERFACE_HPP
#define KLINE_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
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

        virtual float GetBatteryVoltage(void) const = 0;
        virtual float GetEctTemp(void) const = 0;
        virtual float GetEctVoltage(void) const = 0;
        virtual float GetIatTemp(void) const = 0;
        virtual float GetIatVoltage(void) const = 0;
        virtual float GetMapPressure(void) const = 0;
        virtual float GetMapVoltage(void) const = 0;
        virtual uint16_t GetRpm(void) const = 0;
        virtual float GetTpsAngle(void) const = 0;
        virtual float GetTpsVoltage(void) const = 0;
        virtual float GetVehicleSpeed(void) const = 0;
};

} // namespace Eim

#endif // KLINE_INTERFACE_HPP
