#ifndef SERVO_COMM_TYPES_HPP
#define SERVO_COMM_TYPES_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

static constexpr uint8_t SERVO_BROADCAST_ID { 0x1F };
static constexpr uint8_t SERVO_MIN_ID { 0x01 };
static constexpr uint8_t SERVO_MAX_ID { 0x1E };

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
enum class Servo_Request_E : uint8_t
{
    INVALID = 0x00,

    SET_ACTUATOR_ID = 0xAA,
    READ_ACTUATOR_ID = 0xDA,

    SILENT_SET_POSITION = 0x77,

    SET_POSITION = 0x76,
    READ_POSITION = 0x69,

    SET_SCALED_POINT = 0x78,
    READ_SCALED_POSITION = 0x79,

    SET_LOSS_OF_COMM_POSITION = 0xBB,
    READ_LOSS_OF_COMM_POSITION = 0x90,

    SET_LOSS_OF_COMM_TIMEOUT = 0xCC,
    READ_LOSS_OF_COMM_TIMEOUT = 0x91,

    SET_POSITION_AS_ZERO = 0x99,
    SET_POSITION_AS_LOSS_OF_COMM = 0xBC,

    READ_CURRENT = 0xB0,
    READ_TEMPERATURE = 0xC0,
    READ_VOLTAGE = 0xB1,

    // EEPROM address 0x20 to 0x30
    SET_EEPROM_PARAM = 0xE8,
    READ_EEPROM_PARAM = 0xE7,

    // EEPROM address 0x00 to 0xFF
    SET_EEPROM_LOW_PARAM = 0xF9,
    READ_EEPROM_LOW_PARAM = 0xF8,

    // EEPROM address 0x100 to 0x1FF
    SET_EEPROM_HIGH_PARAM = 0xFA,
    READ_EEPROM_HIGH_PARAM = 0xE9,

    SPECIAL_FEATURE = 0xFF,
};

enum class Servo_Response_E : uint8_t
{
    INVALID = 0x00,

    SET_ACTUATOR_ID = 0x55,
    READ_ACTUATOR_ID = 0x6D,

    SET_POSITION = 0x56,
    READ_POSITION = 0x49,

    SET_SCALED_POINT = 0x58,
    READ_SCALED_POSITION = 0x59,

    SET_LOSS_OF_COMM_POSITION = 0x5D,
    READ_LOSS_OF_COMM_POSITION = 0x60,

    SET_LOSS_OF_COMM_TIMEOUT = 0x66,
    READ_LOSS_OF_COMM_TIMEOUT = 0x61,

    SET_POSITION_AS_ZERO = 0x4C,
    SET_POSITION_AS_LOSS_OF_COMM = 0x5C,

    READ_CURRENT = 0x30,
    READ_TEMPERATURE = 0x10,
    READ_VOLTAGE = 0x31,

    // EEPROM address 0x20 to 0x30
    SET_EEPROM_PARAM = 0x48,
    READ_EEPROM_PARAM = 0x47,

    // EEPROM address 0x00 to 0xFF
    SET_EEPROM_LOW_PARAM = 0xF9,
    READ_EEPROM_LOW_PARAM = 0xF8,

    // EEPROM address 0x100 to 0x1FF
    SET_EEPROM_HIGH_PARAM = 0xFA,
    READ_EEPROM_HIGH_PARAM = 0x49,

    SPECIAL_FEATURE = 0xFF,
};

enum class Servo_Special_Request_E
{
    ACCESS_SPECIAL_FEATURE,
    RESET,
};

//--------------------------------------------------------------------------------------------------
// Data packing
//--------------------------------------------------------------------------------------------------
static constexpr uint32_t SERVO_FRAME_NUM_DATA_BYTES { 4U };

struct Servo_Comm_Frame_S
{
    uint8_t code;
    uint8_t id;
    uint16_t data;
    uint16_t crc;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Servo_Comm_Frame_S) == 6U,
    "Incorrect servo data size");

struct Servo_Comm_Raw_Frame_S
{
    uint8_t data[SERVO_FRAME_NUM_DATA_BYTES];
    uint16_t crc;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Servo_Comm_Raw_Frame_S) == 6U,
    "Incorrect servo data size");

union Servo_Comm_Frame_U
{
    Servo_Comm_Frame_S frame;
    Servo_Comm_Raw_Frame_S raw;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Servo_Comm_Frame_U) == 6U,
    "Incorrect servo data size");

