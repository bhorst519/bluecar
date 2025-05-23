#include "DEV_canReceiver.hpp"
#include "DEV_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

// Used for atomic operations
#define MEM_ORDER __ATOMIC_SEQ_CST

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gTESTER_request_RX_ARR[CANRX_DEV_TESTER_request_ARR_LEN][CAN_DEV_TESTER_request_DLC];
static uint8_t * gTESTER_request_LatestRxPtr = &gTESTER_request_RX_ARR[0U][0U];
static uint32_t gTESTER_request_RxCounter[CANRX_DEV_TESTER_request_ARR_LEN];
static uint32_t * gTESTER_request_LatestCounterPtr = &gTESTER_request_RxCounter[0U];

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gMidFromIdx[CANRX_DEV_NUM_MESSAGES] = {
    CAN_DEV_TESTER_request_MID,
};
uint32_t CANRX_DEV_GetMidFromIdx(const uint32_t msgIdx)
{
    return gMidFromIdx[msgIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// TESTER_Servo_Position
uint16_t CANRX_DEV_GetSRawFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    const uint16_t rawVal =
        (pData[0]) +
        (((pData[1]) & 0x3F) << 8);
    return rawVal;
}
uint16_t CANRX_DEV_GetSRaw_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_DEV_GetSRawFromFrame_TESTER_Servo_Position(pData);
}
float_q CANRX_DEV_GetSFromFrame_TESTER_Servo_Position(const uint8_t * const pData)
{
    const uint32_t * const pCounter = &gTESTER_request_RxCounter[0U];
    int16_t raw = (int16_t)CANRX_DEV_GetSRawFromFrame_TESTER_Servo_Position(pData);
    float_q converted;
    if (   (raw == 8192) // SNA value
        || (__atomic_load_n(pCounter, MEM_ORDER) >= CANRX_DEV_TESTER_request_CYCLE_TIMEOUT) )
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
float_q CANRX_DEV_GetS_TESTER_Servo_Position(void)
{
    const uint8_t * const pData = &gTESTER_request_RX_ARR[0U][0U];
    return CANRX_DEV_GetSFromFrame_TESTER_Servo_Position(pData);
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
        for (uint32_t d = 0U; d < CAN_DEV_TESTER_request_DLC; ++d)
        {
            gTESTER_request_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Message receive init and run
//--------------------------------------------------------------------------------------------------
bool CANRX_DEV_Init(void)
{
    for (uint32_t i = 0U; i < CANRX_DEV_TESTER_request_ARR_LEN; ++i)
    {
        gTESTER_request_RxCounter[i] = CANRX_DEV_TESTER_request_CYCLE_TIMEOUT;
    }

    return true;
}

void CANRX_DEV_Run1ms(void)
{
    for (uint32_t i = 0U; i < CANRX_DEV_TESTER_request_ARR_LEN; ++i)
    {
        uint32_t cycleTimeoutOverflow_TESTER_request = CANRX_DEV_TESTER_request_CYCLE_TIMEOUT + 1U;
        (void)__atomic_add_fetch(&gTESTER_request_RxCounter[i], 1U, MEM_ORDER);
        (void)__atomic_compare_exchange_n(
            &gTESTER_request_RxCounter[i],
            &cycleTimeoutOverflow_TESTER_request,
            CANRX_DEV_TESTER_request_CYCLE_TIMEOUT,
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

bool CANRX_DEV_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    bool success = true;

    switch (mid)
    {
        case CAN_DEV_TESTER_request_MID:
        {
            if (dlc != CAN_DEV_TESTER_request_DLC)
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
