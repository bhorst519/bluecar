#include "ben_test_canTransmitter.h"
#include "ben_test_messageInfo.h"
#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Transmit message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_ARR_LEN][CAN_ben_test_SAMPLE_B_alertLog_DLC];
static uint8_t gSAMPLE_B_alertMatrix_TX_ARR[CANTX_ben_test_SAMPLE_B_alertMatrix_ARR_LEN][CAN_ben_test_SAMPLE_B_alertMatrix_DLC];

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_ben_test_GetTxStorage_SAMPLE_B_alertLog(const uint32_t muxIdx)
{
    return &gSAMPLE_B_alertLog_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_ben_test_GetTxStorage_SAMPLE_B_alertMatrix(const uint32_t muxIdx)
{
    (void)muxIdx;
    return &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
}

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gSAMPLE_B_alertLog_MuxFromIdx[] = {
    5U,
    6U,
    8U,
    9U,
    20U,
    21U,
    47U,
};
uint32_t CANTX_ben_test_GetMuxFromIdx_SAMPLE_B_alertLog(const uint32_t muxIdx)
{
    return gSAMPLE_B_alertLog_MuxFromIdx[muxIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// SAMPLE_B_alertID
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertID(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x7F);
    pData[0] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 76U ? 76U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertID(rawVal, pData);
}

// SAMPLE_B_alertState
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertState(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x80);
    pData[1] |= (uint8_t)((((rawVal) << 7) & 0x80));
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertState(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertState(rawVal, pData);
}

// SAMPLE_B_a005_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data1(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0x01);
    pData[2] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_data1(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a005_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data1(converted, pData);
}

// SAMPLE_B_a005_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0x02);
    pData[2] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_data2(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data2(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a005_data2(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data2(converted, pData);
}

// SAMPLE_B_a006_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data1(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_data1(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 65535U ? 65535U : (converted < 0U ? 0U : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a006_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data1(converted, pData);
}

// SAMPLE_B_a006_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data2(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
    pData[5] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_data2(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data2(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 65535U ? 65535U : (converted < 0U ? 0U : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a006_data2(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data2(converted, pData);
}

// SAMPLE_B_a008_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data1(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data1(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 65535U ? 65535U : (converted < 0U ? 0U : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data1(converted, pData);
}

// SAMPLE_B_a008_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data2(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data2(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_data2(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data2(converted, pData);
}

// SAMPLE_B_a008_data3
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data3(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data3(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data3(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data3(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data3(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_data3(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data3(converted, pData);
}

// SAMPLE_B_a008_data4
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0x01);
    pData[6] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data4(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data4(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data4(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data4(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_data4(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data4(converted, pData);
}

// SAMPLE_B_a008_data5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0x02);
    pData[6] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data5(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_data5(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data5(converted, pData);
}

// SAMPLE_B_a009_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data1(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data1(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 65535U ? 65535U : (converted < 0U ? 0U : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data1(converted, pData);
}

// SAMPLE_B_a009_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data2(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data2(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_data2(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data2(converted, pData);
}

// SAMPLE_B_a009_data3
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data3(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data3(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data3(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data3(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data3(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_data3(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data3(converted, pData);
}

// SAMPLE_B_a009_data4
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0x01);
    pData[6] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data4(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data4(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data4(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data4(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_data4(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data4(converted, pData);
}

// SAMPLE_B_a009_data5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0x02);
    pData[6] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data5(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_data5(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data5(converted, pData);
}

// SAMPLE_B_a020_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data1(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0x7F);
    pData[2] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data1(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 128U ? 128U : (converted < 1U ? 1U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 1U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data1(converted, pData);
}

// SAMPLE_B_a020_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data2(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data2(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 100.0F ? 100.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_data2(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data2(converted, pData);
}

// SAMPLE_B_a020_data3
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data3(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0x7F);
    pData[4] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data3(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data3(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data3(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 128U ? 128U : (converted < 1U ? 1U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 1U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data3(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_data3(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data3(converted, pData);
}

// SAMPLE_B_a020_data4
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data4(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data4(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data4(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 100.0F ? 100.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data4(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_data4(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data4(converted, pData);
}

// SAMPLE_B_a020_data5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data5(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 100.0F ? 100.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_data5(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data5(converted, pData);
}

// SAMPLE_B_a021_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data1(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0x7F);
    pData[2] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data1(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data1(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 128U ? 128U : (converted < 1U ? 1U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 1U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data1(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data1(converted, pData);
}

// SAMPLE_B_a021_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data2(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data2(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 100.0F ? 100.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data2(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data2(converted, pData);
}

// SAMPLE_B_a021_data3
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data3(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0x7F);
    pData[4] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data3(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data3(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data3(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 128U ? 128U : (converted < 1U ? 1U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 1U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data3(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data3(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data3(converted, pData);
}

// SAMPLE_B_a021_data4
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data4(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data4(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data4(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 100.0F ? 100.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data4(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data4(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data4(converted, pData);
}

// SAMPLE_B_a021_data5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0x7F);
    pData[6] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data5(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 100U ? 100U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data5(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data5(converted, pData);
}

// SAMPLE_B_a021_data6
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data6(const uint8_t rawVal, uint8_t * const pData)
{
    pData[7] &= (uint8_t)(~0x7F);
    pData[7] |= (uint8_t)(((rawVal) & 0x7F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data6(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data6(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data6(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 100U ? 100U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data6(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_data6(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data6(converted, pData);
}

// SAMPLE_B_a047_data1
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data1(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] &= (uint8_t)(~0x03);
    pData[3] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data1(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data1(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data1(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.115F ? 5.115F : (converted < 0.0F ? 0.0F : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data1(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a047_data1(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data1(converted, pData);
}

// SAMPLE_B_a047_data2
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data2(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0xFC);
    pData[3] |= (uint8_t)((((rawVal) << 2) & 0xFC));
    pData[4] &= (uint8_t)(~0x0F);
    pData[4] |= (uint8_t)((((rawVal) >> 6) & 0x0F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data2(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data2(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data2(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.115F ? 5.115F : (converted < 0.0F ? 0.0F : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data2(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a047_data2(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data2(converted, pData);
}

// SAMPLE_B_a047_data3
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data3(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0xF0);
    pData[4] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[5] &= (uint8_t)(~0x3F);
    pData[5] |= (uint8_t)((((rawVal) >> 4) & 0x3F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data3(const uint16_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data3(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data3(const int32_t converted, uint8_t * const pData)
{
    const int32_t convertedSat = (converted > 2555 ? 2555 : (converted < -2560 ? -2560 : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0) / 5);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data3(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a047_data3(const int32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data3(converted, pData);
}

// SAMPLE_B_a047_data4
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xC0);
    pData[5] |= (uint8_t)((((rawVal) << 6) & 0xC0));
    pData[6] &= (uint8_t)(~0x3F);
    pData[6] |= (uint8_t)((((rawVal) >> 2) & 0x3F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data4(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data4(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data4(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 127.5F ? 127.5F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data4(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a047_data4(const float converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data4(converted, pData);
}

// SAMPLE_B_a047_data5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0xC0);
    pData[6] |= (uint8_t)((((rawVal) << 6) & 0xC0));
    pData[7] &= (uint8_t)(~0x3F);
    pData[7] |= (uint8_t)((((rawVal) >> 2) & 0x3F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data5(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 256U ? 256U : (converted < 1U ? 1U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 1U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a047_data5(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data5(converted, pData);
}

// SAMPLE_B_matrixIndex
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_matrixIndex(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_matrixIndex(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_matrixIndex(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_matrixIndex(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 15U ? 15U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_matrixIndex(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_matrixIndex(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_matrixIndex(converted, pData);
}

// SAMPLE_B_a005_alert5
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_alert5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x10);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0x10));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_alert5(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_alert5(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_alert5(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_alert5(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a005_alert5(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_alert5(converted, pData);
}

// SAMPLE_B_a006_alert6
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_alert6(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x20);
    pData[0] |= (uint8_t)((((rawVal) << 5) & 0x20));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_alert6(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_alert6(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_alert6(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_alert6(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a006_alert6(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_alert6(converted, pData);
}

// SAMPLE_B_a007_alert7
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a007_alert7(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x40);
    pData[0] |= (uint8_t)((((rawVal) << 6) & 0x40));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a007_alert7(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a007_alert7(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a007_alert7(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a007_alert7(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a007_alert7(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a007_alert7(converted, pData);
}

// SAMPLE_B_a008_alert8
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_alert8(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x80);
    pData[0] |= (uint8_t)((((rawVal) << 7) & 0x80));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_alert8(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_alert8(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_alert8(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_alert8(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a008_alert8(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_alert8(converted, pData);
}

// SAMPLE_B_a009_alert9
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_alert9(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x01);
    pData[1] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_alert9(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_alert9(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_alert9(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_alert9(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a009_alert9(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_alert9(converted, pData);
}

// SAMPLE_B_a020_alert20
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_alert20(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x02);
    pData[1] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_alert20(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_alert20(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_alert20(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_alert20(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a020_alert20(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_alert20(converted, pData);
}

// SAMPLE_B_a021_alert21
void  CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_alert21(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x04);
    pData[1] |= (uint8_t)((((rawVal) << 2) & 0x04));
}
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_alert21(const uint8_t rawVal)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_alert21(rawVal, pData);
}
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_alert21(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 1U ? 1U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_alert21(rawVal, pData);
}
void CANTX_ben_test_SetS_SAMPLE_B_a021_alert21(const uint32_t converted)
{
    uint8_t * const pData = &gSAMPLE_B_alertMatrix_TX_ARR[0U][0U];
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_alert21(converted, pData);
}

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_ben_test_Init(void)
{
    // SAMPLE_B_alertLog
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(5U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(6U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(8U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(9U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(20U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(21U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX][0U]);
    CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(47U, &gSAMPLE_B_alertLog_TX_ARR[CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX][0U]);

    return true;
}