static constexpr uint32_t SERVO_FRAME_SIZE { sizeof(Servo_Comm_Frame_U) };

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/
constexpr Servo_Response_E ServoGetResponseFromRequest(const Servo_Request_E request)
{
    Servo_Response_E response = Servo_Response_E::INVALID;

    switch(request)
    {
        case Servo_Request_E::SET_ACTUATOR_ID:
            response = Servo_Response_E::SET_ACTUATOR_ID;
            break;
        case Servo_Request_E::READ_ACTUATOR_ID:
            response = Servo_Response_E::READ_ACTUATOR_ID;
            break;
        case Servo_Request_E::SET_POSITION:
            response = Servo_Response_E::SET_POSITION;
            break;
        case Servo_Request_E::READ_POSITION:
            response = Servo_Response_E::READ_POSITION;
            break;
        case Servo_Request_E::SET_SCALED_POINT:
            response = Servo_Response_E::SET_SCALED_POINT;
            break;
        case Servo_Request_E::READ_SCALED_POSITION:
            response = Servo_Response_E::READ_SCALED_POSITION;
            break;
        case Servo_Request_E::SET_LOSS_OF_COMM_POSITION:
            response = Servo_Response_E::SET_LOSS_OF_COMM_POSITION;
            break;
        case Servo_Request_E::READ_LOSS_OF_COMM_POSITION:
            response = Servo_Response_E::READ_LOSS_OF_COMM_POSITION;
            break;
        case Servo_Request_E::SET_LOSS_OF_COMM_TIMEOUT:
            response = Servo_Response_E::SET_LOSS_OF_COMM_TIMEOUT;
            break;
        case Servo_Request_E::READ_LOSS_OF_COMM_TIMEOUT:
            response = Servo_Response_E::READ_LOSS_OF_COMM_TIMEOUT;
            break;
        case Servo_Request_E::SET_POSITION_AS_ZERO:
            response = Servo_Response_E::SET_POSITION_AS_ZERO;
            break;
        case Servo_Request_E::SET_POSITION_AS_LOSS_OF_COMM:
            response = Servo_Response_E::SET_POSITION_AS_LOSS_OF_COMM;
            break;
        case Servo_Request_E::READ_CURRENT:
            response = Servo_Response_E::READ_CURRENT;
            break;
        case Servo_Request_E::READ_TEMPERATURE:
            response = Servo_Response_E::READ_TEMPERATURE;
            break;
        case Servo_Request_E::READ_VOLTAGE:
            response = Servo_Response_E::READ_VOLTAGE;
            break;
        case Servo_Request_E::SET_EEPROM_PARAM:
            response = Servo_Response_E::SET_EEPROM_PARAM;
            break;
        case Servo_Request_E::READ_EEPROM_PARAM:
            response = Servo_Response_E::READ_EEPROM_PARAM;
            break;
        case Servo_Request_E::SET_EEPROM_LOW_PARAM:
            response = Servo_Response_E::SET_EEPROM_LOW_PARAM;
            break;
        case Servo_Request_E::READ_EEPROM_LOW_PARAM:
            response = Servo_Response_E::READ_EEPROM_LOW_PARAM;
            break;
        case Servo_Request_E::SET_EEPROM_HIGH_PARAM:
            response = Servo_Response_E::SET_EEPROM_HIGH_PARAM;
            break;
        case Servo_Request_E::READ_EEPROM_HIGH_PARAM:
            response = Servo_Response_E::READ_EEPROM_HIGH_PARAM;
            break;
        case Servo_Request_E::SPECIAL_FEATURE:
            // Some special features may not respond, handle those separately
            response = Servo_Response_E::SPECIAL_FEATURE;
            break;

        case Servo_Request_E::SILENT_SET_POSITION:
        case Servo_Request_E::INVALID:
        default:
            response = Servo_Response_E::INVALID;
            break;
    }

    return response;
}

constexpr bool ServoGetResponseExpectEcho(const Servo_Request_E request)
{
    bool expectEcho = false;

    switch(request)
    {
        case Servo_Request_E::SET_ACTUATOR_ID:
        case Servo_Request_E::SET_LOSS_OF_COMM_POSITION:
        case Servo_Request_E::SET_LOSS_OF_COMM_TIMEOUT:
        case Servo_Request_E::SET_EEPROM_PARAM:
        case Servo_Request_E::SET_EEPROM_LOW_PARAM:
        case Servo_Request_E::SET_EEPROM_HIGH_PARAM:
            expectEcho = true;
            break;
        case Servo_Request_E::READ_ACTUATOR_ID:
        case Servo_Request_E::SILENT_SET_POSITION:
        case Servo_Request_E::SET_POSITION: // Response is actual position
        case Servo_Request_E::READ_POSITION:
        case Servo_Request_E::SET_SCALED_POINT: // Response is actual scaled position
        case Servo_Request_E::READ_SCALED_POSITION:
        case Servo_Request_E::READ_LOSS_OF_COMM_POSITION:
        case Servo_Request_E::READ_LOSS_OF_COMM_TIMEOUT:
        case Servo_Request_E::SET_POSITION_AS_ZERO: // Response is actual position
        case Servo_Request_E::SET_POSITION_AS_LOSS_OF_COMM: // Response is actual position
        case Servo_Request_E::READ_CURRENT:
        case Servo_Request_E::READ_TEMPERATURE:
        case Servo_Request_E::READ_VOLTAGE:
        case Servo_Request_E::READ_EEPROM_PARAM:
        case Servo_Request_E::READ_EEPROM_LOW_PARAM:
        case Servo_Request_E::READ_EEPROM_HIGH_PARAM:
        case Servo_Request_E::SPECIAL_FEATURE:
        case Servo_Request_E::INVALID:
            expectEcho = false;
            break;
    }

    return expectEcho;
}

constexpr bool ServoGetValidId(const uint8_t id)
{
    return (   (id >= SERVO_MIN_ID)
            && (id <= SERVO_MAX_ID)
            && (id != SERVO_BROADCAST_ID) );
}

} // namespace Eim

#endif // SERVO_COMM_TYPES_HPP
