#ifndef IO_INT_DATA_HPP
#define IO_INT_DATA_HPP

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

enum class GearSelect_E
{
    NEUTRAL     = 0U,
    FIRST       = 1U,
    SECOND      = 2U,
    THIRD       = 3U,
    FOURTH      = 4U,
    FIFTH       = 5U,
    SIXTH       = 6U,
    MAX,
    ERROR       = GearSelect_E::MAX
};
static constexpr uint8_t MAX_NUM_GEAR_SELECT {static_cast<uint8_t>(GearSelect_E::MAX)};

struct IoIntData_S
{
    bool turnRight;
    bool turnLeft;
    bool lowBeam;
    bool highBeam;
    bool faultIndicator;
    bool oilPressureLow;
    bool gearN;
    bool gear1;
    bool gear2;
    bool gear3;
    bool gear4;
    bool gear5;
    bool gear6;
    GearSelect_E gearSelect;
};

} // namespace Eim

#endif // IO_INT_DATA_HPP
