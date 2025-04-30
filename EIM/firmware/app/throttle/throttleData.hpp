#ifndef THROTTLE_DATA_HPP
#define THROTTLE_DATA_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "qualifiedValTypes.hpp"
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

struct ThrottleData_S
{
    float idleThrottlePosDegrees;
    float_q throttlePosRequestDegrees;
};

} // namespace Eim

#endif // THROTTLE_DATA_HPP
