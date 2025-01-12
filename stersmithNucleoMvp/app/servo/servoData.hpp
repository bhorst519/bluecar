#ifndef SERVO_DATA_HPP
#define SERVO_DATA_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

struct ServoData_S
{
    uint8_t id;
    float positionDegrees;
    float lossOfCommPositionDegrees;
    float lossOfCommTimeout;
    float current;
    float temperature;
    float voltage;
};

} // namespace Eim

#endif // SERVO_DATA_HPP
