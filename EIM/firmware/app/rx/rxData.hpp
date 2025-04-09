#ifndef RX_DATA_HPP
#define RX_DATA_HPP

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

struct Rx100HzData_S
{
    uint8_q brakeLightEn;
    uint8_q headlightEn;
    uint8_q highBeamEn;
    uint8_q hornEn;
    uint8_q mainRelayEn;
    uint8_q turnRightEn;
    uint8_q turnLeftEn;
};

struct Rx10HzData_S
{
    float_q servoPositionRequest;
};

} // namespace Eim

#endif // RX_DATA_HPP
