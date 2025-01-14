#ifndef SERVO_DATA_HPP
#define SERVO_DATA_HPP

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

struct ServoData_S
{
    uint8_t id;
    float_q positionDegrees;
    float_q lossOfCommPositionDegrees;
    float_q lossOfCommTimeout;
    float_q current;
    float_q temperature;
    float_q voltage;
};

} // namespace Eim

#endif // SERVO_DATA_HPP
