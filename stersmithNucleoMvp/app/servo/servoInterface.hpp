#ifndef SERVO_INTERFACE_HPP
#define SERVO_INTERFACE_HPP

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

class ServoInputInterface
{
    public:
        constexpr ServoInputInterface()
        {}

        NOCOPY_NOMOVE(ServoInputInterface);

        virtual float GetLossOfCommPositionDegreesToSet(void) const = 0;
        virtual float GetLossOfCommTimeoutToSet(void) const = 0;
        virtual float GetPositionDegreesToSet(void) const = 0;
};

class ServoOutputInterface
{
    public:
        constexpr ServoOutputInterface()
        {}

        NOCOPY_NOMOVE(ServoOutputInterface);

        virtual float GetCurrent(void) const = 0;
        virtual uint8_t GetId(void) const = 0;
        virtual float GetLossOfCommPositionDegrees(void) const = 0;
        virtual float GetLossOfCommTimeout(void) const = 0;
        virtual float GetPositionDegrees(void) const = 0;
        virtual float GetTemperature(void) const = 0;
        virtual float GetVoltage(void) const = 0;
};

} // namespace Eim

#endif // SERVO_INTERFACE_HPP
