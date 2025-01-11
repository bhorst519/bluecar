#include "SAMPLE_canReceiver.h"
#include "SAMPLE_messageInfo.h"
#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_ARR_LEN][CAN_SAMPLE_SAMPLE_B_alertLog_DLC];
static uint8_t * gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[0U][0U];
static uint8_t gSAMPLE_B_alertMatrix_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertMatrix_ARR_LEN][CAN_SAMPLE_SAMPLE_B_alertMatrix_DLC];
static uint8_t * gSAMPLE_B_alertMatrix_LatestRxPtr = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gMidFromIdx[CANRX_SAMPLE_NUM_MESSAGES] = {
    CAN_SAMPLE_SAMPLE_B_alertLog_MID,
    CAN_SAMPLE_SAMPLE_B_alertMatrix_MID,
};
uint32_t CANRX_SAMPLE_GetMidFromIdx(const uint32_t msgIdx)
{
    return gMidFromIdx[msgIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// SAMPLE_B_alertID
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertID(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[0]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_alertID(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_alertLog_LatestRxPtr;
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertID(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertID(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertID(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_alertID(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_alertLog_LatestRxPtr;
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertID(pData);
}

// SAMPLE_B_alertState
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertState(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x80) >> 7);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_alertState(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_alertLog_LatestRxPtr;
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertState(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertState(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertState(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_alertState(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_alertLog_LatestRxPtr;
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertState(pData);
}

// SAMPLE_B_a005_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x01);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data1(pData);
}

// SAMPLE_B_a005_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[2]) & 0x02) >> 1);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data2(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data2(pData);
}

// SAMPLE_B_a006_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data1(pData);
}

// SAMPLE_B_a006_data2
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[4]) + ((pData[5]) << 8);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data2(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data2(pData);
}

// SAMPLE_B_a008_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data1(pData);
}

// SAMPLE_B_a008_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[4]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data2(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data2(pData);
}

// SAMPLE_B_a008_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data3(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data3(pData);
}

// SAMPLE_B_a008_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x01);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data4(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data4(pData);
}

// SAMPLE_B_a008_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x02) >> 1);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data5(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data5(pData);
}

// SAMPLE_B_a009_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data1(pData);
}

// SAMPLE_B_a009_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[4]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data2(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data2(pData);
}

// SAMPLE_B_a009_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data3(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data3(pData);
}

// SAMPLE_B_a009_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x01);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data4(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data4(pData);
}

// SAMPLE_B_a009_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x02) >> 1);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data5(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data5(pData);
}

// SAMPLE_B_a020_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data1(pData);
}

// SAMPLE_B_a020_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[3]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data2(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data2(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data2(pData);
}

// SAMPLE_B_a020_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[4]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data3(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data3(pData);
}

// SAMPLE_B_a020_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data4(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data4(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data4(pData);
}

// SAMPLE_B_a020_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[6]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data5(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data5(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data5(pData);
}

// SAMPLE_B_a021_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data1(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data1(pData);
}

// SAMPLE_B_a021_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[3]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data2(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data2(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a021_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data2(pData);
}

// SAMPLE_B_a021_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[4]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data3(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data3(pData);
}

// SAMPLE_B_a021_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data4(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data4(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a021_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data4(pData);
}

// SAMPLE_B_a021_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data5(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data5(pData);
}

// SAMPLE_B_a021_data6
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data6(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[7]) & 0x7F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data6(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data6(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data6(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data6(pData);
}

// SAMPLE_B_a047_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + (((pData[3]) & 0x03) << 8);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data1(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data1(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data1(pData);
}

// SAMPLE_B_a047_data2
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[3]) & 0xFC) >> 2) + (((pData[4]) & 0x0F) << 6);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data2(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data2(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data2(pData);
}

// SAMPLE_B_a047_data3
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[4]) & 0xF0) >> 4) + (((pData[5]) & 0x3F) << 4);
    return rawVal;
}
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data3(pData);
}
int32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data3(const uint8_t * const pData)
{
    int16_t raw = (int16_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data3(pData);
    // Sign extend
    raw = (raw << 6) >> 6;
    int32_t converted = (((int32_t)raw) * 5) + 0;
    return converted;
}
int32_t CANRX_SAMPLE_GetS_SAMPLE_B_a047_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data3(pData);
}

