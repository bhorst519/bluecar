#ifndef RX_MESSAGE_MODULE_HPP
#define RX_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "rxInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class Rx100HzMessageModule final : public Rx100HzOutputInterface
{
    private:
        const Rx100HzData_S& m_dataRef;

    public:
        constexpr Rx100HzMessageModule(
                const Rx100HzData_S& dataRef
            ) :
                Rx100HzOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(Rx100HzMessageModule);

        virtual uint8_q GetBrakeLightEn(void) const override
        {
            return m_dataRef.brakeLightEn;
        }

        virtual uint8_q GetEngineOnEn(void) const override
        {
            return m_dataRef.engineOnEn;
        }

        virtual uint8_q GetEngineStartEn(void) const override
        {
            return m_dataRef.engineStartEn;
        }

        virtual uint8_q GetHeadlightEn(void) const override
        {
            return m_dataRef.headlightEn;
        }

        virtual uint8_q GetHighBeamEn(void) const override
        {
            return m_dataRef.highBeamEn;
        }

        virtual uint8_q GetHornEn(void) const override
        {
            return m_dataRef.hornEn;
        }

        virtual uint8_q GetMainRelayEn(void) const override
        {
            return m_dataRef.mainRelayEn;
        }

        virtual uint8_q GetTurnLeftEn(void) const override
        {
            return m_dataRef.turnLeftEn;
        }

        virtual uint8_q GetTurnRightEn(void) const override
        {
            return m_dataRef.turnRightEn;
        }
};

class Rx10HzMessageModule final : public Rx10HzOutputInterface
{
    private:
        const Rx10HzData_S& m_dataRef;

    public:
        constexpr Rx10HzMessageModule(
                const Rx10HzData_S& dataRef
            ) :
                Rx10HzOutputInterface(),
                m_dataRef(dataRef)
        {}

        NOCOPY_NOMOVE(Rx10HzMessageModule);

        virtual float_q GetServoPositionRequest(void) const override
        {
            return m_dataRef.servoPositionRequest;
        }
};

} // namespace Eim

#endif // RX_MESSAGE_MODULE_HPP
