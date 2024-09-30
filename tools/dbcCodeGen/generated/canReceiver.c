#include "messageInfo.h"
#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_RX_ARR_LEN][SAMPLE_A_alertLog_DLC];
static uint8_t * gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[0U][0U];
static uint8_t gSAMPLE_A_alertMatrix_RX_ARR[SAMPLE_A_alertMatrix_RX_ARR_LEN][SAMPLE_A_alertMatrix_DLC];
static uint8_t * gSAMPLE_A_alertMatrix_LatestRxPtr = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
static uint8_t gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_RX_ARR_LEN][SAMPLE_B_debug_DLC];
static uint8_t * gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[0U][0U];

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// SAMPLE_A_alertID
static uint8_t GetSRawFromFrame_SAMPLE_A_alertID(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[0]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_alertID(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_A_alertLog_LatestRxPtr;
    return GetSRawFromFrame_SAMPLE_A_alertID(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_alertID(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_alertID(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_alertID(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_A_alertLog_LatestRxPtr;
    return GetSFromFrame_SAMPLE_A_alertID(pData);
}

// SAMPLE_A_alertState
static uint8_t GetSRawFromFrame_SAMPLE_A_alertState(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x80) >> 7);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_alertState(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_A_alertLog_LatestRxPtr;
    return GetSRawFromFrame_SAMPLE_A_alertState(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_alertState(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_alertState(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_alertState(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_A_alertLog_LatestRxPtr;
    return GetSFromFrame_SAMPLE_A_alertState(pData);
}

// SAMPLE_A_a005_data1
static uint8_t GetSRawFromFrame_SAMPLE_A_a005_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x01);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a005_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a005_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a005_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a005_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a005_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a005_data1(pData);
}

// SAMPLE_A_a005_data2
static uint8_t GetSRawFromFrame_SAMPLE_A_a005_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[2]) & 0x02) >> 1);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a005_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a005_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a005_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a005_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a005_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a005_data2(pData);
}

// SAMPLE_A_a006_data1
static uint16_t GetSRawFromFrame_SAMPLE_A_a006_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_A_a006_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a006_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a006_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_A_a006_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a006_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a006_data1(pData);
}

// SAMPLE_A_a006_data2
static uint16_t GetSRawFromFrame_SAMPLE_A_a006_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[4]) + ((pData[5]) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_A_a006_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a006_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a006_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_A_a006_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a006_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a006_data2(pData);
}

// SAMPLE_A_a008_data1
static uint16_t GetSRawFromFrame_SAMPLE_A_a008_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_A_a008_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_A_a008_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a008_data1(pData);
}

// SAMPLE_A_a008_data2
static uint8_t GetSRawFromFrame_SAMPLE_A_a008_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[4]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a008_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a008_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a008_data2(pData);
}

// SAMPLE_A_a008_data3
static uint8_t GetSRawFromFrame_SAMPLE_A_a008_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a008_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a008_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a008_data3(pData);
}

// SAMPLE_A_a008_data4
static uint8_t GetSRawFromFrame_SAMPLE_A_a008_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x01);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a008_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a008_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a008_data4(pData);
}

// SAMPLE_A_a008_data5
static uint8_t GetSRawFromFrame_SAMPLE_A_a008_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x02) >> 1);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a008_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a008_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a008_data5(pData);
}

// SAMPLE_A_a009_data1
static uint16_t GetSRawFromFrame_SAMPLE_A_a009_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[2]) + ((pData[3]) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_A_a009_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_A_a009_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a009_data1(pData);
}

// SAMPLE_A_a009_data2
static uint8_t GetSRawFromFrame_SAMPLE_A_a009_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[4]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a009_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a009_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a009_data2(pData);
}

// SAMPLE_A_a009_data3
static uint8_t GetSRawFromFrame_SAMPLE_A_a009_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a009_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a009_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a009_data3(pData);
}