// SAMPLE_B_a047_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[5]) & 0xC0) >> 6) + (((pData[6]) & 0x3F) << 2);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data4(pData);
}
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data4(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data4(pData);
}

// SAMPLE_B_a047_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0xC0) >> 6) + (((pData[7]) & 0x3F) << 2);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data5(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a047_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data5(pData);
}

// SAMPLE_B_matrixIndex
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_matrixIndex(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[0]) & 0x0F);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_matrixIndex(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_matrixIndex(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_matrixIndex(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_matrixIndex(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_matrixIndex(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_matrixIndex(pData);
}

// SAMPLE_B_a005_alert5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_alert5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x10) >> 4);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_alert5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_alert5(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_alert5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_alert5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_alert5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_alert5(pData);
}

// SAMPLE_B_a006_alert6
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_alert6(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x20) >> 5);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_alert6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_alert6(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_alert6(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_alert6(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_alert6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_alert6(pData);
}

// SAMPLE_B_a007_alert7
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a007_alert7(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x40) >> 6);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a007_alert7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a007_alert7(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a007_alert7(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a007_alert7(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a007_alert7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a007_alert7(pData);
}

// SAMPLE_B_a008_alert8
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_alert8(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x80) >> 7);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_alert8(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_alert8(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_alert8(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_alert8(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_alert8(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_alert8(pData);
}

// SAMPLE_B_a009_alert9
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_alert9(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[1]) & 0x01);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_alert9(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_alert9(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_alert9(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_alert9(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_alert9(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_alert9(pData);
}

// SAMPLE_B_a020_alert20
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_alert20(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x02) >> 1);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_alert20(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_alert20(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_alert20(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_alert20(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_alert20(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_alert20(pData);
}

// SAMPLE_B_a021_alert21
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_alert21(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x04) >> 2);
    return rawVal;
}
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_alert21(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_alert21(pData);
}
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_alert21(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_alert21(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_alert21(void)
{
    const uint8_t * const pData = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];
    return CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_alert21(pData);
}

//--------------------------------------------------------------------------------------------------
// Message receive storage functions
//--------------------------------------------------------------------------------------------------
static bool CANRX_ProcessM_SAMPLE_B_alertLog(const uint8_t * const pData)
{
    bool success = true;
    const uint32_t muxIdx = CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertID(pData);

    switch (muxIdx)
    {
        case 5U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
            break;
        }
        case 6U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
            break;
        }
        case 8U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
            break;
        }
        case 9U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
            break;
        }
        case 20U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
            break;
        }
        case 21U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
            break;
        }
        case 47U:
        {
            gSAMPLE_B_alertLog_LatestRxPtr = &gSAMPLE_B_alertLog_RX_ARR[CANRX_SAMPLE_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
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
        for (uint32_t d = 0U; d < CAN_SAMPLE_SAMPLE_B_alertLog_DLC; ++d)
        {
            gSAMPLE_B_alertLog_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

static bool CANRX_ProcessM_SAMPLE_B_alertMatrix(const uint8_t * const pData)
{
    bool success = true;

    gSAMPLE_B_alertMatrix_LatestRxPtr = &gSAMPLE_B_alertMatrix_RX_ARR[0U][0U];

    if (success)
    {
        for (uint32_t d = 0U; d < CAN_SAMPLE_SAMPLE_B_alertMatrix_DLC; ++d)
        {
            gSAMPLE_B_alertMatrix_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
bool CANRX_SAMPLE_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    bool success = true;

    switch (mid)
    {
        case CAN_SAMPLE_SAMPLE_B_alertLog_MID:
        {
            if (dlc != CAN_SAMPLE_SAMPLE_B_alertLog_DLC)
            {
                success = false;
            }
            else
            {
                success = CANRX_ProcessM_SAMPLE_B_alertLog(pData);
            }
            break;
        }
        case CAN_SAMPLE_SAMPLE_B_alertMatrix_MID:
        {
            if (dlc != CAN_SAMPLE_SAMPLE_B_alertMatrix_DLC)
            {
                success = false;
            }
            else
            {
                success = CANRX_ProcessM_SAMPLE_B_alertMatrix(pData);
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
