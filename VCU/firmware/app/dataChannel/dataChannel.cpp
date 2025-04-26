/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "dataChannel.hpp"

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Shared
{

void DataChannelBase::Lock(void) const
{
    taskENTER_CRITICAL();
}

void DataChannelBase::Unlock(void) const
{
    taskEXIT_CRITICAL();
}

} // namespace Shared