// SAMPLE_A_a009_data4
static uint8_t GetSRawFromFrame_SAMPLE_A_a009_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x01);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a009_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a009_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a009_data4(pData);
}

// SAMPLE_A_a009_data5
static uint8_t GetSRawFromFrame_SAMPLE_A_a009_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x02) >> 1);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a009_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a009_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a009_data5(pData);
}

// SAMPLE_A_a020_data1
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a020_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a020_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a020_data1(pData);
}

// SAMPLE_A_a020_data2
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[3]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_data2(pData);
}
static float GetSFromFrame_SAMPLE_A_a020_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_data2(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_A_a020_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a020_data2(pData);
}

// SAMPLE_A_a020_data3
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[4]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a020_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a020_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a020_data3(pData);
}

// SAMPLE_A_a020_data4
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_data4(pData);
}
static float GetSFromFrame_SAMPLE_A_a020_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_data4(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_A_a020_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a020_data4(pData);
}

// SAMPLE_A_a020_data5
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[6]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_data5(pData);
}
static float GetSFromFrame_SAMPLE_A_a020_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_data5(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_A_a020_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a020_data5(pData);
}

// SAMPLE_A_a021_data1
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a021_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a021_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data1(pData);
}

// SAMPLE_A_a021_data2
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[3]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data2(pData);
}
static float GetSFromFrame_SAMPLE_A_a021_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data2(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_A_a021_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data2(pData);
}

// SAMPLE_A_a021_data3
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[4]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a021_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a021_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data3(pData);
}

// SAMPLE_A_a021_data4
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data4(pData);
}
static float GetSFromFrame_SAMPLE_A_a021_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data4(pData);
    float converted = (((float)raw) * 0.5F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_A_a021_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data4(pData);
}

// SAMPLE_A_a021_data5
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a021_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a021_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data5(pData);
}

