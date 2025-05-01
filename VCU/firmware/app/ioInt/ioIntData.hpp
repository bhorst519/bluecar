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
namespace Vcu
{

struct IoIntData_S
{
    bool brakeSwitch;
    bool engineEnable;
    bool engineStart;
    bool userSwitch;
};

} // namespace Vcu

#endif // IO_INT_DATA_HPP
