/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "halWrappers.h"
#include "klineCommTypes.hpp"
#include "klineModule.hpp"
#include "string.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Eim
{

#define KLINE_MAX_TX_BYTES          (KLINE_MAX_REQUEST_LENGTH)
#define KLINE_MAX_RX_BYTES          (KLINE_MAX_REQUEST_LENGTH + KLINE_MAX_RESPONSE_LENGTH) // Request echo

#define KLINE_INIT_LOW_TIME_MS      (70U)
#define KLINE_INIT_HIGH_TIME_MS     (130U)
#define KLINE_RESPONSE_TIMEOUT_MS   (35U)

static constexpr uint8_t gRequestResponseLength[KLINE_MAX_NUM_REQUEST] = {
    /* Kline_Request_E::WAKE_UP */  4U,
    /* Kline_Request_E::INIT */     4U,
    /* Kline_Request_E::ECM_ID */   15U,
    /* Kline_Request_E::DATA */     25U,
};

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static uint8_t gSerialBytesTx[KLINE_MAX_TX_BYTES];
static uint8_t gSerialBytesRx[KLINE_MAX_RX_BYTES];

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void KlineModule::Init(void)
{
    // Nothing to do
}

// Larget message appears to be:
//  * Request: 5 bytes
//  * Response: 25 bytes
// 30 total bytes at 10.4 kbps = 23ms.
// Could run at 10Hz, but init sequene has segments that are > 100ms.
// Could have different runs at 1Hz (for init handling) and 10Hz (for polling) if desired.
void KlineModule::Run(void)
{
    const Kline_State_E nextState = RunStateMachine();

    if (nextState != m_state)
    {
        ExecuteStateTransition(nextState);
        m_state = nextState;
    }
}

//--------------------------------------------------------------------------------------------------
// State management
//--------------------------------------------------------------------------------------------------
Kline_State_E KlineModule::RunStateMachine(void)
{
    const Kline_State_E currentState = m_state;
    Kline_State_E nextState = currentState;

    switch (currentState)
    {
        case Kline_State_E::INIT_PEND:
            nextState = RunInitPendState();
            break;
        case Kline_State_E::INIT:
            nextState = RunInitState();
            break;
        case Kline_State_E::ACTIVE:
            nextState = RunActiveState();
            break;
        default:
            nextState = Kline_State_E::INIT_PEND;
            break;
    }

    return nextState;
}

Kline_State_E KlineModule::RunInitPendState(void) const
{
    // Idle state for TX pin to sit high
    // Change TX to GPIO output
    HalWrappersSetUartGpio(SERIAL_KLINE, true);
    HalWrappersGpioSet(GPIO_KLINE_TX, true);

    return Kline_State_E::INIT;
}

Kline_State_E KlineModule::RunInitState(void)
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
        success = SendRequest(Kline_Request_E::WAKE_UP);
    }

    if (success)
    {
        success = SendRequest(Kline_Request_E::INIT);
    }

    return success ? Kline_State_E::ACTIVE : Kline_State_E::INIT_PEND;
}

Kline_State_E KlineModule::RunActiveState(void)
{
    const bool success = SendRequest(Kline_Request_E::DATA);

    return success ? Kline_State_E::ACTIVE : Kline_State_E::INIT_PEND;
}

void KlineModule::ExecuteStateTransition(const Kline_State_E nextState) const
{
    (void)nextState;
}

//--------------------------------------------------------------------------------------------------
// Communication
//--------------------------------------------------------------------------------------------------
uint8_t KlineModule::CalculateCrc(const uint8_t * const pData, const uint8_t numBytes) const
{
    uint32_t dataSum = 0U;
    for (uint32_t i = 0U; i < numBytes; i++)
    {
        dataSum += pData[i];
    }

    uint32_t crc = 0x100 - (dataSum & 0xFF);
    return (uint8_t)(crc & 0xFF);
}

bool KlineModule::VerifyCrc(const Kline_Comm_Response_U * const pResponse) const
{
    const uint8_t * const pRxData = &pResponse->startData;
    const uint8_t numBytes = pResponse->header.numBytes;
    const uint8_t crcReceived = pRxData[numBytes - 1U];
    const uint8_t crcExpected = CalculateCrc(pRxData, (numBytes - 1U));

    return (crcReceived == crcExpected);
}

bool KlineModule::VerifyResponse(const Kline_Comm_Request_U * const pRequest, const Kline_Comm_Response_U * const pResponse) const
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

    success = success && VerifyCrc(pResponse);

    return success;
}

