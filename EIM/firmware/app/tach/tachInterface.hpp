#ifndef TACH_INTERFACE_HPP
#define TACH_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "tachData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class TachOutputInterface
{
    public:
        constexpr TachOutputInterface()
        {}

        NOCOPY_NOMOVE(TachOutputInterface);

        virtual float_q GetFreq(void) const = 0;
        virtual float_q GetRpm(void) const = 0;
};

} // namespace Eim

#endif // TACH_INTERFACE_HPP
