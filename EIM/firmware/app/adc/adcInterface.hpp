#ifndef ADC_INTERFACE_HPP
#define ADC_INTERFACE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "nocopy.hpp"
#include "adcData.hpp"
#include "util.h"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class AdcOutputInterface
{
    public:
        constexpr AdcOutputInterface()
        {}

        NOCOPY_NOMOVE(AdcOutputInterface);
};

} // namespace Eim

#endif // ADC_INTERFACE_HPP