// SAMPLE_A_a021_data6
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_data6(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[7]) & 0x7F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_data6(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a021_data6(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_data6(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a021_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_A_a021_data6(pData);
}

// SAMPLE_A_matrixIndex
static uint8_t GetSRawFromFrame_SAMPLE_A_matrixIndex(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[0]) & 0x0F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_matrixIndex(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_matrixIndex(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_matrixIndex(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_matrixIndex(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_matrixIndex(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_matrixIndex(pData);
}

// SAMPLE_A_a005_alert5
static uint8_t GetSRawFromFrame_SAMPLE_A_a005_alert5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x10) >> 4);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a005_alert5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a005_alert5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a005_alert5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a005_alert5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a005_alert5(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a005_alert5(pData);
}

// SAMPLE_A_a006_alert6
static uint8_t GetSRawFromFrame_SAMPLE_A_a006_alert6(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x20) >> 5);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a006_alert6(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a006_alert6(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a006_alert6(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a006_alert6(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a006_alert6(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a006_alert6(pData);
}

// SAMPLE_A_a007_alert7
static uint8_t GetSRawFromFrame_SAMPLE_A_a007_alert7(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x40) >> 6);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a007_alert7(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a007_alert7(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a007_alert7(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a007_alert7(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a007_alert7(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a007_alert7(pData);
}

// SAMPLE_A_a008_alert8
static uint8_t GetSRawFromFrame_SAMPLE_A_a008_alert8(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[0]) & 0x80) >> 7);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a008_alert8(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a008_alert8(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a008_alert8(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a008_alert8(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a008_alert8(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a008_alert8(pData);
}

// SAMPLE_A_a009_alert9
static uint8_t GetSRawFromFrame_SAMPLE_A_a009_alert9(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[1]) & 0x01);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a009_alert9(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a009_alert9(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a009_alert9(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a009_alert9(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a009_alert9(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a009_alert9(pData);
}

// SAMPLE_A_a020_alert20
static uint8_t GetSRawFromFrame_SAMPLE_A_a020_alert20(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x02) >> 1);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a020_alert20(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a020_alert20(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a020_alert20(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a020_alert20(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a020_alert20(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a020_alert20(pData);
}

// SAMPLE_A_a021_alert21
static uint8_t GetSRawFromFrame_SAMPLE_A_a021_alert21(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[1]) & 0x04) >> 2);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_A_a021_alert21(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSRawFromFrame_SAMPLE_A_a021_alert21(pData);
}
static uint32_t GetSFromFrame_SAMPLE_A_a021_alert21(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_A_a021_alert21(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_A_a021_alert21(void)
{
    const uint8_t * const pData = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];
    return GetSFromFrame_SAMPLE_A_a021_alert21(pData);
}

// SAMPLE_B_debugMultiplexer
static uint8_t GetSRawFromFrame_SAMPLE_B_debugMultiplexer(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[0]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_debugMultiplexer(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_debug_LatestRxPtr;
    return GetSRawFromFrame_SAMPLE_B_debugMultiplexer(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_debugMultiplexer(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_debugMultiplexer(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_debugMultiplexer(void)
{
    // This signal belongs to a muxed message but is static. Get contents from latest-received frame
    const uint8_t * const pData = gSAMPLE_B_debug_LatestRxPtr;
    return GetSFromFrame_SAMPLE_B_debugMultiplexer(pData);
}

// SAMPLE_B_m0_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m0_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x03) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m0_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m0_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m0_data1(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m0_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data1(pData);
}

// SAMPLE_B_m0_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m0_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xFC) >> 2) + (((pData[3]) & 0x0F) << 6);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m0_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m0_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m0_data2(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m0_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data2(pData);
}

// SAMPLE_B_m0_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m0_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[3]) & 0xF0) >> 4) + (((pData[4]) & 0x3F) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m0_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m0_data3(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m0_data3(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m0_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data3(pData);
}

// SAMPLE_B_m0_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m0_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[4]) & 0xC0) >> 6) + ((pData[5]) << 2);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m0_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m0_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m0_data4(pData);
    float converted = (((float)raw) * 0.002F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m0_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data4(pData);
}

// SAMPLE_B_m0_data5
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x3F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data5(pData);
}
static float GetSFromFrame_SAMPLE_B_m0_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data5(pData);
    float converted = (((float)raw) * 0.025F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m0_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data5(pData);
}

// SAMPLE_B_m0_data6
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data6(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x40) >> 6);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data6(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data6(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data6(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data6(pData);
}

// SAMPLE_B_m0_data7
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data7(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0x80) >> 7);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data7(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data7(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data7(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data7(pData);
}

// SAMPLE_B_m0_data8
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data8(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[7]) & 0x01);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data8(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data8(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data8(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data8(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data8(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data8(pData);
}

// SAMPLE_B_m0_data9
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data9(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x02) >> 1);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data9(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data9(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data9(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data9(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data9(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data9(pData);
}

// SAMPLE_B_m0_data10
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data10(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x04) >> 2);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data10(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data10(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data10(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data10(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data10(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data10(pData);
}

// SAMPLE_B_m0_data11
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data11(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x08) >> 3);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data11(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data11(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data11(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data11(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data11(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data11(pData);
}

// SAMPLE_B_m0_data12
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data12(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x10) >> 4);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data12(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data12(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data12(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data12(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data12(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data12(pData);
}

// SAMPLE_B_m0_data13
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data13(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x20) >> 5);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data13(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data13(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data13(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data13(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data13(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data13(pData);
}

// SAMPLE_B_m0_data14
static uint8_t GetSRawFromFrame_SAMPLE_B_m0_data14(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0x40) >> 6);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m0_data14(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m0_data14(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m0_data14(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m0_data14(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m0_data14(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m0_data14(pData);
}

// SAMPLE_B_m1_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m1_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x0F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m1_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m1_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m1_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m1_data1(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m1_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m1_data1(pData);
}

// SAMPLE_B_m1_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m1_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xF0) >> 4) + ((pData[3]) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m1_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m1_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m1_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m1_data2(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m1_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m1_data2(pData);
}

// SAMPLE_B_m1_data3
static uint8_t GetSRawFromFrame_SAMPLE_B_m1_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[4]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m1_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m1_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m1_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m1_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m1_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m1_data3(pData);
}

// SAMPLE_B_m1_data4
static uint8_t GetSRawFromFrame_SAMPLE_B_m1_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[5]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m1_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m1_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m1_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m1_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m1_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m1_data4(pData);
}

// SAMPLE_B_m1_data5
static uint16_t GetSRawFromFrame_SAMPLE_B_m1_data5(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[6]) + (((pData[7]) & 0x0F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m1_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m1_data5(pData);
}
static float GetSFromFrame_SAMPLE_B_m1_data5(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m1_data5(pData);
    float converted = (((float)raw) * 0.02F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m1_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m1_data5(pData);
}

// SAMPLE_B_m2_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m2_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x07) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m2_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m2_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m2_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m2_data1(pData);
    float converted = (((float)raw) * 0.1F) + -50.0F;
    return converted;
}
static float GetS_SAMPLE_B_m2_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m2_data1(pData);
}

// SAMPLE_B_m2_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m2_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xF8) >> 3) + (((pData[3]) & 0x3F) << 5);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m2_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m2_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m2_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m2_data2(pData);
    float converted = (((float)raw) * 0.1F) + -50.0F;
    return converted;
}
static float GetS_SAMPLE_B_m2_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m2_data2(pData);
}

// SAMPLE_B_m2_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m2_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[3]) & 0xC0) >> 6) + ((pData[4]) << 2) + (((pData[5]) & 0x01) << 10);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m2_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m2_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m2_data3(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m2_data3(pData);
    float converted = (((float)raw) * 0.1F) + -50.0F;
    return converted;
}
static float GetS_SAMPLE_B_m2_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m2_data3(pData);
}

// SAMPLE_B_m2_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m2_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[5]) & 0xFE) >> 1) + (((pData[6]) & 0x0F) << 7);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m2_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m2_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m2_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m2_data4(pData);
    float converted = (((float)raw) * 0.1F) + -50.0F;
    return converted;
}
static float GetS_SAMPLE_B_m2_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m2_data4(pData);
}

// SAMPLE_B_m2_data5
static uint16_t GetSRawFromFrame_SAMPLE_B_m2_data5(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[6]) & 0xF0) >> 4) + ((pData[7]) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m2_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m2_data5(pData);
}
static float GetSFromFrame_SAMPLE_B_m2_data5(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m2_data5(pData);
    float converted = (((float)raw) * 0.002F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m2_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m2_data5(pData);
}

// SAMPLE_B_m3_data1
static uint8_t GetSRawFromFrame_SAMPLE_B_m3_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[1]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m3_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m3_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m3_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m3_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data1(pData);
}

// SAMPLE_B_m3_data2
static uint8_t GetSRawFromFrame_SAMPLE_B_m3_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[2]) & 0x0F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m3_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m3_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m3_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m3_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data2(pData);
}

// SAMPLE_B_m3_data3
static uint8_t GetSRawFromFrame_SAMPLE_B_m3_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[2]) & 0xF0) >> 4) + (((pData[3]) & 0x07) << 4);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m3_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m3_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m3_data3(pData);
    float converted = (((float)raw) * 0.1F) + 90.0F;
    return converted;
}
static float GetS_SAMPLE_B_m3_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data3(pData);
}

// SAMPLE_B_m3_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m3_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[3]) & 0xF8) >> 3) + (((pData[4]) & 0x1F) << 5);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m3_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m3_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m3_data4(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m3_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data4(pData);
}

// SAMPLE_B_m3_data5
static uint8_t GetSRawFromFrame_SAMPLE_B_m3_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[4]) & 0xE0) >> 5) + (((pData[5]) & 0x0F) << 3);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m3_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data5(pData);
}
static float GetSFromFrame_SAMPLE_B_m3_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m3_data5(pData);
    float converted = (((float)raw) * 0.2F) + -0.2F;
    return converted;
}
static float GetS_SAMPLE_B_m3_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data5(pData);
}

// SAMPLE_B_m3_data6
static uint16_t GetSRawFromFrame_SAMPLE_B_m3_data6(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[5]) & 0xF0) >> 4) + (((pData[6]) & 0x3F) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m3_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data6(pData);
}
static float GetSFromFrame_SAMPLE_B_m3_data6(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m3_data6(pData);
    float converted = (((float)raw) * 0.2F) + -0.2F;
    return converted;
}
static float GetS_SAMPLE_B_m3_data6(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data6(pData);
}

// SAMPLE_B_m3_data7
static uint16_t GetSRawFromFrame_SAMPLE_B_m3_data7(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[6]) & 0xC0) >> 6) + ((pData[7]) << 2);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m3_data7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m3_data7(pData);
}
static float GetSFromFrame_SAMPLE_B_m3_data7(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m3_data7(pData);
    float converted = (((float)raw) * 0.1F) + -0.1F;
    return converted;
}
static float GetS_SAMPLE_B_m3_data7(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m3_data7(pData);
}

// SAMPLE_B_m4_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m4_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x0F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m4_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m4_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m4_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m4_data1(pData);
    float converted = (((float)raw) * 0.015F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m4_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m4_data1(pData);
}

// SAMPLE_B_m4_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m4_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xF0) >> 4) + (((pData[3]) & 0x3F) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m4_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m4_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m4_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m4_data2(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m4_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m4_data2(pData);
}

// SAMPLE_B_m4_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m4_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[3]) & 0xC0) >> 6) + ((pData[4]) << 2);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m4_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m4_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m4_data3(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m4_data3(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m4_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m4_data3(pData);
}

// SAMPLE_B_m4_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m4_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[5]) + (((pData[6]) & 0x03) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m4_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m4_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m4_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m4_data4(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m4_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m4_data4(pData);
}

// SAMPLE_B_m4_data5
static uint16_t GetSRawFromFrame_SAMPLE_B_m4_data5(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[6]) & 0xFC) >> 2) + (((pData[7]) & 0x3F) << 6);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m4_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m4_data5(pData);
}
static float GetSFromFrame_SAMPLE_B_m4_data5(const uint8_t * const pData)
{
    int16_t raw = (int16_t)GetSRawFromFrame_SAMPLE_B_m4_data5(pData);
    // Sign extend
    raw = (raw << 4) >> 4;
    float converted = (((float)raw) * 0.25F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m4_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m4_data5(pData);
}

// SAMPLE_B_m5_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m5_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x3F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m5_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m5_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m5_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m5_data1(pData);
    float converted = (((float)raw) * 2.5e-05F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m5_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m5_data1(pData);
}

// SAMPLE_B_m5_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m5_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[3]) + (((pData[4]) & 0x3F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m5_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m5_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m5_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m5_data2(pData);
    float converted = (((float)raw) * 2.5e-05F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m5_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m5_data2(pData);
}

// SAMPLE_B_m5_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m5_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[5]) + (((pData[6]) & 0x3F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m5_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m5_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m5_data3(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m5_data3(pData);
    float converted = (((float)raw) * 2.5e-05F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m5_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m5_data3(pData);
}

// SAMPLE_B_m5_data4
static uint8_t GetSRawFromFrame_SAMPLE_B_m5_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[6]) & 0xC0) >> 6) + (((pData[7]) & 0x07) << 2);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m5_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m5_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m5_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m5_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m5_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m5_data4(pData);
}

// SAMPLE_B_m5_data5
static uint8_t GetSRawFromFrame_SAMPLE_B_m5_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = (((pData[7]) & 0xF8) >> 3);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m5_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m5_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m5_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m5_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m5_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m5_data5(pData);
}

