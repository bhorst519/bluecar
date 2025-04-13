/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappersComponentSpecific.hpp"
#include "ioIntModule.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

static constexpr uint8_t GEAR_SELECT_DEBOUNCE_COUNT {5U};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
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
    ProcessIO();
    GearSelect();
}

void IoIntModule::ProcessIO(void)
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

    m_outputData.turnRight      = !gHalWrappers.GpioRead(GPIO_TURN_R);
    m_outputData.turnLeft       = !gHalWrappers.GpioRead(GPIO_TURN_L);
    m_outputData.lowBeam        = !gHalWrappers.GpioRead(GPIO_LOW_BEAM);
    m_outputData.highBeam       = !gHalWrappers.GpioRead(GPIO_HIGH_BEAM);
    m_outputData.faultIndicator = !gHalWrappers.GpioRead(GPIO_FAULT_IND);
    m_outputData.oilPressureLow = !gHalWrappers.GpioRead(GPIO_OIL_P_LOW);

    m_outputData.gearN = !gHalWrappers.GpioRead(GPIO_GEAR_N);
    m_outputData.gear1 = !gHalWrappers.GpioRead(GPIO_GEAR_1);
    m_outputData.gear2 = !gHalWrappers.GpioRead(GPIO_GEAR_2);
    m_outputData.gear3 = !gHalWrappers.GpioRead(GPIO_GEAR_3);
    m_outputData.gear4 = !gHalWrappers.GpioRead(GPIO_GEAR_4);
    m_outputData.gear5 = !gHalWrappers.GpioRead(GPIO_GEAR_5);
    m_outputData.gear6 = !gHalWrappers.GpioRead(GPIO_GEAR_6);
}

void IoIntModule::GearSelect(void)
{
    // Loop over all gear sense and identify the gear select candidate
    bool gearSelectFound = false;
    GearSelect_E gearSelectCandidate = m_gearSelectCandidate;
    for (uint8_t idx = 0U; idx < MAX_NUM_GEAR_SELECT; ++idx)
    {
        const bool currGear = (*m_pGears[idx]);
        if (currGear)
        {
            if (gearSelectFound)
            {
                // More than one gear select identified
                gearSelectCandidate = GearSelect_E::ERROR;
            }
            else
            {
                gearSelectFound = true;
                gearSelectCandidate = static_cast<GearSelect_E>(idx);
            }
        }
    }

    // Debounce gear select candidate
    if (gearSelectFound)
    {
        if (gearSelectCandidate == m_gearSelectCandidate)
        {
            ++m_gearSelectCandidateCounter;
            m_gearSelectCandidateCounter = MIN(m_gearSelectCandidateCounter, GEAR_SELECT_DEBOUNCE_COUNT);
        }
        else
        {
            m_gearSelectCandidateCounter = 0U;
        }
    }
    m_gearSelectCandidate = gearSelectCandidate;

    // Set gear select output
    if (m_gearSelectCandidateCounter >= GEAR_SELECT_DEBOUNCE_COUNT)
    {
        m_outputData.gearSelect = m_gearSelectCandidate;
    }
}

} // namespace Eim
