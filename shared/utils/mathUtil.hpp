#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

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

} // namespace MathUtil

#endif  // MATH_UTIL_HPP
