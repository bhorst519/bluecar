/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappersComponentSpecific.hpp"
#include "ioIntModule.hpp"

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
namespace Eim
{

static void SetGpio(const uint8_q sig, const HalWrappers_Gpio_E gpio)
{
    const bool level = (sig.Val() > 0U) ? true : false;
    gHalWrappers.GpioSet(gpio, level);
}

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void IoIntModule::Init(void)
{
}

void IoIntModule::Run(void)
{
    const uint8_q mainRelayEn = m_inputData.GetMainRelayEn();
    if (mainRelayEn.Valid())
    {
        SetGpio(mainRelayEn, GPIO_MAIN_RELAY_EN);
    }

    const uint8_q brakeLightEn = m_inputData.GetBrakeLightEn();
    if (brakeLightEn.Valid())
    {
        SetGpio(brakeLightEn, GPIO_BRAKE_LIGHT_EN);
    }

    const uint8_q turnRightEn = m_inputData.GetTurnRightEn();
    if (turnRightEn.Valid())
    {
        SetGpio(turnRightEn, GPIO_TURN_R_EN);
    }

    const uint8_q turnLeftEn = m_inputData.GetTurnLeftEn();
    if (turnLeftEn.Valid())
    {
        SetGpio(turnLeftEn, GPIO_TURN_L_EN);
    }

    const uint8_q headlightEn = m_inputData.GetHeadlightEn();
    if (headlightEn.Valid())
    {
        SetGpio(headlightEn, GPIO_HEADLIGHT_RELAY_EN);
    }

    const uint8_q highBeamEn = m_inputData.GetHighBeamEn();
    if (highBeamEn.Valid())
    {
        SetGpio(highBeamEn, GPIO_HIGH_BEAM_EN);
    }

    const uint8_q hornEn = m_inputData.GetHornEn();
    if (hornEn.Valid())
    {
        SetGpio(hornEn, GPIO_HORN_EN);
    }
}

} // namespace Eim
