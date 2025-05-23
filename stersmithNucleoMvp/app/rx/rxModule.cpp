/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "DEV_canReceiver.hpp"
#include "rxModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

using namespace CanGen;

void RxNoneModule::Receive(void)
{
    // Nothing to do
}

void Rx10HzModule::Receive(void)
{
    m_outputData.servoPositionRequest = CANRX_DEV_GetS_TESTER_Servo_Position();
}

} // namespace Eim
