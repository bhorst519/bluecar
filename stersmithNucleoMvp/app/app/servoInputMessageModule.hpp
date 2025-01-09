#ifndef SERVO_INPUT_MESSAGE_MODULE_HPP
#define SERVO_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "servoInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class ServoInputMessageModule final : public ServoInputInterface
{
    public:
        constexpr ServoInputMessageModule(
            ) :
                ServoInputInterface()
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

        virtual float GetPositionDegreesToSet(void) const override
        {
            return 0.0F;
        }
};

} // namespace Eim

#endif // SERVO_INPUT_MESSAGE_MODULE_HPP
