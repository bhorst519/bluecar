#ifndef QUALIFIED_VAL_TYPES_HPP
#define QUALIFIED_VAL_TYPES_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "qualifiedVal.hpp"
#include "util.h"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

using SignalStatus_E = Shared::SignalStatus_E;
template<typename T>
using QualifiedVal = Shared::QualifiedVal<T>;

typedef QualifiedVal<float> float_q;

typedef QualifiedVal<uint8_t>  uint8_q;
typedef QualifiedVal<uint16_t> uint16_q;
typedef QualifiedVal<uint32_t> uint32_q;

typedef QualifiedVal<int8_t>  int8_q;
typedef QualifiedVal<int16_t> int16_q;
typedef QualifiedVal<int32_t> int32_q;

} // namespace Eim

#endif // QUALIFIED_VAL_TYPES_HPP
