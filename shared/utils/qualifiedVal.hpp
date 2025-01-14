#ifndef QUALIFIED_VAL_HPP
#define QUALIFIED_VAL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define COMPARE_OVERLOAD(op)    friend constexpr bool operator op(const QualifiedVal lhs,\
                                                                  const QualifiedVal rhs)\
                                {\
                                    return (lhs.m_val op rhs.m_val);\
/*                              }\
                                friend constexpr bool operator op(const T lhs,\
                                                                  const QualifiedVal rhs)\
                                {\
                                    return (lhs op rhs.m_val);\
                                }\
                                friend constexpr bool operator op(const QualifiedVal lhs,\
                                                                  const T rhs)\
                                {\
                                    return (lhs.m_val op rhs);\
*/                              }

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace QualifiedVal
{

enum class SignalStatus_E
{
    SNA,
    BAD,
    VALID,
};

template<typename T>
struct QualifiedVal
{
    public:
        T m_val;
        SignalStatus_E m_status;

        QualifiedVal() =default;

        constexpr explicit QualifiedVal(
                const T& val,
                const SignalStatus_E& status
            ) :
                m_val(val),
                m_status(status)
        {}

        constexpr explicit QualifiedVal(
                const T& val
            ) :
                m_val(val),
                m_status(SignalStatus_E::SNA)
        {}

        //------------------------------------------------------------------------------------------
        // Operator overloads
        //------------------------------------------------------------------------------------------
        constexpr QualifiedVal& operator=(const T val)
        {
            m_val = val;
            return *this;
        }

        constexpr QualifiedVal& operator=(const SignalStatus_E status)
        {
            m_status = status;
            return *this;
        }

        constexpr operator T(void) const
        {
            return m_val;
        }

        COMPARE_OVERLOAD(==)
        COMPARE_OVERLOAD(!=)
        COMPARE_OVERLOAD(>=)
        COMPARE_OVERLOAD(>)
        COMPARE_OVERLOAD(<=)
        COMPARE_OVERLOAD(<)

        //------------------------------------------------------------------------------------------
        // Member functions
        //------------------------------------------------------------------------------------------
        constexpr T Val(void) const
        {
            return m_val;
        }

        constexpr SignalStatus_E Status(void) const
        {
            return m_status;
        }

        constexpr bool Valid(void) const
        {
            return (m_status == SignalStatus_E::VALID);
        }

        //------------------------------------------------------------------------------------------
        // Helper conversions (for CAN setters)
        //------------------------------------------------------------------------------------------
        template<typename C>
        constexpr QualifiedVal<C> Convert(C)
        {
            return QualifiedVal<C>{static_cast<C>(m_val), m_status};
        }
};

//--------------------------------------------------------------------------------------------------
// Aliases
//--------------------------------------------------------------------------------------------------
typedef QualifiedVal<float> float_q;

typedef QualifiedVal<uint8_t>  uint8_q;
typedef QualifiedVal<uint16_t> uint16_q;
typedef QualifiedVal<uint32_t> uint32_q;

typedef QualifiedVal<int8_t>  int8_q;
typedef QualifiedVal<int16_t> int16_q;
typedef QualifiedVal<int32_t> int32_q;

} // namespace QualifiedVal

#endif // QUALIFIED_VAL_HPP
