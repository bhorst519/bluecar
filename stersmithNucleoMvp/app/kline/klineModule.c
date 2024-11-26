/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "halWrappers.h"
#include "klineCommTypes.h"
#include "klineModule.h"
#include "string.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define KLINE_MAX_TX_BYTES          (KLINE_MAX_REQUEST_LENGTH)
#define KLINE_MAX_RX_BYTES          (KLINE_MAX_REQUEST_LENGTH + KLINE_MAX_RESPONSE_LENGTH) // Request echo

#define KLINE_INIT_LOW_TIME_MS      (70U)
#define KLINE_INIT_HIGH_TIME_MS     (130U)
#define KLINE_RESPONSE_TIMEOUT_MS   (35U)

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
typedef enum
{
    STATE_INIT_PEND,
    STATE_INIT,
    STATE_ACTIVE,
} Kline_State_E;

typedef enum
{
    REQUEST_WAKE_UP,
    REQUEST_INIT,
    REQUEST_ECM_ID,
    REQUEST_DATA,
    MAX_NUM_REQUEST
} Kline_Request_E;

typedef struct
{
    Kline_State_E state;

    uint16_t rpm;
    float tpsVoltage;
    float tpsAngle;
    float ectVoltage;
    float ectTemp;
    float iatVoltage;
    float iatTemp;
    float mapVoltage;
    float mapPressure;
    float batteryVoltage;
    float vehicleSpeed;
} Kline_Data_S;

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static uint8_t gSerialBytesTx[KLINE_MAX_TX_BYTES];
static uint8_t gSerialBytesRx[KLINE_MAX_RX_BYTES];

static Kline_Data_S gKlineData = {0};

static const uint8_t gRequestResponseLength[MAX_NUM_REQUEST] = {
    /* REQUEST_WAKE_UP */   4U,
    /* REQUEST_INIT */      4U,
    /* REQUEST_ECM_ID */    15U,
    /* REQUEST_DATA */      25U,
};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// Process data
//--------------------------------------------------------------------------------------------------
static void KlineProcessData(const Kline_Comm_TableResponse_S * const pTableResponse)
{
    taskENTER_CRITICAL();
    gKlineData.rpm = pTableResponse->rpm;
    gKlineData.tpsVoltage = (float)pTableResponse->tpsVoltage * (5.0F / 256.0F);
    gKlineData.tpsAngle = (float)pTableResponse->tpsAngle / 2.0F;
    gKlineData.ectVoltage = (float)pTableResponse->ectVoltage * (5.0F / 256.0F);
    gKlineData.ectTemp = (float)pTableResponse->ectTemp - 40.0F;
    gKlineData.iatVoltage = (float)pTableResponse->iatVoltage * (5.0F / 256.0F);
    gKlineData.iatTemp = (float)pTableResponse->iatTemp - 40.0F;
    gKlineData.mapVoltage = (float)pTableResponse->mapVoltage * (5.0F / 256.0F);
    gKlineData.mapPressure = (float)pTableResponse->mapPressure;
    gKlineData.batteryVoltage = (float)pTableResponse->batteryVoltage / 10.0F;
    gKlineData.vehicleSpeed = (float)pTableResponse->vehicleSpeed;
    taskEXIT_CRITICAL();
}

//--------------------------------------------------------------------------------------------------
// Communication
//--------------------------------------------------------------------------------------------------
static uint8_t KlineCalculateCrc(const uint8_t * const pData, const uint8_t numBytes)
{
    uint32_t dataSum = 0U;
    for (uint32_t i = 0U; i < numBytes; i++)
    {
        dataSum += pData[i];
    }

    uint32_t crc = 0x100 - (dataSum & 0xFF);
    return (uint8_t)(crc & 0xFF);
}

static bool KlineVerifyCrc(const Kline_Comm_Response_U * const pResponse)
{
    const uint8_t * const pRxData = &pResponse->startData;
    const uint8_t numBytes = pResponse->header.numBytes;
    const uint8_t crcReceived = pRxData[numBytes - 1U];
    const uint8_t crcExpected = KlineCalculateCrc(pRxData, (numBytes - 1U));

    return (crcReceived == crcExpected);
}

static bool KlineVerifyResponse(const Kline_Comm_Request_U * const pRequest, const Kline_Comm_Response_U * const pResponse)
{
    bool success = true;
    const uint8_t numRxBytes = pResponse->header.numBytes;

    if (numRxBytes == 4U)
    {
        success = success && ((pRequest->wake.headerCode & 0x0F) == pResponse->wake.headerCode);
        success = success && (pRequest->wake.data == pResponse->wake.data);
    }
    else
    {
        success = success && ((pRequest->table.headerCode & 0x0F) == pResponse->table.headerCode);
        success = success && (pRequest->table.table == pResponse->table.table);
        success = success && (pRequest->table.address == pResponse->table.address);
    }

    success = success && KlineVerifyCrc(pResponse);

    return success;
}

