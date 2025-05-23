#ifndef KLINE_DATA_HPP
#define KLINE_DATA_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "qualifiedVal.hpp"
#include "util.h"

using namespace ::QualifiedVal;

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Shared
{

struct KlineData_S
{
    uint16_q rpm;
    float_q batteryVoltage;
    float_q vehicleSpeed;
    // Throttle position sensor
    float_q tpsVoltage;
    float_q tpsAngle;
    // Engine coolant temp sensor
    float_q ectVoltage;
    float_q ectTemp;
    // Intake air temp sensor
    float_q iatVoltage;
    float_q iatTemp;
    // Manifold absolute pressure sensor
    float_q mapVoltage;
    float_q mapPressure;
};

} // namespace Shared

#endif // KLINE_DATA_HPP
