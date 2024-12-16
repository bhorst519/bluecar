#ifndef THROTTLE_COMM_TYPES_HPP
#define THROTTLE_COMM_TYPES_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

enum class Throttle_Request_E : uint8_t
{
    INVALID = 0x00,

    SET_ACTUATOR_ID = 0xAA,
    READ_ACTUATOR_ID = 0xDA,

    SILENT_SET_POINT = 0x77,

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

enum class Throttle_Response_E : uint8_t
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

enum class Throttle_Special_Request_E
{
    ACCESS_SPECIAL_FEATURE,
    ACCESS_SPECIAL_FEATURE_RESPONSE,
    RESET,
};

//--------------------------------------------------------------------------------------------------
// Data packing
//--------------------------------------------------------------------------------------------------
static constexpr uint32_t THROTTLE_FRAME_NUM_DATA_BYTES { 4U };

struct Throttle_Comm_Frame_S
{
    uint8_t code;
    uint8_t id;
    uint16_t data;
    uint16_t crc;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Throttle_Comm_Frame_S) == 6U,
    "Incorrect throttle data size");

struct Throttle_Comm_Raw_Frame_S
{
    uint8_t data[THROTTLE_FRAME_NUM_DATA_BYTES];
    uint16_t crc;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Throttle_Comm_Raw_Frame_S) == 6U,
    "Incorrect throttle data size");

union Throttle_Comm_Frame_U
{
    Throttle_Comm_Frame_S frame;
    Throttle_Comm_Raw_Frame_S raw;
} __attribute__((packed));
UTIL_ASSERT(sizeof(Throttle_Comm_Frame_U) == 6U,
    "Incorrect throttle data size");

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/
constexpr Throttle_Response_E ThrottleGetResponseFromRequest(const Throttle_Request_E request)
{
    Throttle_Response_E response = Throttle_Response_E::INVALID;

    switch(request)
    {
        case Throttle_Request_E::SET_ACTUATOR_ID:
            response = Throttle_Response_E::SET_ACTUATOR_ID;
            break;
        case Throttle_Request_E::READ_ACTUATOR_ID:
            response = Throttle_Response_E::READ_ACTUATOR_ID;
            break;
        case Throttle_Request_E::SET_POSITION:
            response = Throttle_Response_E::SET_POSITION;
            break;
        case Throttle_Request_E::READ_POSITION:
            response = Throttle_Response_E::READ_POSITION;
            break;
        case Throttle_Request_E::SET_SCALED_POINT:
            response = Throttle_Response_E::SET_SCALED_POINT;
            break;
        case Throttle_Request_E::READ_SCALED_POSITION:
            response = Throttle_Response_E::READ_SCALED_POSITION;
            break;
        case Throttle_Request_E::SET_LOSS_OF_COMM_POSITION:
            response = Throttle_Response_E::SET_LOSS_OF_COMM_POSITION;
            break;
        case Throttle_Request_E::READ_LOSS_OF_COMM_POSITION:
            response = Throttle_Response_E::READ_LOSS_OF_COMM_POSITION;
            break;
        case Throttle_Request_E::SET_LOSS_OF_COMM_TIMEOUT:
            response = Throttle_Response_E::SET_LOSS_OF_COMM_TIMEOUT;
            break;
        case Throttle_Request_E::READ_LOSS_OF_COMM_TIMEOUT:
            response = Throttle_Response_E::READ_LOSS_OF_COMM_TIMEOUT;
            break;
        case Throttle_Request_E::SET_POSITION_AS_ZERO:
            response = Throttle_Response_E::SET_POSITION_AS_ZERO;
            break;
        case Throttle_Request_E::SET_POSITION_AS_LOSS_OF_COMM:
            response = Throttle_Response_E::SET_POSITION_AS_LOSS_OF_COMM;
            break;
        case Throttle_Request_E::READ_CURRENT:
            response = Throttle_Response_E::READ_CURRENT;
            break;
        case Throttle_Request_E::READ_TEMPERATURE:
            response = Throttle_Response_E::READ_TEMPERATURE;
            break;
        case Throttle_Request_E::READ_VOLTAGE:
            response = Throttle_Response_E::READ_VOLTAGE;
            break;
        case Throttle_Request_E::SET_EEPROM_PARAM:
            response = Throttle_Response_E::SET_EEPROM_PARAM;
            break;
        case Throttle_Request_E::READ_EEPROM_PARAM:
            response = Throttle_Response_E::READ_EEPROM_PARAM;
            break;
        case Throttle_Request_E::SET_EEPROM_LOW_PARAM:
            response = Throttle_Response_E::SET_EEPROM_LOW_PARAM;
            break;
        case Throttle_Request_E::READ_EEPROM_LOW_PARAM:
            response = Throttle_Response_E::READ_EEPROM_LOW_PARAM;
            break;
        case Throttle_Request_E::SET_EEPROM_HIGH_PARAM:
            response = Throttle_Response_E::SET_EEPROM_HIGH_PARAM;
            break;
        case Throttle_Request_E::READ_EEPROM_HIGH_PARAM:
            response = Throttle_Response_E::READ_EEPROM_HIGH_PARAM;
            break;
        case Throttle_Request_E::SPECIAL_FEATURE:
            // Some special features may not respond, handle those separately
            response = Throttle_Response_E::SPECIAL_FEATURE;
            break;

        case Throttle_Request_E::SILENT_SET_POINT:
        case Throttle_Request_E::INVALID:
        default:
            response = Throttle_Response_E::INVALID;
            break;
    }

    return response;
}

} // namespace Eim

#endif // THROTTLE_COMM_TYPES_HPP