bool KlineModule::Transceive(const Kline_Request_E request, Kline_Comm_Response_U * pResponse) const
{
    bool success = true;
    Kline_Comm_Request_U * pRequest = (Kline_Comm_Request_U *)(&gSerialBytesTx[0U]);
    uint8_t * pCrc = NULL;

    switch (request)
    {
        case Kline_Request_E::WAKE_UP:
        {
            pRequest->wake = KLINE_PREFORMAT_WAKE_REQUEST;
            pRequest->header.numBytes = KLINE_WAKE_REQUEST_LENGTH;
            pCrc = &pRequest->wake.crc;
            break;
        }
        case Kline_Request_E::INIT:
        {
            pRequest->table = KLINE_PREFORMAT_INIT_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        }
        case Kline_Request_E::ECM_ID:
        {
            pRequest->table = KLINE_PREFORMAT_ECM_ID_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        }
        case Kline_Request_E::DATA:
        {
            pRequest->table = KLINE_PREFORMAT_DATA_REQUEST;
            pRequest->header.numBytes = KLINE_TABLE_REQUEST_LENGTH;
            pCrc = &pRequest->table.crc;
            break;
        }
        default:
            success = false;
            break;
    }

    uint8_t numTxBytes = 0U;

    if (success)
    {
        numTxBytes = pRequest->header.numBytes;
        *pCrc = CalculateCrc(&pRequest->startData, (numTxBytes - 1U));
    }

    // Set up for receive
    if (success)
    {
        const uint8_t numRxBytes = gRequestResponseLength[static_cast<size_t>(request)] + numTxBytes;
        success = HalWrappersUartReceive(SERIAL_KLINE, &gSerialBytesRx[0U], numRxBytes);
    }

    // Initiate transmit
    if (success)
    {
        success = HalWrappersUartTransmit(SERIAL_KLINE, &gSerialBytesTx[0U], numTxBytes, false);
    }

    // Wait for receive data
    if (success)
    {
        success = HalWrappersUartWait(SERIAL_KLINE, KLINE_RESPONSE_TIMEOUT_MS);
    }

    if (success)
    {
        pResponse = (Kline_Comm_Response_U *)(&gSerialBytesRx[numTxBytes]);
        success = VerifyResponse(pRequest, pResponse);
    }

    return success;
}

bool KlineModule::SendRequest(const Kline_Request_E request)
{
    Kline_Comm_Response_U * pResponse = NULL;
    const bool success = Transceive(request, pResponse);

    if (success)
    {
        switch (request)
        {
            case Kline_Request_E::DATA:
                ProcessData(&pResponse->table);
                break;
            case Kline_Request_E::WAKE_UP:
            case Kline_Request_E::INIT:
            case Kline_Request_E::ECM_ID:
            default:
                // Nothing to do
                break;
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Process data
//--------------------------------------------------------------------------------------------------
void KlineModule::ProcessData(const Kline_Comm_TableResponse_S * const pTableResponse)
{
    taskENTER_CRITICAL();
    m_rpm = pTableResponse->rpm;
    m_tpsVoltage = (float)pTableResponse->tpsVoltage * (5.0F / 256.0F);
    m_tpsAngle = (float)pTableResponse->tpsAngle / 2.0F;
    m_ectVoltage = (float)pTableResponse->ectVoltage * (5.0F / 256.0F);
    m_ectTemp = (float)pTableResponse->ectTemp - 40.0F;
    m_iatVoltage = (float)pTableResponse->iatVoltage * (5.0F / 256.0F);
    m_iatTemp = (float)pTableResponse->iatTemp - 40.0F;
    m_mapVoltage = (float)pTableResponse->mapVoltage * (5.0F / 256.0F);
    m_mapPressure = (float)pTableResponse->mapPressure;
    m_batteryVoltage = (float)pTableResponse->batteryVoltage / 10.0F;
    m_vehicleSpeed = (float)pTableResponse->vehicleSpeed;
    taskEXIT_CRITICAL();
}

//--------------------------------------------------------------------------------------------------
// Getter interfaces
//--------------------------------------------------------------------------------------------------
uint16_t KlineModule::GetRpm(void) const
{
    return m_rpm;
}

float KlineModule::GetTpsVoltage(void) const
{
    return m_tpsVoltage;
}

float KlineModule::GetTpsAngle(void) const
{
    return m_tpsAngle;
}

float KlineModule::GetEctVoltage(void) const
{
    return m_ectVoltage;
}

float KlineModule::GetEctTemp(void) const
{
    return m_ectTemp;
}

float KlineModule::GetIatVoltage(void) const
{
    return m_iatVoltage;
}

float KlineModule::GetIatTemp(void) const
{
    return m_iatTemp;
}

float KlineModule::GetMapVoltage(void) const
{
    return m_mapVoltage;
}

float KlineModule::GetMapPressure(void) const
{
    return m_mapPressure;
}

float KlineModule::GetBatteryVoltage(void) const
{
    return m_batteryVoltage;
}

float KlineModule::GetVehicleSpeed(void) const
{
    return m_vehicleSpeed;
}

} // namespace Eim