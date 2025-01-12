#ifndef KLINE_DATA_HPP
#define KLINE_DATA_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

struct KlineData_S
{
    uint16_t rpm;
    float batteryVoltage;
    float vehicleSpeed;
    // Throttle position sensor
    float tpsVoltage;
    float tpsAngle;
    // Engine coolant temp sensor
    float ectVoltage;
    float ectTemp;
    // Intake air temp sensor
    float iatVoltage;
    float iatTemp;
    // Manifold absolute pressure sensor
    float mapVoltage;
    float mapPressure;
};

} // namespace Eim

#endif // KLINE_DATA_HPP