// SAMPLE_B_m6_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m6_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x0F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m6_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m6_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m6_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m6_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 2U) + -8000U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m6_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m6_data1(pData);
}

// SAMPLE_B_m6_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m6_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xF0) >> 4) + ((pData[3]) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m6_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m6_data2(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m6_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m6_data2(pData);
    uint32_t converted = (((uint32_t)raw) * 2U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m6_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m6_data2(pData);
}

// SAMPLE_B_m6_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m6_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[4]) + (((pData[5]) & 0x03) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m6_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m6_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m6_data3(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m6_data3(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m6_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m6_data3(pData);
}

// SAMPLE_B_m6_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m6_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[5]) & 0xFC) >> 2) + (((pData[6]) & 0x0F) << 6);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m6_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m6_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m6_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m6_data4(pData);
    float converted = (((float)raw) * 0.005F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m6_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m6_data4(pData);
}

// SAMPLE_B_m6_data5
static uint16_t GetSRawFromFrame_SAMPLE_B_m6_data5(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[6]) & 0xF0) >> 4) + ((pData[7]) << 4);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m6_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m6_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m6_data5(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m6_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m6_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m6_data5(pData);
}

// SAMPLE_B_m7_data1
static uint32_t GetSRawFromFrame_SAMPLE_B_m7_data1(const uint8_t * const pData)
{
    const uint32_t rawVal = (pData[1]) + ((pData[2]) << 8) + ((pData[3]) << 16) + ((pData[4]) << 24);
    return rawVal;
}
static uint32_t GetSRaw_SAMPLE_B_m7_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m7_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m7_data1(const uint8_t * const pData)
{
    uint32_t raw = (uint32_t)GetSRawFromFrame_SAMPLE_B_m7_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m7_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m7_data1(pData);
}

