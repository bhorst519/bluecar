#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include <cmath>

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/
namespace MathUtil
{

template <typename T>
constexpr T Saturate(const T val, const T min, const T max)
{
    return
        /* if */ (val > max) ? max
        /* else if */ : (val < min) ? min
        /* else */ : val;
}

template <typename T>
constexpr T IsWithinRange(const T a, const T b, const T range)
{
    return std::abs(a - b) <= range;
}

} // namespace MathUtil

#endif  // MATH_UTIL_HPP
