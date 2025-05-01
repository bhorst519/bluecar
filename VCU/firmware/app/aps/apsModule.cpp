/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "apsModule.hpp"

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
    m_outputData.aps1Frac = aps1AdcV.Status();
    m_outputData.aps1Frac = m_inputData.InterpAps1Pct(aps1AdcV);

    const float_q aps2AdcV = m_inputData.GetAps2AdcV();
    m_outputData.aps2Frac = aps2AdcV.Status();
    m_outputData.aps2Frac = m_inputData.InterpAps2Pct(aps2AdcV);

    // TODO - proper rationality/arbitration
}

} // namespace Vcu
