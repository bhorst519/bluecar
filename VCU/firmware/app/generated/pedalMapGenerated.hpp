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
// Exponent p = 1.5
// Order N = 6
// Point of approximation a = 0.75

static constexpr float PEDAL_MAP_POINT_A { 0.75F };
static constexpr size_t PEDAL_MAP_ODER_N { 6U };
static constexpr float PEDAL_MAP_COEFFS[PEDAL_MAP_ODER_N + 1U] = {
    0.649519052838329F,
    1.299038105676658F,
    0.4330127018922193F,
    -0.09622504486493762F,
    0.04811252243246881F,
    -0.032075014954979206F,
    0.02494723385387272F,
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
