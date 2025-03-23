#include "EIM_canReceiver.hpp"
#include "EIM_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gTESTER_request_RX_ARR[CANRX_EIM_TESTER_request_ARR_LEN][CAN_EIM_TESTER_request_DLC];
static uint8_t * gTESTER_request_LatestRxPtr = &gTESTER_request_RX_ARR[0U][0U];
static bool gTESTER_request_EverReceived[CANRX_EIM_TESTER_request_ARR_LEN];

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gMidFromIdx[CANRX_EIM_NUM_MESSAGES] = {
    CAN_EIM_TESTER_request_MID,
};
uint32_t CANRX_EIM_GetMidFromIdx(const uint32_t msgIdx)
{
    return gMidFromIdx[msgIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_TurnRightEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[3]) & 0x30) >> 4);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_TurnRightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_TurnRightEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_TurnRightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_TurnRightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_TurnRightEnable(pData);
}

// TESTER_TurnLeftEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[3]) & 0x0C) >> 2);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_TurnLeftEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_TurnLeftEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_TurnLeftEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_TurnLeftEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_TurnLeftEnable(pData);
}

// TESTER_HornEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_HornEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[3]) & 0x03);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_HornEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_HornEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_HornEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_HornEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_HornEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_HornEnable(pData);
}

// TESTER_HighBeamEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0xC0) >> 6);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_HighBeamEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_HighBeamEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_HighBeamEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_HighBeamEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_HighBeamEnable(pData);
}

// TESTER_HeadlightEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0x30) >> 4);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_HeadlightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_HeadlightEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_HeadlightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_HeadlightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_HeadlightEnable(pData);
}

// TESTER_BrakeLightEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0x0C) >> 2);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_BrakeLightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_BrakeLightEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_BrakeLightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_BrakeLightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_BrakeLightEnable(pData);
}

// TESTER_MainRelayEnable
uint8_t CANRX_EIM_GetSRawFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[2]) & 0x03);
    return rawVal;
}
uint8_t CANRX_EIM_GetSRaw_TESTER_MainRelayEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_MainRelayEnable(pData);
}
uint32_q CANRX_EIM_GetSFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_EIM_GetSRawFromFrame_TESTER_MainRelayEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((( decltype(converted.Val()) )raw) * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_EIM_GetS_TESTER_MainRelayEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_MainRelayEnable(pData);
}

// TESTER_Servo_Position
uint16_t CANRX_EIM_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    const uint16_t rawVal =
        (pData[0]) +
        (((pData[1]) & 0x3F) << 8);
    return rawVal;
}
uint16_t CANRX_EIM_GetSRaw_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSRawFromFrame_TESTER_Servo_Position(pData);
}
float_q CANRX_EIM_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    int16_t raw = (int16_t)CANRX_EIM_GetSRawFromFrame_TESTER_Servo_Position(pData);
    float_q converted;
    if (   (raw == 8192) // SNA value
        || (!gTESTER_request_EverReceived[0U]) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        // Sign extend
        const int16_t rawTemp = raw << 2;
        raw = rawTemp >> 2;
        converted = ((( decltype(converted.Val()) )raw) * 0.025F) + 0.0F;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
float_q CANRX_EIM_GetS_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_EIM_GetSFromFrame_TESTER_Servo_Position(pData);
}

//--------------------------------------------------------------------------------------------------
// Message receive storage functions
//--------------------------------------------------------------------------------------------------
static bool CANRX_ProcessM_TESTER_request(const uint8_t * const pData)
{
    bool success = true;

    gTESTER_request_LatestRxPtr = &gTESTER_request_RX_ARR[0U][0U];
    gTESTER_request_EverReceived[0U] = true;

    if (success)
    {
        for (uint32_t d = 0U; d < CAN_EIM_TESTER_request_DLC; ++d)
        {
            gTESTER_request_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

} // namespace CanGen

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
extern "C" {

bool CANRX_EIM_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    bool success = true;

    switch (mid)
    {
        case CAN_EIM_TESTER_request_MID:
        {
            if (dlc != CAN_EIM_TESTER_request_DLC)
            {
                success = false;
            }
            else
            {
                success = CanGen::CANRX_ProcessM_TESTER_request(pData);
            }
            break;
        }
        default:
        {
            success = false;
            break;
        }
    }

    return success;
}

} // extern "C"
