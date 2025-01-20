/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "halWrappers.h"
#include "mathUtil.hpp"
#include "servoModule.hpp"
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define SERVO_RESPONSE_TIMEOUT_MS (3U)

namespace Eim
{

static constexpr float SERVO_POSITION_MIN { -170.0F }; // degrees
static constexpr float SERVO_POSITION_MAX {  170.0F }; // degrees
static constexpr float SERVO_POSITION_SCALE { 360.0F / 4096.0F };
static constexpr float SERVO_POSITION_ROUND { SERVO_POSITION_SCALE / 2.0F };

static constexpr float SERVO_LOSS_OF_COMM_TIMEOUT_MAX { 12.7F }; // seconds
static constexpr float SERVO_LOSS_OF_COMM_TIMEOUT_SCALE { 0.1F };
static constexpr float SERVO_LOSS_OF_COMM_TIMEOUT_ROUND { SERVO_LOSS_OF_COMM_TIMEOUT_SCALE / 2.0F };

static constexpr float SERVO_CURRENT_SCALE { 0.02F };
static constexpr float SERVO_TEMPERATURE_OFFSET { -50.0F };
static constexpr float SERVO_VOLTAGE_SCALE { 0.2F };

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static Servo_Comm_Frame_U gRequestFrame __attribute__((aligned(4))) {};
static Servo_Comm_Frame_U gResponseFrame __attribute__((aligned(4))) {};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void ServoModule::Init(void)
{
    m_outputData.id = SERVO_BROADCAST_ID;
}

void ServoModule::Run(void)
{
    SanitizeInputs();

    if (!m_initialRead)
    {
        bool success = true;
        success = success && SendRequest(Servo_Request_E::READ_ACTUATOR_ID);
        success = success && SendRequest(Servo_Request_E::READ_LOSS_OF_COMM_POSITION);
        success = success && SendRequest(Servo_Request_E::READ_LOSS_OF_COMM_TIMEOUT);
        success = success && SendRequest(Servo_Request_E::READ_POSITION);
        m_initialRead = success;
    }
    else
    {
        if (m_lossOfCommPositionDegreesToSet != m_outputData.lossOfCommPositionDegrees)
        {
            (void)SendRequest(Servo_Request_E::SET_LOSS_OF_COMM_POSITION);
        }

        if (m_lossOfCommTimeoutToSet != m_outputData.lossOfCommTimeout)
        {
            (void)SendRequest(Servo_Request_E::SET_LOSS_OF_COMM_TIMEOUT);
        }

        InvalidateData();
        (void)SendRequest(Servo_Request_E::READ_VOLTAGE);
        (void)SendRequest(Servo_Request_E::SET_POSITION);
        (void)SendRequest(Servo_Request_E::READ_CURRENT);
        (void)SendRequest(Servo_Request_E::READ_TEMPERATURE);
    }
}

void ServoModule::SanitizeInputs(void)
{
    const float_q positionDegreesToSet = m_inputData.GetPositionDegreesToSet();
    if (positionDegreesToSet.Valid())
    {
        m_positionDegreesToSet = MathUtil::Saturate(positionDegreesToSet.Val(), SERVO_POSITION_MIN, SERVO_POSITION_MAX);
    }
    // else
    // {
    //     // TODO remove demo
    //     static float gInc = 5.0F;
    //     float position = m_positionDegreesToSet;
    //     position = position + gInc;
    //     if      (position >= SERVO_POSITION_MAX) { position = SERVO_POSITION_MAX; gInc *= -1.0F; }
    //     else if (position <= SERVO_POSITION_MIN) { position = SERVO_POSITION_MIN; gInc *= -1.0F; }
    //     m_positionDegreesToSet = position;
    // }

    const float lossOfCommPositionDegreesToSet = m_inputData.GetLossOfCommPositionDegreesToSet();
    m_lossOfCommPositionDegreesToSet = MathUtil::Saturate(lossOfCommPositionDegreesToSet, SERVO_POSITION_MIN, SERVO_POSITION_MAX);

    const float lossOfCommTimeoutToSet = m_inputData.GetLossOfCommTimeoutToSet();
    m_lossOfCommTimeoutToSet = MathUtil::Saturate(lossOfCommTimeoutToSet, 0.0F, SERVO_LOSS_OF_COMM_TIMEOUT_MAX);
}

void ServoModule::InvalidateData(void)
{
    m_outputData.positionDegrees = SignalStatus_E::SNA;
    m_outputData.current = SignalStatus_E::SNA;
    m_outputData.temperature = SignalStatus_E::SNA;
    m_outputData.voltage = SignalStatus_E::SNA;
}

//--------------------------------------------------------------------------------------------------
// Communication
//--------------------------------------------------------------------------------------------------
uint16_t ServoModule::CalculateCrc(const uint8_t (&data)[SERVO_FRAME_NUM_DATA_BYTES]) const
{
    uint16_t crc = 0xFFFF;

    for (uint32_t i = 0U; i < SERVO_FRAME_NUM_DATA_BYTES; i++)
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

bool ServoModule::VerifyCrc(const Servo_Comm_Frame_U& frame) const
{
    const uint16_t crcReceived = ENDIANSWAP_U16(frame.raw.crc);
    const uint16_t crcExpected = CalculateCrc(frame.raw.data);

    return (crcReceived == crcExpected);
}

bool ServoModule::VerifyResponse(const Servo_Request_E request, const Servo_Comm_Frame_U& frame, const uint16_t requestData) const
{
    bool success = true;
    const Servo_Response_E response = ServoGetResponseFromRequest(request);
    const bool expectEcho = ServoGetResponseExpectEcho(request);

    uint8_t expectedId;
    if (request == Servo_Request_E::READ_ACTUATOR_ID)
    {
        // Device will respond using the ID that it's reporting as data
        expectedId = U16_LSB(frame.frame.data);
    }
    else if (request == Servo_Request_E::SET_ACTUATOR_ID)
    {
        // Device will respond with the newly assigned ID
        expectedId = m_idToSet;
    }
    else
    {
        expectedId = m_outputData.id;
    }

    success = success && (response != Servo_Response_E::INVALID);
    success = success && (frame.frame.id == expectedId);
    success = success && VerifyCrc(frame);
    success = success && (frame.frame.code == static_cast<uint8_t>(response));

    if (expectEcho)
    {
        success = success && (frame.frame.data == requestData);
    }
    else if (request == Servo_Request_E::SPECIAL_FEATURE)
    {
        // Reset will not respond, but the access request will - with a special response
        success = success && (frame.frame.data == U16(0x41, 0x45));
    }
    else
    {
        // Checks are all done
    }

    return success;
}

bool ServoModule::Transceive(const Servo_Request_E request, const bool checkRequest) const
{
    bool success = true;

    gRequestFrame.frame.code = static_cast<uint8_t>(request);
    gRequestFrame.frame.id = m_outputData.id;
    gRequestFrame.frame.crc = ENDIANSWAP_U16(CalculateCrc(gRequestFrame.raw.data));

    // Set up for receive, if needed
    if (success && checkRequest)
    {
        success = HalWrappersUartReceive(SERIAL_SERVO, &gResponseFrame.raw.data[0U], SERVO_FRAME_SIZE);
    }

    // Initiate transmit
    if (success)
    {
        const bool txCompleteNotify = (!checkRequest);
        success = HalWrappersUartTransmit(SERIAL_SERVO, &gRequestFrame.raw.data[0U], SERVO_FRAME_SIZE, txCompleteNotify);
    }

    // Wait for receive data, if needed. Otherwise wait for transmit to finish
    if (success)
    {
        success = HalWrappersUartWait(SERIAL_SERVO, SERVO_RESPONSE_TIMEOUT_MS);
    }

    if (success && checkRequest)
    {
        success = VerifyResponse(request, gResponseFrame, gRequestFrame.frame.data);
    }

    return success;
}

bool ServoModule::PrepareRequest(const Servo_Request_E request,  uint16_t& data)
{
    bool success = true;

    switch(request)
    {
        case Servo_Request_E::SET_ACTUATOR_ID:
        {
            if (ServoGetValidId(m_idToSet))
            {
                data = U16(m_idToSet, m_idToSet);
            }
            else
            {
                success = false;
            }
            break;
        }
        case Servo_Request_E::SILENT_SET_POSITION:
        case Servo_Request_E::SET_POSITION:
        {
            data = static_cast<int16_t>(
                  (m_positionDegreesToSet + SERVO_POSITION_ROUND)
                / SERVO_POSITION_SCALE );
            data = ENDIANSWAP_U16(static_cast<uint16_t>(data));
            break;
        }
        case Servo_Request_E::SET_LOSS_OF_COMM_POSITION:
            data = static_cast<int16_t>(
                  (m_lossOfCommPositionDegreesToSet + SERVO_POSITION_ROUND)
                / SERVO_POSITION_SCALE );
            data = ENDIANSWAP_U16(static_cast<uint16_t>(data));
            // Invalidate stored config data
            m_outputData.lossOfCommTimeout = SignalStatus_E::SNA;
            break;
        case Servo_Request_E::SET_LOSS_OF_COMM_TIMEOUT:
        {
            const uint8_t dataToSet = static_cast<uint8_t>(
                  (m_lossOfCommTimeoutToSet + SERVO_LOSS_OF_COMM_TIMEOUT_ROUND)
                / SERVO_LOSS_OF_COMM_TIMEOUT_SCALE );
            data = U16(dataToSet, dataToSet);
            // Invalidate stored config data
            m_outputData.lossOfCommPositionDegrees = SignalStatus_E::SNA;
            break;
        }
        case Servo_Request_E::READ_ACTUATOR_ID:
        case Servo_Request_E::READ_POSITION:
        case Servo_Request_E::READ_SCALED_POSITION:
        case Servo_Request_E::READ_LOSS_OF_COMM_POSITION:
        case Servo_Request_E::READ_LOSS_OF_COMM_TIMEOUT:
        case Servo_Request_E::READ_CURRENT:
        case Servo_Request_E::READ_TEMPERATURE:
        case Servo_Request_E::READ_VOLTAGE:
            data = 0U;
            break;
        case Servo_Request_E::SPECIAL_FEATURE:
            // Not handled here
            break;
        case Servo_Request_E::SET_SCALED_POINT:
        case Servo_Request_E::SET_POSITION_AS_ZERO:
        case Servo_Request_E::SET_POSITION_AS_LOSS_OF_COMM:
        case Servo_Request_E::SET_EEPROM_PARAM:
        case Servo_Request_E::READ_EEPROM_PARAM:
        case Servo_Request_E::SET_EEPROM_LOW_PARAM:
        case Servo_Request_E::READ_EEPROM_LOW_PARAM:
        case Servo_Request_E::SET_EEPROM_HIGH_PARAM:
        case Servo_Request_E::READ_EEPROM_HIGH_PARAM:
        case Servo_Request_E::INVALID:
        default:
            // Invalid, or not supported
            success = false;
            break;
    }

    return success;
}

bool ServoModule::PrepareSpecialRequest(const Servo_Special_Request_E request, uint16_t& data) const
{
    bool success = true;

    switch (request)
    {
        case Servo_Special_Request_E::ACCESS_SPECIAL_FEATURE:
            data = U16(0x41, 0x3F);
            break;
        case Servo_Special_Request_E::RESET:
            data = U16(0x52, 0x52);
            break;
        default:
            success = false;
            break;
    }

    return success;
}

bool ServoModule::ProcessResponse(const Servo_Request_E request, const uint16_t data)
{
    bool success = true;

    switch(request)
    {
        case Servo_Request_E::SET_ACTUATOR_ID:
        case Servo_Request_E::READ_ACTUATOR_ID:
            m_outputData.id = U16_LSB(data);
            break;
        case Servo_Request_E::SET_POSITION:
        case Servo_Request_E::READ_POSITION:
        case Servo_Request_E::SET_POSITION_AS_ZERO:
        case Servo_Request_E::SET_POSITION_AS_LOSS_OF_COMM:
        {
            const int16_t readData = static_cast<int16_t>(data);
            m_outputData.positionDegrees = static_cast<float>(readData) * SERVO_POSITION_SCALE;
            m_outputData.positionDegrees = SignalStatus_E::VALID;
            break;
        }
        case Servo_Request_E::SET_LOSS_OF_COMM_POSITION:
        case Servo_Request_E::READ_LOSS_OF_COMM_POSITION:
        {
            const int16_t readData = static_cast<int16_t>(data);
            m_outputData.lossOfCommPositionDegrees = static_cast<float>(readData) * SERVO_POSITION_SCALE;
            m_outputData.lossOfCommPositionDegrees = SignalStatus_E::VALID;
            break;
        }
        case Servo_Request_E::SET_LOSS_OF_COMM_TIMEOUT:
        case Servo_Request_E::READ_LOSS_OF_COMM_TIMEOUT:
            m_outputData.lossOfCommTimeout = static_cast<float>(U16_LSB(data)) * SERVO_LOSS_OF_COMM_TIMEOUT_SCALE;
            m_outputData.lossOfCommTimeout = SignalStatus_E::VALID;
            break;
        case Servo_Request_E::READ_CURRENT:
            m_outputData.current = static_cast<float>(U16_LSB(data)) * SERVO_CURRENT_SCALE;
            m_outputData.current = SignalStatus_E::VALID;
            break;
        case Servo_Request_E::READ_TEMPERATURE:
            m_outputData.temperature = static_cast<float>(U16_LSB(data)) + SERVO_TEMPERATURE_OFFSET;
            m_outputData.temperature = SignalStatus_E::VALID;
            break;
        case Servo_Request_E::READ_VOLTAGE:
            m_outputData.voltage = static_cast<float>(U16_LSB(data)) * SERVO_VOLTAGE_SCALE;
            m_outputData.voltage = SignalStatus_E::VALID;
            break;
        case Servo_Request_E::SILENT_SET_POSITION:
        case Servo_Request_E::SET_EEPROM_PARAM:
        case Servo_Request_E::SET_EEPROM_LOW_PARAM:
        case Servo_Request_E::SET_EEPROM_HIGH_PARAM:
        case Servo_Request_E::SPECIAL_FEATURE:
            // Nothing to do
            break;
        case Servo_Request_E::SET_SCALED_POINT: // Response is actual scaled position
        case Servo_Request_E::READ_SCALED_POSITION:
        case Servo_Request_E::READ_EEPROM_PARAM:
        case Servo_Request_E::READ_EEPROM_LOW_PARAM:
        case Servo_Request_E::READ_EEPROM_HIGH_PARAM:
        case Servo_Request_E::INVALID:
            // Invalid, or not supported
            success = false;
            break;
    }

    return success;
}

bool ServoModule::SendRequest(const Servo_Request_E request, bool checkRequest)
{
    bool success = true;

    // Some requests will not respond
    checkRequest = checkRequest && (request != Servo_Request_E::SILENT_SET_POSITION);

    if (success)
    {
        // Since the data struct is packed, need to be careful not to use pointers/references
        // due to risk of losing alignment
        uint16_t dataToSet;
        success = PrepareRequest(request, dataToSet);
        gRequestFrame.frame.data = dataToSet;
    }

    if (success)
    {
        success = Transceive(request, checkRequest);
    }

    if (success && checkRequest)
    {
        success = ProcessResponse(request, ENDIANSWAP_U16(gResponseFrame.frame.data));
    }

    return success;
}

bool ServoModule::SendSpecialRequest(const Servo_Special_Request_E request)
{
    bool success = true;

    // Some requests will not respond
    const bool checkRequest = (request != Servo_Special_Request_E::RESET);

    if (success)
    {
        // Since the data struct is packed, need to be careful not to use pointers/references
        // due to risk of losing alignment
        uint16_t dataToSet;
        success = PrepareSpecialRequest(request, dataToSet);
        gRequestFrame.frame.data = dataToSet;
    }

    if (success)
    {
        success = SendRequest(Servo_Request_E::SPECIAL_FEATURE, checkRequest);
    }

    return success;
}

} // namespace Eim