static bool KlineTransceive(const Kline_Request_E request, Kline_Comm_Response_U * pResponse)
{
    bool success = true;
    Kline_Comm_Request_U * pRequest = (Kline_Comm_Request_U *)(&gSerialBytesTx[0U]);
    uint8_t * pCrc = NULL;

    switch (request)
    {
        case REQUEST_WAKE_UP:
            pRequest->wake = KLINE_PREFORMAT_WAKE_REQUEST;
            pRequest->header.numBytes = KLINE_WAKE_REQUEST_LENGTH;
            pCrc = &pRequest->wake.crc;
            break;
        case REQUEST_INIT:
            pRequest->table = KLINE_PREFORMAT_INIT_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        case REQUEST_ECM_ID:
            pRequest->table = KLINE_PREFORMAT_ECM_ID_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        case REQUEST_DATA:
            pRequest->table = KLINE_PREFORMAT_DATA_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        default:
            success = false;
            break;
    }

    uint8_t numTxBytes = 0U;

    if (success)
    {
        numTxBytes = pRequest->header.numBytes;
        *pCrc = KlineCalculateCrc(&pRequest->startData, (numTxBytes - 1U));
    }

    // Set up for receive
    if (success)
    {
        const uint8_t numRxBytes = gRequestResponseLength[request] + numTxBytes;
        success = HalWrappersUartReceive(SERIAL_KLINE, &gSerialBytesRx[0U], numRxBytes);
    }

    // Initiate transmit
    if (success)
    {
        success = HalWrappersUartTransmit(SERIAL_KLINE, &gSerialBytesTx[0U], numTxBytes);
    }

    // Wait for receive data
    if (success)
    {
        success = HalWrappersUartWait(SERIAL_KLINE, KLINE_RESPONSE_TIMEOUT_MS);
    }

    if (success)
    {
        pResponse = (Kline_Comm_Response_U *)(&gSerialBytesRx[numTxBytes]);
        success = KlineVerifyResponse(pRequest, pResponse);
    }

    return success;
}

static bool KlineSendRequest(const Kline_Request_E request)
{
    Kline_Comm_Response_U * pResponse = NULL;
    const bool success = KlineTransceive(request, pResponse);

    if (success)
    {
        switch (request)
        {
            case REQUEST_DATA:
                KlineProcessData(&pResponse->table);
                break;
            case REQUEST_WAKE_UP:
            case REQUEST_INIT:
            case REQUEST_ECM_ID:
            default:
                // Nothing to do
                break;
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// State management
//--------------------------------------------------------------------------------------------------
static Kline_State_E KlineRunInitPendState(void)
{
    // Idle state for TX pin to sit high
    // Change TX to GPIO output
    HalWrappersSetUartGpio(SERIAL_KLINE, true);
    HalWrappersGpioSet(GPIO_KLINE_TX, true);

    return STATE_INIT;
}

static Kline_State_E KlineRunInitState(void)
{
    HalWrappersGpioSet(GPIO_KLINE_TX, false);
    (void)osDelay(KLINE_INIT_LOW_TIME_MS);
    HalWrappersGpioSet(GPIO_KLINE_TX, true);
    (void)osDelay(KLINE_INIT_HIGH_TIME_MS);
    // Restore UART pins
    HalWrappersSetUartGpio(SERIAL_KLINE, false);

    bool success = true;

    if (success)
    {
        success = KlineSendRequest(REQUEST_WAKE_UP);
    }

    if (success)
    {
        success = KlineSendRequest(REQUEST_INIT);
    }

    return success ? STATE_ACTIVE : STATE_INIT_PEND;
}

static Kline_State_E KlineRunActiveState(void)
{
    const bool success = KlineSendRequest(REQUEST_DATA);

    return success ? STATE_ACTIVE : STATE_INIT_PEND;
}

static Kline_State_E KlineRunStateMachine(void)
{
    const Kline_State_E currentState = gKlineData.state;
    Kline_State_E nextState = currentState;

    switch (currentState)
    {
        case STATE_INIT_PEND:
            nextState = KlineRunInitPendState();
            break;
        case STATE_INIT:
            nextState = KlineRunInitState();
            break;
        case STATE_ACTIVE:
            nextState = KlineRunActiveState();
            break;
        default:
            nextState = STATE_INIT_PEND;
            break;
    }

    return nextState;
}

static void KlineExecuteStateTransition(const Kline_State_E nextState)
{
    (void)nextState;
}

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void KlineModuleInit(void)
{
    gKlineData.state = STATE_INIT_PEND;
}

// Larget message appears to be:
//  * Request: 5 bytes
//  * Response: 25 bytes
// 30 total bytes at 10.4 kbps = 23ms.
// Could run at 10Hz, but init sequene has segments that are > 100ms.
// Could have different runs at 1Hz (for init handling) and 10Hz (for polling) if desired.
void KlineModuleRun(void)
{
    const Kline_State_E nextState = KlineRunStateMachine();

    if (nextState != gKlineData.state)
    {
        KlineExecuteStateTransition(nextState);
        gKlineData.state = nextState;
    }
}

uint16_t KlineGetRpm(void)
{
    return gKlineData.rpm;
}

float KlineGetTpsVoltage(void)
{
    return gKlineData.tpsVoltage;
}

float KlineGetTpsAngle(void)
{
    return gKlineData.tpsAngle;
}

float KlineGetEctVoltage(void)
{
    return gKlineData.ectVoltage;
}

float KlineGetEctTemp(void)
{
    return gKlineData.ectTemp;
}

float KlineGetIatVoltage(void)
{
    return gKlineData.iatVoltage;
}

float KlineGetIatTemp(void)
{
    return gKlineData.iatTemp;
}

float KlineGetMapVoltage(void)
{
    return gKlineData.mapVoltage;
}

float KlineGetMapPressure(void)
{
    return gKlineData.mapPressure;
}

float KlineGetBatteryVoltage(void)
{
    return gKlineData.batteryVoltage;
}

float KlineGetVehicleSpeed(void)
{
    return gKlineData.vehicleSpeed;
}
