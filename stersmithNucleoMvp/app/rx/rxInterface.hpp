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

class Rx10HzOutputInterface
{
    public:
        constexpr Rx10HzOutputInterface()
        {}

        NOCOPY_NOMOVE(Rx10HzOutputInterface);

        virtual float_q GetServoPositionRequest(void) const = 0;
};

} // namespace Eim

#endif // RX_INTERFACE_HPP
