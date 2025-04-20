/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "filter.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "tachComponent.h"
#include "tachModule.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

static constexpr uint32_t TACH_CHECKIN_TIMEOUT_US {1000000U}; // 1 sec
static constexpr uint32_t TACH_MIN_DELTA_T_US_FILT {1000U}; // 1 ms

} // namespace Eim

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace
{

using Lpf1stFloat = Filter::Lpf1st<float, float>;

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static Lpf1stFloat::Core gTachTimeDeltaFilt {Lpf1stFloat::ComputeCoeffs(10.0F, 1.0F)};
static uint32_t gTachCheckInTimestampUs {0U};
static uint32_t gTachCheckInTimestampUsPrev {0U};
static bool gTachCheckInValid {false};
static bool gTachCheckInPrevValid {false};

} // namespace (anonymous)

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
extern "C" {

void TachComponentCheckIn(void)
{
    gTachCheckInTimestampUsPrev = gTachCheckInTimestampUs;
    gTachCheckInTimestampUs = Eim::gHalWrappers.TimerGetUs();
    gTachCheckInPrevValid = gTachCheckInValid;
    gTachCheckInValid = true;

    if (gTachCheckInPrevValid && gTachCheckInValid)
    {
        const float tachTimeDeltaUs = static_cast<float>(gTachCheckInTimestampUs - gTachCheckInTimestampUsPrev);
        if (tachTimeDeltaUs < Eim::TACH_MIN_DELTA_T_US_FILT)
        {
            gTachTimeDeltaFilt.Run(tachTimeDeltaUs);
        }
        else
        {
            gTachTimeDeltaFilt.SetState(tachTimeDeltaUs);
        }
    }
}

} // extern "C"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

void TachModule::Init(void)
{
}

void TachModule::Run(void)
{
    taskENTER_CRITICAL();
    const uint32_t currentTimeUs = gHalWrappers.TimerGetUs();
    const uint32_t tachTimestampUs = gTachCheckInTimestampUs;
    const float tachTimeDeltaUsFilt = gTachTimeDeltaFilt.GetOutput();
    const bool tachTimeDeltaUsValid = (gTachCheckInPrevValid && gTachCheckInValid);
    taskEXIT_CRITICAL();

    const uint32_t timeSinceCheckInUs = currentTimeUs - tachTimestampUs;

    if (timeSinceCheckInUs >= TACH_CHECKIN_TIMEOUT_US)
    {
        gTachCheckInPrevValid = false;
        gTachCheckInValid = false;

        m_outputData.freq = SignalStatus_E::SNA;
        m_outputData.rpm = SignalStatus_E::SNA;
    }
    else if (tachTimeDeltaUsValid)
    {
        const float freqFilt = 1000000.0F / tachTimeDeltaUsFilt;

        m_outputData.freq = freqFilt;
        m_outputData.freq = SignalStatus_E::VALID;
        m_outputData.rpm = (freqFilt * 60.0F);
        m_outputData.rpm = SignalStatus_E::VALID;
    }
    else
    {
        m_outputData.freq = SignalStatus_E::SNA;
        m_outputData.rpm = SignalStatus_E::SNA;
    }
}

} // namespace Eim
