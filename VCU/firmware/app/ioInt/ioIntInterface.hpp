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
namespace Vcu
{

class IoIntOutputInterface
{
    public:
        constexpr IoIntOutputInterface()
        {}

        NOCOPY_NOMOVE(IoIntOutputInterface);

        virtual bool GetBrakeSwitch(void) const = 0;
        virtual bool GetEngineEnable(void) const = 0;
        virtual bool GetEngineStart(void) const = 0;
        virtual bool GetUserSwitch(void) const = 0;
};

} // namespace Vcu

#endif // IO_INT_INTERFACE_HPP
