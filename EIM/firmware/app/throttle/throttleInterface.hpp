#ifndef THROTTLE_INTERFACE_HPP
#define THROTTLE_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "throttleData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class ThrottleInputInterface
{
    public:
        constexpr ThrottleInputInterface()
        {}

        NOCOPY_NOMOVE(ThrottleInputInterface);

        virtual float_q GetApsFrac(void) const = 0;
        virtual float InterpThrottlePosDegrees(const float frac) const = 0;
};

class ThrottleOutputInterface
{
    public:
        constexpr ThrottleOutputInterface()
        {}

        NOCOPY_NOMOVE(ThrottleOutputInterface);

        virtual float GetIdleThrottlePosDegrees(void) const = 0;
        virtual float_q GetThrottlePosRequestDegrees(void) const = 0;
};

} // namespace Eim

#endif // THROTTLE_INTERFACE_HPP
