/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "throttleModule.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
namespace Eim
{

static Throttle_Comm_Frame_U gRequestFrame {};
static Throttle_Comm_Frame_U gResponseFrame {};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void ThrottleModule::Init(void)
{
    // Nothing to do
}

void ThrottleModule::Run(void)
{
}

//--------------------------------------------------------------------------------------------------
// Communication
//--------------------------------------------------------------------------------------------------
uint16_t ThrottleModule::CalculateCrc(const uint8_t (&data)[THROTTLE_FRAME_NUM_DATA_BYTES]) const
{
    uint16_t crc = 0xFFFF;

    for (uint32_t i = 0U; i < THROTTLE_FRAME_NUM_DATA_BYTES; i++)
    {
        crc = ((data[i] << 8) ^ crc);

        for (uint32_t j = 0U; j < 8U; j++)
        {
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x8005;
            }
            else
            {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

bool ThrottleModule::VerifyCrc(const Throttle_Comm_Frame_U& frame) const
{
    const uint16_t crcReceived = frame.raw.crc;
    const uint16_t crcExpected = CalculateCrc(frame.raw.data);

    return (crcReceived == crcExpected);
}

bool ThrottleModule::SendRequest(const Throttle_Request_E request, bool checkRequest) const
{
    gRequestFrame.frame.code = static_cast<uint8_t>(request);
    gRequestFrame.frame.id = m_id;
    gRequestFrame.frame.data = 0x0000;
    gRequestFrame.frame.crc = CalculateCrc(gRequestFrame.raw.data);

    // Some requests will not respond
    checkRequest = checkRequest && (request != Throttle_Request_E::SILENT_SET_POINT);

    return checkRequest; // TODO remove
}

bool ThrottleModule::SendSpecialRequest(const Throttle_Special_Request_E request, bool checkRequest) const
{
    // Some requests will not respond
    checkRequest = checkRequest && (request != Throttle_Special_Request_E::RESET);

    return SendRequest(Throttle_Request_E::SPECIAL_FEATURE, checkRequest);
}

} // namespace Eim
