/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappersComponentSpecific.hpp"
#include "ioIntModule.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Vcu
{

void IoIntModule::Init(void)
{
}

void IoIntModule::Run(void)
{
    m_outputData.brakeSwitch    = !gHalWrappers.GpioRead(GPIO_BRAKE_SWITCH);
    m_outputData.engineEnable   = !gHalWrappers.GpioRead(GPIO_ENG_ENABLE);
    m_outputData.engineStart    = !gHalWrappers.GpioRead(GPIO_ENG_START);
    m_outputData.userSwitch     = !gHalWrappers.GpioRead(GPIO_USER_SWITCH);
}

} // namespace Vcu
