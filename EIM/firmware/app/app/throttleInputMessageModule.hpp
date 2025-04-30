#ifndef THROTTLE_INPUT_MESSAGE_MODULE_HPP
#define THROTTLE_INPUT_MESSAGE_MODULE_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "rxInterface.hpp"
#include "throttleInterface.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

static constexpr float THROTTLE_CLOSED_DEG  {   10.0F };
static constexpr float THROTTLE_WOT_DEG     { -100.0F };

// m = (y2 - y1) / (x2 - x1)
// b = y - mx
static constexpr float THROTTLE_M = (THROTTLE_WOT_DEG - THROTTLE_CLOSED_DEG) / (1.0F - 0.0F);
static constexpr float THROTTLE_B = THROTTLE_CLOSED_DEG;

/**************************************************************************************************
*                              C L A S S   D E C L A R A T I O N S                                *
**************************************************************************************************/
class ThrottleInputMessageModule final : public ThrottleInputInterface
{
    private:
        const Rx10HzOutputInterface& m_rx10HzRef;

    public:
        constexpr ThrottleInputMessageModule(
                const Rx10HzOutputInterface& rx10HzRef
            ) :
                ThrottleInputInterface(),
                m_rx10HzRef(rx10HzRef)
        {}

        NOCOPY_NOMOVE(ThrottleInputMessageModule);

        virtual float_q GetApsFrac(void) const override
        {
            return m_rx10HzRef.GetApsFrac();
        }

        virtual float InterpThrottlePosDegrees(const float frac) const override
        {
            return (frac * THROTTLE_M) + THROTTLE_B;
        }
};

} // namespace Eim

#endif // THROTTLE_INPUT_MESSAGE_MODULE_HPP
