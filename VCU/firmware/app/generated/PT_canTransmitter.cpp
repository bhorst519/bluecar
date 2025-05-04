#include "PT_canTransmitter.hpp"
#include "PT_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Transmit message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_ARR_LEN][CAN_PT_VCU_CpuStats_DLC];
static uint8_t gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_ARR_LEN][CAN_PT_VCU_PcbaVitals_DLC];

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_PT_GetTxStorage_VCU_CpuStats(const uint32_t muxIdx)
{
    return &gVCU_CpuStats_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_PT_GetTxStorage_VCU_PcbaVitals(const uint32_t muxIdx)
{
    return &gVCU_PcbaVitals_TX_ARR[muxIdx][0U];
}

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gVCU_CpuStats_MuxFromIdx[] = {
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
};
uint32_t CANTX_PT_GetMuxFromIdx_VCU_CpuStats(const uint32_t muxIdx)
{
    return gVCU_CpuStats_MuxFromIdx[muxIdx];
}
uint32_t gVCU_PcbaVitals_MuxFromIdx[] = {
    0U,
    1U,
};
uint32_t CANTX_PT_GetMuxFromIdx_VCU_PcbaVitals(const uint32_t muxIdx)
{
    return gVCU_PcbaVitals_MuxFromIdx[muxIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// VCU_100Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_VCU_100Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_100Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_100Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_100Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_100Hz_AvgPeriod(converted, pData);
}

// VCU_100Hz_Load
void CANTX_PT_SetSRawFromFrame_VCU_100Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0xF0);
    pData[3] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[4] &= (uint8_t)(~0x3F);
    pData[4] |= (uint8_t)((((rawVal) >> 4) & 0x3F));
}
void CANTX_PT_SetSRaw_VCU_100Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_100Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_100Hz_Load(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_100Hz_Load(converted, pData);
}

// VCU_100Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_VCU_100Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_100Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_100Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_100Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_100Hz_MaxPeriod(converted, pData);
}

// VCU_100Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_VCU_100Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_100Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_100Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_100Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_100Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_100Hz_MinPeriod(converted, pData);
}

// VCU_10Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_VCU_10Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_10Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_10Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_10Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_10Hz_AvgPeriod(converted, pData);
}

// VCU_10Hz_Load
void CANTX_PT_SetSRawFromFrame_VCU_10Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0xC0);
    pData[4] |= (uint8_t)((((rawVal) << 6) & 0xC0));
    pData[5] = (uint8_t)((((rawVal) >> 2) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_10Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_10Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_10Hz_Load(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_10Hz_Load(converted, pData);
}

// VCU_10Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_VCU_10Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_10Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_10Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_10Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_10Hz_MaxPeriod(converted, pData);
}

// VCU_10Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_VCU_10Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_10Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_10Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_10Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_10Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_10Hz_MinPeriod(converted, pData);
}

// VCU_1Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_1Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1Hz_AvgPeriod(converted, pData);
}

// VCU_1Hz_Load
void CANTX_PT_SetSRawFromFrame_VCU_1Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
    pData[7] &= (uint8_t)(~0x03);
    pData[7] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_VCU_1Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1Hz_Load(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1Hz_Load(converted, pData);
}

// VCU_1Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_1Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1Hz_MaxPeriod(converted, pData);
}

// VCU_1Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_1Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1Hz_MinPeriod(converted, pData);
}

// VCU_1kHz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1kHz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_1kHz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1kHz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1kHz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1kHz_AvgPeriod(converted, pData);
}

// VCU_1kHz_Load
void CANTX_PT_SetSRawFromFrame_VCU_1kHz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0xFC);
    pData[2] |= (uint8_t)((((rawVal) << 2) & 0xFC));
    pData[3] &= (uint8_t)(~0x0F);
    pData[3] |= (uint8_t)((((rawVal) >> 6) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_1kHz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1kHz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1kHz_Load(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1kHz_Load(converted, pData);
}

// VCU_1kHz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1kHz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_1kHz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1kHz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1kHz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1kHz_MaxPeriod(converted, pData);
}

// VCU_1kHz_MinPeriod
void CANTX_PT_SetSRawFromFrame_VCU_1kHz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_1kHz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_1kHz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_1kHz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_1kHz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_1kHz_MinPeriod(converted, pData);
}

// VCU_ADC_AvgPeriod
void CANTX_PT_SetSRawFromFrame_VCU_ADC_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_ADC_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_ADC_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_ADC_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_ADC_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_ADC_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_ADC_AvgPeriod(converted, pData);
}

// VCU_ADC_MaxPeriod
void CANTX_PT_SetSRawFromFrame_VCU_ADC_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_ADC_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_ADC_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_ADC_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_ADC_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_ADC_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_ADC_MaxPeriod(converted, pData);
}

// VCU_ADC_MinPeriod
void CANTX_PT_SetSRawFromFrame_VCU_ADC_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_ADC_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_ADC_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_ADC_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_ADC_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_ADC_MinPeriod(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_ADC_MinPeriod(converted, pData);
}

// VCU_CPU_Load
void CANTX_PT_SetSRawFromFrame_VCU_CPU_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] &= (uint8_t)(~0x03);
    pData[2] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_VCU_CPU_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_CPU_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_CPU_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_CPU_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_CPU_Load(const float converted)
{
    uint8_t * const pData = &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_CPU_Load(converted, pData);
}

