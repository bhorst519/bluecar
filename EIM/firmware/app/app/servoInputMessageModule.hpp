#ifndef SERVO_INPUT_MESSAGE_MODULE_HPP
#define SERVO_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
// #include "rxInterface.hpp"
#include "servoInterface.hpp"
#include "throttleInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class ServoInputMessageModule final : public Shared::ServoInputInterface
{
    private:
        // const Rx10HzOutputInterface& m_rx10HzRef;
        const ThrottleOutputInterface& m_throttleRef;

    public:
        constexpr ServoInputMessageModule(
                // const Rx10HzOutputInterface& rx10HzRef
                const ThrottleOutputInterface& throttleRef
            ) :
                ServoInputInterface(),
                // m_rx10HzRef(rx10HzRef)
                m_throttleRef(throttleRef)
        {}

        NOCOPY_NOMOVE(ServoInputMessageModule);

        virtual float GetLossOfCommPositionDegreesToSet(void) const override
        {
            // return 0.0F;
            return m_throttleRef.GetIdleThrottlePosDegrees();
        }

        virtual float GetLossOfCommTimeoutToSet(void) const override
        {
            return 1.0F;
        }

        virtual float_q GetPositionDegreesToSet(void) const override
        {
            // return m_rx10HzRef.GetServoPositionRequest();
            return m_throttleRef.GetThrottlePosRequestDegrees();
        }
};

} // namespace Eim

#endif // SERVO_INPUT_MESSAGE_MODULE_HPP
