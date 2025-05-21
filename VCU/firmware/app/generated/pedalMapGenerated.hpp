#ifndef PEDAL_MAP_GENERATED_HPP
#define PEDAL_MAP_GENERATED_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace PedalMap
{

// Taylor series for power function
// Exponent p = 1.3
// Order N = 6
// Point of approximation a = 0.5

static constexpr float PEDAL_MAP_POINT_A { 0.5F };
static constexpr size_t PEDAL_MAP_ODER_N { 6U };
static constexpr float PEDAL_MAP_COEFFS[PEDAL_MAP_ODER_N + 1U] = {
    0.40612619817811774F,
    1.0559281152631061F,
    0.3167784345789319F,
    -0.14782993613683487F,
    0.12565544571630965F,
    -0.13570788137361445F,
    0.16737305369412447F,
};

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/
float GetPedalPositionMapped(const float pedalPosition)
{
    const float xa = (pedalPosition - PEDAL_MAP_POINT_A);
    float xaLoop = 1.0F;

    float pedalPositionMapped = PEDAL_MAP_COEFFS[0U];
    for (size_t i = 0; i < PEDAL_MAP_ODER_N; ++i)
    {
        xaLoop = xaLoop * xa;
        pedalPositionMapped += PEDAL_MAP_COEFFS[i + 1U] * xaLoop;
    }

    return pedalPositionMapped;
}

} // namespace PedalMap

#endif // PEDAL_MAP_GENERATED_HPP
