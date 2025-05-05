#include "PT_canReceiver.hpp"
#include "PT_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

// Used for atomic operations
#define MEM_ORDER __ATOMIC_SEQ_CST

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gTESTER_request_RX_ARR[CANRX_PT_TESTER_request_ARR_LEN][CAN_PT_TESTER_request_DLC];
static uint8_t * gTESTER_request_LatestRxPtr = &gTESTER_request_RX_ARR[0U][0U];
static uint32_t gTESTER_request_RxCounter[CANRX_PT_TESTER_request_ARR_LEN];
static uint32_t * gTESTER_request_LatestCounterPtr = &gTESTER_request_RxCounter[0U];
static uint8_t gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_ARR_LEN][CAN_PT_VCU_PcbaVitals_DLC];
static uint8_t * gVCU_PcbaVitals_LatestRxPtr = &gVCU_PcbaVitals_RX_ARR[0U][0U];
static uint32_t gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_ARR_LEN];
static uint32_t * gVCU_PcbaVitals_LatestCounterPtr = &gVCU_PcbaVitals_RxCounter[0U];

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gMidFromIdx[CANRX_PT_NUM_MESSAGES] = {
    CAN_PT_TESTER_request_MID,
    CAN_PT_VCU_PcbaVitals_MID,
};
uint32_t CANRX_PT_GetMidFromIdx(const uint32_t msgIdx)
{
    return gMidFromIdx[msgIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_BrakeLightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0x0C) >> 2);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_BrakeLightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_BrakeLightEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_BrakeLightEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_BrakeLightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_BrakeLightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_BrakeLightEnable(pData);
}

// TESTER_HeadlightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0x30) >> 4);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_HeadlightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_HeadlightEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_HeadlightEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_HeadlightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_HeadlightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_HeadlightEnable(pData);
}

// TESTER_HighBeamEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[2]) & 0xC0) >> 6);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_HighBeamEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_HighBeamEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_HighBeamEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_HighBeamEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_HighBeamEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_HighBeamEnable(pData);
}

// TESTER_HornEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_HornEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[3]) & 0x03);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_HornEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_HornEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_HornEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_HornEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_HornEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_HornEnable(pData);
}

// TESTER_MainRelayEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[2]) & 0x03);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_MainRelayEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_MainRelayEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_MainRelayEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_MainRelayEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_MainRelayEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_MainRelayEnable(pData);
}

// TESTER_Servo_Position
uint16_t CANRX_PT_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    const uint16_t rawVal =
        (pData[0]) +
        (((pData[1]) & 0x3F) << 8);
    return rawVal;
}
uint16_t CANRX_PT_GetSRaw_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_Servo_Position(pData);
}
float_q CANRX_PT_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    int16_t raw = (int16_t)CANRX_PT_GetSRawFromFrame_TESTER_Servo_Position(pData);
    float_q converted;
    if (   (raw == 8192) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        // Sign extend
        const int16_t rawTemp = raw << 2;
        raw = rawTemp >> 2;
        converted = ((decltype(converted.Val()))raw * 0.025F) + 0.0F;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
float_q CANRX_PT_GetS_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_Servo_Position(pData);
}

// TESTER_TurnLeftEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[3]) & 0x0C) >> 2);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_TurnLeftEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_TurnLeftEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_TurnLeftEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_TurnLeftEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_TurnLeftEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_TurnLeftEnable(pData);
}

