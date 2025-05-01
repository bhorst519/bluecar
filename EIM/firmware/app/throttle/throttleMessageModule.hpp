#ifndef THROTTLE_MESSAGE_MODULE_HPP
#define THROTTLE_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "throttleInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class ThrottleMessageModule final : public ThrottleOutputInterface
{
    private:
        const ThrottleData_S& m_dataRef;

    public:
        constexpr ThrottleMessageModule(
                const ThrottleData_S& dataRef
            ) :
                ThrottleOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(ThrottleMessageModule);

        virtual float GetIdleThrottlePosDegrees(void) const override
        {
            return m_dataRef.idleThrottlePosDegrees;
        }

        virtual float_q GetThrottlePosRequestDegrees(void) const override
        {
            return m_dataRef.throttlePosRequestDegrees;
        }
};

} // namespace Eim

#endif // THROTTLE_MESSAGE_MODULE_HPP
