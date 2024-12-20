#ifndef KLINE_COMM_TYPES_HPP
#define KLINE_COMM_TYPES_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Eim
{

enum class Kline_Request_E
{
    WAKE_UP,
    INIT,
    ECM_ID,
    DATA,
    MAX_NUM_REQUEST
};
static constexpr size_t KLINE_MAX_NUM_REQUEST {static_cast<size_t>(Kline_Request_E::MAX_NUM_REQUEST)};

//--------------------------------------------------------------------------------------------------
// Data packing
//--------------------------------------------------------------------------------------------------
struct Kline_Comm_Header_S
{
    uint8_t headerCode;
    uint8_t numBytes;
} __attribute__((packed));
#define KLINE_HEADER_LENGTH (sizeof(Kline_Comm_Header_S))
UTIL_ASSERT(KLINE_HEADER_LENGTH == 2U,
    "Incorrect Kline data size");

//--------------------------------------------------------------------------------------------------
// Request types
//--------------------------------------------------------------------------------------------------
struct Kline_Comm_WakeRequest_S
{
    uint8_t headerCode;
    uint8_t numBytes;
    uint8_t data;
    uint8_t crc;
} __attribute__((packed));
#define KLINE_WAKE_REQUEST_LENGTH (sizeof(Kline_Comm_WakeRequest_S))
UTIL_ASSERT(KLINE_WAKE_REQUEST_LENGTH == 4U,
    "Incorrect Kline data size");

struct Kline_Comm_TableRequest_S
{
    uint8_t headerCode;
    uint8_t numBytes;
    uint8_t table;
    uint8_t address;
    uint8_t crc;
} __attribute__((packed));
#define KLINE_TABLE_REQUEST_LENGTH (sizeof(Kline_Comm_TableRequest_S))
UTIL_ASSERT(KLINE_TABLE_REQUEST_LENGTH == 5U,
    "Incorrect Kline data size");

union Kline_Comm_Request_U
{
    uint8_t startData;
    Kline_Comm_Header_S header;
    Kline_Comm_WakeRequest_S wake;
    Kline_Comm_TableRequest_S table;
} __attribute__((packed));
#define KLINE_MAX_REQUEST_LENGTH (sizeof(Kline_Comm_Request_U))

//--------------------------------------------------------------------------------------------------
// Preformatted requests
//--------------------------------------------------------------------------------------------------
#define KLINE_PREFORMAT_WAKE_REQUEST ( (Kline_Comm_WakeRequest_S)\
    {.headerCode=0xFE, .numBytes=0x04, .data=0x72, .crc=0x8C}\
)

#define KLINE_PREFORMAT_INIT_REQUEST ( (Kline_Comm_TableRequest_S)\
    {.headerCode=0x72, .numBytes=0x05, .table=0x00, .address=0xF0, .crc=0x99}\
)

#define KLINE_PREFORMAT_ECM_ID_REQUEST ( (Kline_Comm_TableRequest_S)\
    {.headerCode=0x72, .numBytes=0x05, .table=0x71, .address=0x00, .crc=0x18}\
)

#define KLINE_PREFORMAT_DATA_REQUEST ( (Kline_Comm_TableRequest_S)\
    {.headerCode=0x72, .numBytes=0x05, .table=0x71, .address=0x11, .crc=0x07}\
)

//--------------------------------------------------------------------------------------------------
// Response types
//--------------------------------------------------------------------------------------------------
struct Kline_Comm_WakeResponse_S
{
    uint8_t headerCode;
    uint8_t numBytes;
    uint8_t data;
    uint8_t crc;
} __attribute__((packed));
#define KLINE_WAKE_RESPONSE_LENGTH (sizeof(Kline_Comm_WakeResponse_S))
UTIL_ASSERT(KLINE_WAKE_RESPONSE_LENGTH == 4U,
    "Incorrect Kline data size");

struct Kline_Comm_TableResponse_S
{
    uint8_t headerCode;
    uint8_t numBytes;
    uint8_t table;
    uint8_t address;
    uint16_t rpm;
    uint8_t tpsVoltage;
    uint8_t tpsAngle;
    uint8_t ectVoltage;
    uint8_t ectTemp;
    uint8_t iatVoltage;
    uint8_t iatTemp;
    uint8_t mapVoltage;
    uint8_t mapPressure;
    uint8_t unused[2U];
    uint8_t batteryVoltage;
    uint8_t vehicleSpeed;
    uint8_t unused2[6U];
    uint8_t crc;
} __attribute__((packed));
#define KLINE_TABLE_RESPONSE_LENGTH (sizeof(Kline_Comm_TableResponse_S))
UTIL_ASSERT(KLINE_TABLE_RESPONSE_LENGTH == 25U,
    "Incorrect Kline data size");

union Kline_Comm_Response_U
{
    uint8_t startData;
    Kline_Comm_Header_S header;
    Kline_Comm_WakeResponse_S wake;
    Kline_Comm_TableResponse_S table;
} __attribute__((packed));
#define KLINE_MAX_RESPONSE_LENGTH (sizeof(Kline_Comm_Response_U))

} // namespace Eim

#endif // KLINE_COMM_TYPES_HPP
