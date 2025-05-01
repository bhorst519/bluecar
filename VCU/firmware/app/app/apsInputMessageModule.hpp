#ifndef APS_INPUT_MESSAGE_MODULE_HPP
#define APS_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcInterface.hpp"
#include "apsInterface.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Vcu
{

static constexpr float APS_1_NO_THROTTLE_V      { 0.657F };
static constexpr float APS_1_FULL_THROTTLE_V    { 2.753F };

static constexpr float APS_2_NO_THROTTLE_V      { 0.345F };
static constexpr float APS_2_FULL_THROTTLE_V    { 1.396F };

// m = (y2 - y1) / (x2 - x1)
// b = y - mx
static constexpr float APS_1_M = (1.0F - 0.0F) / (APS_1_FULL_THROTTLE_V - APS_1_NO_THROTTLE_V);
static constexpr float APS_1_B = -APS_1_M * APS_1_NO_THROTTLE_V;

static constexpr float APS_2_M = (1.0F - 0.0F) / (APS_2_FULL_THROTTLE_V - APS_2_NO_THROTTLE_V);
static constexpr float APS_2_B = -APS_2_M * APS_2_NO_THROTTLE_V;

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
class ApsInputMessageModule final : public ApsInputInterface
{
    private:
        const AdcOutputInterface& m_adcRef;

    public:
        constexpr ApsInputMessageModule(
                const AdcOutputInterface& adcRef
            ) :
                ApsInputInterface(),
                m_adcRef(adcRef)
        {}

        NOCOPY_NOMOVE(ApsInputMessageModule);

        virtual float_q GetAps1AdcV(void) const override
        {
            return m_adcRef.GetAdcFilt10Hz(ANALOG_APS_1);
        }

        virtual float_q GetAps2AdcV(void) const override
        {
            return m_adcRef.GetAdcFilt10Hz(ANALOG_APS_2);
        }

        virtual float InterpAps1Pct(const float voltage) const override
        {
            return (voltage * APS_1_M) + APS_1_B;
        }

        virtual float InterpAps2Pct(const float voltage) const override
        {
            return (voltage * APS_2_M) + APS_2_B;
        }
};

} // namespace Vcu

#endif // APS_INPUT_MESSAGE_MODULE_HPP