// VCU_CpuStatsMux
void CANTX_PT_SetSRawFromFrame_VCU_CpuStatsMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_CpuStatsMux((uint8_t)rawVal, pData);
}

// VCU_PCBA_Aps1Pct
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1Pct(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] &= (uint8_t)(~0x03);
    pData[2] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_VCU_PCBA_Aps1Pct(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1Pct(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_Aps1Pct(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 1023U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 102.2F ? 102.2F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1Pct((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_Aps1Pct(const float_q converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_Aps1Pct(converted, pData);
}

// VCU_PCBA_Aps1V
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1V(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] &= (uint8_t)(~0x0F);
    pData[4] |= (uint8_t)((((rawVal) >> 8) & 0x0F));
}
void CANTX_PT_SetSRaw_VCU_PCBA_Aps1V(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1V(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_Aps1V(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 4095U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 4.094F ? 4.094F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps1V((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_Aps1V(const float_q converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_Aps1V(converted, pData);
}

// VCU_PCBA_Aps2Pct
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2Pct(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] &= (uint8_t)(~0x03);
    pData[4] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_VCU_PCBA_Aps2Pct(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2Pct(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_Aps2Pct(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 1023U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 102.2F ? 102.2F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2Pct((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_Aps2Pct(const float_q converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_Aps2Pct(converted, pData);
}

// VCU_PCBA_Aps2V
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2V(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0xF0);
    pData[4] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[5] = (uint8_t)((((rawVal) >> 4) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_PCBA_Aps2V(const uint16_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2V(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_Aps2V(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 4095U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 4.094F ? 4.094F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_Aps2V((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_Aps2V(const float_q converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_Aps2V(converted, pData);
}

// VCU_PCBA_BrakeSwitch
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_BrakeSwitch(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x04);
    pData[1] |= (uint8_t)((((rawVal) << 2) & 0x04));
}
void CANTX_PT_SetSRaw_VCU_PCBA_BrakeSwitch(const uint8_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_BrakeSwitch(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_BrakeSwitch(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_BrakeSwitch((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_BrakeSwitch(const uint32_t converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_BrakeSwitch(converted, pData);
}

// VCU_PCBA_DieTemp
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_DieTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_VCU_PCBA_DieTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_DieTemp(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_DieTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 204 ? 204 : (converted < -50 ? -50 : converted));
        rawVal = (uint8_t)((convertedSat - -50) / 1);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_DieTemp((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_DieTemp(const int32_q converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_DieTemp(converted, pData);
}

// VCU_PCBA_EngEnable
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngEnable(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x01);
    pData[1] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_PT_SetSRaw_VCU_PCBA_EngEnable(const uint8_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngEnable(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_EngEnable(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngEnable((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_EngEnable(const uint32_t converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_EngEnable(converted, pData);
}

// VCU_PCBA_EngStart
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngStart(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x02);
    pData[1] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_PT_SetSRaw_VCU_PCBA_EngStart(const uint8_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngStart(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_EngStart(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_EngStart((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_EngStart(const uint32_t converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_EngStart(converted, pData);
}

// VCU_PCBA_UserSwitch
void CANTX_PT_SetSRawFromFrame_VCU_PCBA_UserSwitch(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x08);
    pData[1] |= (uint8_t)((((rawVal) << 3) & 0x08));
}
void CANTX_PT_SetSRaw_VCU_PCBA_UserSwitch(const uint8_t rawVal)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_UserSwitch(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_VCU_PCBA_UserSwitch(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PCBA_UserSwitch((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_VCU_PCBA_UserSwitch(const uint32_t converted)
{
    uint8_t * const pData = &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_VCU_PCBA_UserSwitch(converted, pData);
}

// VCU_PcbaVitalsMux
void CANTX_PT_SetSRawFromFrame_VCU_PcbaVitalsMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_VCU_PcbaVitalsMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_VCU_PcbaVitalsMux((uint8_t)rawVal, pData);
}

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_PT_Init(void)
{
    // VCU_CpuStats
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        0U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        1U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M1_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        2U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M2_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        3U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M3_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        4U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M4_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_CpuStatsMux(
        5U,
        &gVCU_CpuStats_TX_ARR[CANTX_PT_VCU_CpuStats_M5_ARR_IDX][0U]
    );

    // VCU_PcbaVitals
    CANTX_PT_SetSFromFrame_VCU_PcbaVitalsMux(
        0U,
        &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_VCU_PcbaVitalsMux(
        1U,
        &gVCU_PcbaVitals_TX_ARR[CANTX_PT_VCU_PcbaVitals_M1_ARR_IDX][0U]
    );

    // Signals SNA on init
    CANTX_PT_SetS_VCU_PCBA_Aps1Pct(float_q{});
    CANTX_PT_SetS_VCU_PCBA_Aps1V(float_q{});
    CANTX_PT_SetS_VCU_PCBA_Aps2Pct(float_q{});
    CANTX_PT_SetS_VCU_PCBA_Aps2V(float_q{});
    CANTX_PT_SetS_VCU_PCBA_DieTemp(int32_q{});

    return true;
}

} // namespace CanGen
