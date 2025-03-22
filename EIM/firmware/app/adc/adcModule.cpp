/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "adcModule.hpp"
#include "halWrappers.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

void AdcModule::Init(void)
{
}

void AdcModule::Run(void)
{
    for (size_t idx = 0U; idx < m_adcFilt10Hz.Size(); ++idx)
    {
        const float_q val = HalWrappersAdcGetValue(static_cast<HalWrappers_Analog_E>(idx));
        const float valFilt = m_adcFilt10Hz.RunIfValidAndGetOutput(idx, val.Val(), val.Valid());
        m_outputData.adcFilt10Hz[idx] = valFilt;
        m_outputData.adcFilt10Hz[idx] = val.Status();
    }

    if (HalWrappersAdcGetFinished())
    {
        HalWrappersAdcTriggerStart();
    }
}

} // namespace Eim