// TESTER_TurnRightEnable
uint8_t CANRX_PT_GetSRawFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[3]) & 0x30) >> 4);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_TESTER_TurnRightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSRawFromFrame_TESTER_TurnRightEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_TESTER_TurnRightEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_TESTER_TurnRightEnable(pData);
    uint32_q converted;
    if (   (raw == 3U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_TESTER_request_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_TESTER_TurnRightEnable(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_PT_GetSFromFrame_TESTER_TurnRightEnable(pData);
}

// VCU_PCBA_Aps1Pct
uint16_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_Aps1Pct(const uint8_t * const pData)
{
    const uint16_t rawVal =
        (pData[1]) +
        (((pData[2]) & 0x03) << 8);
    return rawVal;
}
uint16_t CANRX_PT_GetSRaw_VCU_PCBA_Aps1Pct(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    return CANRX_PT_GetSRawFromFrame_VCU_PCBA_Aps1Pct(pData);
}
float_q CANRX_PT_GetSFromFrame_VCU_PCBA_Aps1Pct(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX];
    uint16_t raw = (uint16_t)CANRX_PT_GetSRawFromFrame_VCU_PCBA_Aps1Pct(pData);
    float_q converted;
    if (   (raw == 1023U) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT) )
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 0.1F) + 0.0F;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
float_q CANRX_PT_GetS_VCU_PCBA_Aps1Pct(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    return CANRX_PT_GetSFromFrame_VCU_PCBA_Aps1Pct(pData);
}

// VCU_PCBA_BrakeSwitch
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[1]) & 0x04) >> 2);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_BrakeSwitch(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSRawFromFrame_VCU_PCBA_BrakeSwitch(pData);
}
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_VCU_PCBA_BrakeSwitch(pData);
    uint32_q converted;
    if (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT)
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_VCU_PCBA_BrakeSwitch(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSFromFrame_VCU_PCBA_BrakeSwitch(pData);
}

