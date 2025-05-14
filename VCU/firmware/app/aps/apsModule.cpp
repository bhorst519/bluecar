/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "apsModule.hpp"
#include "mathUtil.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Vcu
{

void ApsModule::Init(void)
{
}

void ApsModule::Run(void)
{
    const float_q aps1AdcV = m_inputData.GetAps1AdcV();
    float aps1Frac = m_inputData.InterpAps1Pct(aps1AdcV);
    aps1Frac = MathUtil::Saturate(aps1Frac, 0.0F, 1.0F);
    m_outputData.aps1Frac = aps1AdcV.Status();
    m_outputData.aps1Frac = aps1Frac;

    const float_q aps2AdcV = m_inputData.GetAps2AdcV();
    float aps2Frac = m_inputData.InterpAps2Pct(aps2AdcV);
    aps2Frac = MathUtil::Saturate(aps2Frac, 0.0F, 1.0F);
    m_outputData.aps2Frac = aps2AdcV.Status();
    m_outputData.aps2Frac = aps2Frac;

    // TODO - proper rationality/arbitration
}

} // namespace Vcu
