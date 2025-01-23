#ifndef SERVO_INPUT_MESSAGE_MODULE_HPP
#define SERVO_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "rxInterface.hpp"
#include "servoInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class ServoInputMessageModule final : public ServoInputInterface
{
    private:
        const Rx10HzOutputInterface& m_rx10HzRef;

    public:
        constexpr ServoInputMessageModule(
                const Rx10HzOutputInterface& rx10HzRef
            ) :
                ServoInputInterface(),
                m_rx10HzRef(rx10HzRef)
        {}

        NOCOPY_NOMOVE(ServoInputMessageModule);

        virtual float GetLossOfCommPositionDegreesToSet(void) const override
        {
            return 0.0F;
        }

        virtual float GetLossOfCommTimeoutToSet(void) const override
        {
            return 1.0F;
        }

        virtual float_q GetPositionDegreesToSet(void) const override
        {
            return m_rx10HzRef.GetServoPositionRequest();
        }
};

} // namespace Eim

#endif // SERVO_INPUT_MESSAGE_MODULE_HPP