// SAMPLE_B_m7_data2
static uint8_t GetSRawFromFrame_SAMPLE_B_m7_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[5]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m7_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m7_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m7_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m7_data2(pData);
    float converted = (((float)raw) * 0.01F) + 0.5F;
    return converted;
}
static float GetS_SAMPLE_B_m7_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m7_data2(pData);
}

// SAMPLE_B_m7_data3
static uint8_t GetSRawFromFrame_SAMPLE_B_m7_data3(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m7_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m7_data3(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m7_data3(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m7_data3(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m7_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m7_data3(pData);
}

// SAMPLE_B_m7_data4
static uint8_t GetSRawFromFrame_SAMPLE_B_m7_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[7]) & 0x0F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m7_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m7_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m7_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m7_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m7_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m7_data4(pData);
}

// SAMPLE_B_m8_data1
static uint16_t GetSRawFromFrame_SAMPLE_B_m8_data1(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[1]) + (((pData[2]) & 0x1F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m8_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m8_data1(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m8_data1(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m8_data1(pData);
    uint32_t converted = (((uint32_t)raw) * 864000U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m8_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m8_data1(pData);
}

// SAMPLE_B_m8_data2
static uint16_t GetSRawFromFrame_SAMPLE_B_m8_data2(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[2]) & 0xE0) >> 5) + (((pData[3]) & 0x3F) << 3);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m8_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m8_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m8_data2(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m8_data2(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m8_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m8_data2(pData);
}

// SAMPLE_B_m8_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m8_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[4]) + (((pData[5]) & 0x3F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m8_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m8_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m8_data3(const uint8_t * const pData)
{
    int16_t raw = (int16_t)GetSRawFromFrame_SAMPLE_B_m8_data3(pData);
    // Sign extend
    raw = (raw << 2) >> 2;
    float converted = (((float)raw) * 0.1F) + 200.0F;
    return converted;
}
static float GetS_SAMPLE_B_m8_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m8_data3(pData);
}

// SAMPLE_B_m8_data4
static uint16_t GetSRawFromFrame_SAMPLE_B_m8_data4(const uint8_t * const pData)
{
    const uint16_t rawVal = (((pData[5]) & 0xC0) >> 6) + ((pData[6]) << 2);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m8_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m8_data4(pData);
}
static float GetSFromFrame_SAMPLE_B_m8_data4(const uint8_t * const pData)
{
    uint16_t raw = (uint16_t)GetSRawFromFrame_SAMPLE_B_m8_data4(pData);
    float converted = (((float)raw) * 0.1F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m8_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m8_data4(pData);
}

// SAMPLE_B_m8_data5
static uint8_t GetSRawFromFrame_SAMPLE_B_m8_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[7]) & 0x07);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m8_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m8_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m8_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m8_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 0U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m8_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m8_data5(pData);
}

// SAMPLE_B_m9_data1
static uint8_t GetSRawFromFrame_SAMPLE_B_m9_data1(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[1]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m9_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m9_data1(pData);
}
static float GetSFromFrame_SAMPLE_B_m9_data1(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m9_data1(pData);
    float converted = (((float)raw) * 0.01F) + 0.5F;
    return converted;
}
static float GetS_SAMPLE_B_m9_data1(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m9_data1(pData);
}

// SAMPLE_B_m9_data2
static uint8_t GetSRawFromFrame_SAMPLE_B_m9_data2(const uint8_t * const pData)
{
    const uint8_t rawVal = (pData[2]);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m9_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m9_data2(pData);
}
static float GetSFromFrame_SAMPLE_B_m9_data2(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m9_data2(pData);
    float converted = (((float)raw) * 0.01F) + 0.5F;
    return converted;
}
static float GetS_SAMPLE_B_m9_data2(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m9_data2(pData);
}

// SAMPLE_B_m9_data3
static uint16_t GetSRawFromFrame_SAMPLE_B_m9_data3(const uint8_t * const pData)
{
    const uint16_t rawVal = (pData[3]) + (((pData[4]) & 0x0F) << 8);
    return rawVal;
}
static uint16_t GetSRaw_SAMPLE_B_m9_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m9_data3(pData);
}
static float GetSFromFrame_SAMPLE_B_m9_data3(const uint8_t * const pData)
{
    int16_t raw = (int16_t)GetSRawFromFrame_SAMPLE_B_m9_data3(pData);
    // Sign extend
    raw = (raw << 4) >> 4;
    float converted = (((float)raw) * 0.25F) + 0.0F;
    return converted;
}
static float GetS_SAMPLE_B_m9_data3(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m9_data3(pData);
}

