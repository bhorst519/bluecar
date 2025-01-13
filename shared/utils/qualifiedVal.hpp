#ifndef QUALIFIED_VAL_HPP
#define QUALIFIED_VAL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                 *
***************************************************************************************************/
namespace Shared
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

        friend constexpr bool operator==(const QualifiedVal lhs,
                                         const QualifiedVal rhs)
        {
            return (lhs.m_val == rhs.m_val);
        }

        friend constexpr bool operator!=(const QualifiedVal lhs,
                                         const QualifiedVal rhs)
        {
            return (lhs.m_val != rhs.m_val);
        }

        constexpr operator T(void) const
        {
            return m_val;
        }

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
};

} // namespace Shared

#endif // QUALIFIED_VAL_HPP
