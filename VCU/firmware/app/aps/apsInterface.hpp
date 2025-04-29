#ifndef APS_INTERFACE_HPP
#define APS_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "apsData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Vcu
{

class ApsInputInterface
{
    public:
        constexpr ApsInputInterface()
        {}

        NOCOPY_NOMOVE(ApsInputInterface);

        virtual float_q GetAps1AdcV(void) const = 0;
        virtual float_q GetAps2AdcV(void) const = 0;
        virtual float InterpAps1Pct(const float voltage) const = 0;
        virtual float InterpAps2Pct(const float voltage) const = 0;
};

class ApsOutputInterface
{
    public:
        constexpr ApsOutputInterface()
        {}

        NOCOPY_NOMOVE(ApsOutputInterface);

        virtual float_q GetAps1Frac(void) const = 0;
        virtual float_q GetAps2Frac(void) const = 0;
};

} // namespace Vcu

#endif // APS_INTERFACE_HPP
