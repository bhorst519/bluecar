#ifndef SERVO_INTERFACE_HPP
#define SERVO_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "servoData.hpp"
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

        virtual float_q GetCurrent(void) const = 0;
        virtual uint8_t GetId(void) const = 0;
        virtual float_q GetLossOfCommPositionDegrees(void) const = 0;
        virtual float_q GetLossOfCommTimeout(void) const = 0;
        virtual float_q GetPositionDegrees(void) const = 0;
        virtual float_q GetTemperature(void) const = 0;
        virtual float_q GetVoltage(void) const = 0;
};

} // namespace Eim

#endif // SERVO_INTERFACE_HPP
