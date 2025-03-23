#ifndef IO_INT_INPUT_MESSAGE_MODULE_HPP
#define IO_INT_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "ioIntInterface.hpp"
#include "rxInterface.hpp"

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
namespace Eim
{

class IoIntInputMessageModule final : public IoIntInputInterface
{
    private:
        const Rx100HzOutputInterface& m_rx100HzRef;

    public:
        constexpr IoIntInputMessageModule(
                const Rx100HzOutputInterface& rx100HzRef
            ) :
                IoIntInputInterface(),
                m_rx100HzRef(rx100HzRef)
        {}

        NOCOPY_NOMOVE(IoIntInputMessageModule);

        virtual uint8_q GetBrakeLightEn(void) const override
        {
            return m_rx100HzRef.GetBrakeLightEn();
        }

        virtual uint8_q GetHeadlightEn(void) const override
        {
            return m_rx100HzRef.GetHeadlightEn();
        }

        virtual uint8_q GetHighBeamEn(void) const override
        {
            return m_rx100HzRef.GetHighBeamEn();
        }

        virtual uint8_q GetHornEn(void) const override
        {
            return m_rx100HzRef.GetHornEn();
        }

        virtual uint8_q GetMainRelayEn(void) const override
        {
            return m_rx100HzRef.GetMainRelayEn();
        }

        virtual uint8_q GetTurnLeftEn(void) const override
        {
            return m_rx100HzRef.GetTurnLeftEn();
        }

        virtual uint8_q GetTurnRightEn(void) const override
        {
            return m_rx100HzRef.GetTurnRightEn();
        }
};

} // namespace Eim

#endif // IO_INT_INPUT_MESSAGE_MODULE_HPP