// VCU_PCBA_EngEnable
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngEnable(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[1]) & 0x01);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_EngEnable(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngEnable(pData);
}
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_EngEnable(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngEnable(pData);
    uint32_q converted;
    if (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT)
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_VCU_PCBA_EngEnable(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSFromFrame_VCU_PCBA_EngEnable(pData);
}

// VCU_PCBA_EngStart
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngStart(const uint8_t * const pData)
{
    const uint8_t rawVal =
        (((pData[1]) & 0x02) >> 1);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_VCU_PCBA_EngStart(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngStart(pData);
}
uint32_q CANRX_PT_GetSFromFrame_VCU_PCBA_EngStart(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX];
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_VCU_PCBA_EngStart(pData);
    uint32_q converted;
    if (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT)
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_VCU_PCBA_EngStart(void)
{
    const uint8_t * const pData = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    return CANRX_PT_GetSFromFrame_VCU_PCBA_EngStart(pData);
}

// VCU_PcbaVitalsMux
uint8_t CANRX_PT_GetSRawFromFrame_VCU_PcbaVitalsMux(const uint8_t * const pData)
{
    const uint8_t rawVal =
        ((pData[0]) & 0x0F);
    return rawVal;
}
uint8_t CANRX_PT_GetSRaw_VCU_PcbaVitalsMux(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gVCU_PcbaVitals_LatestRxPtr;
    return CANRX_PT_GetSRawFromFrame_VCU_PcbaVitalsMux(pData);
}
uint32_q CANRX_PT_GetSFromFrame_VCU_PcbaVitalsMux(const uint8_t * const pData)
{
    // This signal belongs to a muxed message but is static. Get counter from latest-received frame
    const uint32_t * const pCounter = gVCU_PcbaVitals_LatestCounterPtr;
    uint8_t raw = (uint8_t)CANRX_PT_GetSRawFromFrame_VCU_PcbaVitalsMux(pData);
    uint32_q converted;
    if (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT)
    {
        converted = SignalStatus_E::SNA;
    }
    else
    {
        converted = ((decltype(converted.Val()))raw * 1U) + 0U;
        converted = SignalStatus_E::VALID;
    }
    return converted;
}
uint32_q CANRX_PT_GetS_VCU_PcbaVitalsMux(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gVCU_PcbaVitals_LatestRxPtr;
    return CANRX_PT_GetSFromFrame_VCU_PcbaVitalsMux(pData);
}

//--------------------------------------------------------------------------------------------------
// Message receive storage functions
//--------------------------------------------------------------------------------------------------
static bool CANRX_ProcessM_TESTER_request(const uint8_t * const pData)
{
    bool success = true;

    gTESTER_request_LatestRxPtr = &gTESTER_request_RX_ARR[0U][0U];
    gTESTER_request_LatestCounterPtr = &gTESTER_request_RxCounter[0U];
    __atomic_store_n(gTESTER_request_LatestCounterPtr, 0U, MEM_ORDER);

    if (success)
    {
        for (uint32_t d = 0U; d < CAN_PT_TESTER_request_DLC; ++d)
        {
            gTESTER_request_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

static bool CANRX_ProcessM_VCU_PcbaVitals(const uint8_t * const pData)
{
    bool success = true;
    const uint32_t muxIdx = CANRX_PT_GetSRawFromFrame_VCU_PcbaVitalsMux(pData);

    switch (muxIdx)
    {
        case 0U:
        {
            gVCU_PcbaVitals_LatestRxPtr = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
            gVCU_PcbaVitals_LatestCounterPtr = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX];
            __atomic_store_n(gVCU_PcbaVitals_LatestCounterPtr, 0U, MEM_ORDER);
            break;
        }
        case 1U:
        {
            gVCU_PcbaVitals_LatestRxPtr = &gVCU_PcbaVitals_RX_ARR[CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
            gVCU_PcbaVitals_LatestCounterPtr = &gVCU_PcbaVitals_RxCounter[CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX];
            __atomic_store_n(gVCU_PcbaVitals_LatestCounterPtr, 0U, MEM_ORDER);
            break;
        }
        default:
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        for (uint32_t d = 0U; d < CAN_PT_VCU_PcbaVitals_DLC; ++d)
        {
            gVCU_PcbaVitals_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Message receive init and run
//--------------------------------------------------------------------------------------------------
bool CANRX_PT_Init(void)
{
    for (uint32_t i = 0U; i < CANRX_PT_TESTER_request_ARR_LEN; ++i)
    {
        gTESTER_request_RxCounter[i] = CANRX_PT_TESTER_request_CYCLE_TIMEOUT;
    }

    for (uint32_t i = 0U; i < CANRX_PT_VCU_PcbaVitals_ARR_LEN; ++i)
    {
        gVCU_PcbaVitals_RxCounter[i] = CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT;
    }

    return true;
}

void CANRX_PT_Run1ms(void)
{
    for (uint32_t i = 0U; i < CANRX_PT_TESTER_request_ARR_LEN; ++i)
    {
        uint32_t cycleTimeoutOverflow_TESTER_request = CANRX_PT_TESTER_request_CYCLE_TIMEOUT + 1U;
        (void)__atomic_add_fetch(&gTESTER_request_RxCounter[i], 1U, MEM_ORDER);
        (void)__atomic_compare_exchange_n(
            &gTESTER_request_RxCounter[i],
            &cycleTimeoutOverflow_TESTER_request,
            CANRX_PT_TESTER_request_CYCLE_TIMEOUT,
            false,
            MEM_ORDER,
            MEM_ORDER
        );
    }

    for (uint32_t i = 0U; i < CANRX_PT_VCU_PcbaVitals_ARR_LEN; ++i)
    {
        uint32_t cycleTimeoutOverflow_VCU_PcbaVitals = CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT + 1U;
        (void)__atomic_add_fetch(&gVCU_PcbaVitals_RxCounter[i], 1U, MEM_ORDER);
        (void)__atomic_compare_exchange_n(
            &gVCU_PcbaVitals_RxCounter[i],
            &cycleTimeoutOverflow_VCU_PcbaVitals,
            CANRX_PT_VCU_PcbaVitals_CYCLE_TIMEOUT,
            false,
            MEM_ORDER,
            MEM_ORDER
        );
    }

}

} // namespace CanGen

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
extern "C" {

bool CANRX_PT_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    bool success = true;

    switch (mid)
    {
        case CAN_PT_TESTER_request_MID:
        {
            if (dlc != CAN_PT_TESTER_request_DLC)
            {
                success = false;
            }
            else
            {
                success = CanGen::CANRX_ProcessM_TESTER_request(pData);
            }
            break;
        }
        case CAN_PT_VCU_PcbaVitals_MID:
        {
            if (dlc != CAN_PT_VCU_PcbaVitals_DLC)
            {
                success = false;
            }
            else
            {
                success = CanGen::CANRX_ProcessM_VCU_PcbaVitals(pData);
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
