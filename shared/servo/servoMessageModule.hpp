#ifndef SERVO_MESSAGE_MODULE_HPP
#define SERVO_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "servoData.hpp"
#include "servoInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Shared
{

class ServoMessageModule final : public ServoOutputInterface
{
    private:
        const ServoData_S& m_dataRef;

    public:
        constexpr ServoMessageModule(
                const ServoData_S& dataRef
            ) :
                ServoOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(ServoMessageModule);

        virtual float_q GetCurrent(void) const override
        {
            return m_dataRef.current;
        }

        virtual uint8_t GetId(void) const override
        {
            return m_dataRef.id;
        }

        virtual float_q GetLossOfCommPositionDegrees(void) const override
        {
            return m_dataRef.lossOfCommPositionDegrees;
        }

        virtual float_q GetLossOfCommTimeout(void) const override
        {
            return m_dataRef.lossOfCommTimeout;
        }

        virtual float_q GetPositionDegrees(void) const override
        {
            return m_dataRef.positionDegrees;
        }

        virtual float_q GetTemperature(void) const override
        {
            return m_dataRef.temperature;
        }

        virtual float_q GetVoltage(void) const override
        {
            return m_dataRef.voltage;
        }
};

} // namespace Shared

#endif // SERVO_MESSAGE_MODULE_HPP