// SAMPLE_B_m9_data4
static uint8_t GetSRawFromFrame_SAMPLE_B_m9_data4(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[5]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m9_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m9_data4(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m9_data4(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m9_data4(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m9_data4(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m9_data4(pData);
}

// SAMPLE_B_m9_data5
static uint8_t GetSRawFromFrame_SAMPLE_B_m9_data5(const uint8_t * const pData)
{
    const uint8_t rawVal = ((pData[6]) & 0x1F);
    return rawVal;
}
static uint8_t GetSRaw_SAMPLE_B_m9_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSRawFromFrame_SAMPLE_B_m9_data5(pData);
}
static uint32_t GetSFromFrame_SAMPLE_B_m9_data5(const uint8_t * const pData)
{
    uint8_t raw = (uint8_t)GetSRawFromFrame_SAMPLE_B_m9_data5(pData);
    uint32_t converted = (((uint32_t)raw) * 1U) + 1U;
    return converted;
}
static uint32_t GetS_SAMPLE_B_m9_data5(void)
{
    const uint8_t * const pData = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
    return GetSFromFrame_SAMPLE_B_m9_data5(pData);
}

//--------------------------------------------------------------------------------------------------
// Message receive storage functions
//--------------------------------------------------------------------------------------------------
static bool ProcessM_SAMPLE_A_alertLog(const uint8_t * const pData)
{
    bool success = true;
    const uint32_t muxIdx = GetSRawFromFrame_SAMPLE_A_alertID(pData);

    switch (muxIdx)
    {
        case 5U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M5_RX_ARR_IDX][0U];
            break;
        }
        case 6U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M6_RX_ARR_IDX][0U];
            break;
        }
        case 8U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M8_RX_ARR_IDX][0U];
            break;
        }
        case 9U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M9_RX_ARR_IDX][0U];
            break;
        }
        case 20U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M20_RX_ARR_IDX][0U];
            break;
        }
        case 21U:
        {
            gSAMPLE_A_alertLog_LatestRxPtr = &gSAMPLE_A_alertLog_RX_ARR[SAMPLE_A_alertLog_M21_RX_ARR_IDX][0U];
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
        for (uint32_t d = 0U; d < SAMPLE_A_alertLog_DLC; ++d)
        {
            gSAMPLE_A_alertLog_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

static bool ProcessM_SAMPLE_A_alertMatrix(const uint8_t * const pData)
{
    bool success = true;

    gSAMPLE_A_alertMatrix_LatestRxPtr = &gSAMPLE_A_alertMatrix_RX_ARR[0U][0U];

    if (success)
    {
        for (uint32_t d = 0U; d < SAMPLE_A_alertMatrix_DLC; ++d)
        {
            gSAMPLE_A_alertMatrix_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

static bool ProcessM_SAMPLE_B_debug(const uint8_t * const pData)
{
    bool success = true;
    const uint32_t muxIdx = GetSRawFromFrame_SAMPLE_B_debugMultiplexer(pData);

    switch (muxIdx)
    {
        case 0U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M0_RX_ARR_IDX][0U];
            break;
        }
        case 1U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M1_RX_ARR_IDX][0U];
            break;
        }
        case 2U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M2_RX_ARR_IDX][0U];
            break;
        }
        case 3U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M3_RX_ARR_IDX][0U];
            break;
        }
        case 4U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M4_RX_ARR_IDX][0U];
            break;
        }
        case 5U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M5_RX_ARR_IDX][0U];
            break;
        }
        case 6U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M6_RX_ARR_IDX][0U];
            break;
        }
        case 7U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M7_RX_ARR_IDX][0U];
            break;
        }
        case 8U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M8_RX_ARR_IDX][0U];
            break;
        }
        case 9U:
        {
            gSAMPLE_B_debug_LatestRxPtr = &gSAMPLE_B_debug_RX_ARR[SAMPLE_B_debug_M9_RX_ARR_IDX][0U];
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
        for (uint32_t d = 0U; d < SAMPLE_B_debug_DLC; ++d)
        {
            gSAMPLE_B_debug_LatestRxPtr[d] = pData[d];
        }
    }

    return success;
}

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
bool CanReceive(const uint8_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    bool success = true;

    switch (mid)
    {
        case SAMPLE_A_alertLog_MID:
        {
            if (dlc != SAMPLE_A_alertLog_DLC)
            {
                success = false;
            }
            else
            {
                success = ProcessM_SAMPLE_A_alertLog(pData);
            }
            break;
        }
        case SAMPLE_A_alertMatrix_MID:
        {
            if (dlc != SAMPLE_A_alertMatrix_DLC)
            {
                success = false;
            }
            else
            {
                success = ProcessM_SAMPLE_A_alertMatrix(pData);
            }
            break;
        }
        case SAMPLE_B_debug_MID:
        {
            if (dlc != SAMPLE_B_debug_DLC)
            {
                success = false;
            }
            else
            {
                success = ProcessM_SAMPLE_B_debug(pData);
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
