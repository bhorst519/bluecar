/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "throttleModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

void ThrottleModule::Init(void)
{
    m_outputData.idleThrottlePosDegrees = m_inputData.InterpThrottlePosDegrees(0.0F);
}

void ThrottleModule::Run(void)
{
    const float_q apsFrac = m_inputData.GetApsFrac();
    m_outputData.throttlePosRequestDegrees = apsFrac.Status();
    m_outputData.throttlePosRequestDegrees = m_inputData.InterpThrottlePosDegrees(apsFrac);
}

} // namespace Eim
