#include "EIM_canTransmitter.hpp"
#include "EIM_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Transmit message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gEIM_PcbaVitals_TX_ARR[CANTX_EIM_EIM_PcbaVitals_ARR_LEN][CAN_EIM_EIM_PcbaVitals_DLC];
static uint8_t gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_ARR_LEN][CAN_EIM_EIM_CpuStats_DLC];
static uint8_t gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_ARR_LEN][CAN_EIM_EIM_ServoStatus_DLC];
static uint8_t gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_ARR_LEN][CAN_EIM_EIM_EngineStatus_DLC];

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_EIM_GetTxStorage_EIM_PcbaVitals(const uint32_t muxIdx)
{
    (void)muxIdx;
    return &gEIM_PcbaVitals_TX_ARR[0U][0U];
}

uint8_t * CANTX_EIM_GetTxStorage_EIM_CpuStats(const uint32_t muxIdx)
{
    return &gEIM_CpuStats_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_EIM_GetTxStorage_EIM_ServoStatus(const uint32_t muxIdx)
{
    return &gEIM_ServoStatus_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_EIM_GetTxStorage_EIM_EngineStatus(const uint32_t muxIdx)
{
    return &gEIM_EngineStatus_TX_ARR[muxIdx][0U];
}

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gEIM_CpuStats_MuxFromIdx[] = {
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
};
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_CpuStats(const uint32_t muxIdx)
{
    return gEIM_CpuStats_MuxFromIdx[muxIdx];
}
uint32_t gEIM_ServoStatus_MuxFromIdx[] = {
    0U,
    1U,
};
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_ServoStatus(const uint32_t muxIdx)
{
    return gEIM_ServoStatus_MuxFromIdx[muxIdx];
}
uint32_t gEIM_EngineStatus_MuxFromIdx[] = {
    0U,
    1U,
};
uint32_t CANTX_EIM_GetMuxFromIdx_EIM_EngineStatus(const uint32_t muxIdx)
{
    return gEIM_EngineStatus_MuxFromIdx[muxIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// EIM_PCBA_DieTemp
void CANTX_EIM_SetSRawFromFrame_EIM_PCBA_DieTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_PCBA_DieTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[0U][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_PCBA_DieTemp(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_PCBA_DieTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 205 ? 205 : (converted < -50 ? -50 : converted));
        rawVal = (uint8_t)((convertedSat - -50) / 1);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_PCBA_DieTemp((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_PCBA_DieTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[0U][0U];
    CANTX_EIM_SetSFromFrame_EIM_PCBA_DieTemp(converted, pData);
}

// EIM_100Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_100Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MinPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_100Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_100Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_100Hz_MinPeriod(converted, pData);
}

// EIM_100Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_100Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MaxPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_100Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_100Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_100Hz_MaxPeriod(converted, pData);
}

// EIM_100Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0xF0);
    pData[3] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[4] &= (uint8_t)(~0x3F);
    pData[4] |= (uint8_t)((((rawVal) >> 4) & 0x3F));
}
void CANTX_EIM_SetSRaw_EIM_100Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_Load(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_100Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_100Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_100Hz_Load(converted, pData);
}

// EIM_100Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_100Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_100Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_AvgPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_100Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_100Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_100Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_100Hz_AvgPeriod(converted, pData);
}

// EIM_ADC_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_ADC_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_MinPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ADC_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ADC_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ADC_MinPeriod(converted, pData);
}

// EIM_ADC_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ADC_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_MaxPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ADC_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ADC_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ADC_MaxPeriod(converted, pData);
}

// EIM_ADC_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_ADC_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ADC_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_AvgPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ADC_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ADC_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ADC_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ADC_AvgPeriod(converted, pData);
}

// EIM_CPU_Load
void CANTX_EIM_SetSRawFromFrame_EIM_CPU_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] &= (uint8_t)(~0x03);
    pData[2] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_EIM_SetSRaw_EIM_CPU_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_CPU_Load(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_CPU_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_CPU_Load((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_CPU_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_CPU_Load(converted, pData);
}

// EIM_1Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
    pData[7] &= (uint8_t)(~0x03);
    pData[7] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_EIM_SetSRaw_EIM_1Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_Load(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1Hz_Load(converted, pData);
}

// EIM_10Hz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0xC0);
    pData[4] |= (uint8_t)((((rawVal) << 6) & 0xC0));
    pData[5] = (uint8_t)((((rawVal) >> 2) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_10Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_Load(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_10Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_10Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_10Hz_Load(converted, pData);
}

// EIM_1kHz_Load
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0xFC);
    pData[2] |= (uint8_t)((((rawVal) << 2) & 0xFC));
    pData[3] &= (uint8_t)(~0x0F);
    pData[3] |= (uint8_t)((((rawVal) >> 6) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_1kHz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_Load(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1kHz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_Load((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1kHz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1kHz_Load(converted, pData);
}

// EIM_1Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_1Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MaxPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1Hz_MaxPeriod(converted, pData);
}

// EIM_1Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_1Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MinPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1Hz_MinPeriod(converted, pData);
}

// EIM_1Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_1Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_AvgPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1Hz_AvgPeriod(converted, pData);
}

// EIM_10Hz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_10Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MaxPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_10Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_10Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_10Hz_MaxPeriod(converted, pData);
}

// EIM_10Hz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_10Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MinPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_10Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_10Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_10Hz_MinPeriod(converted, pData);
}

// EIM_10Hz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_10Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_10Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_AvgPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_10Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_10Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_10Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_10Hz_AvgPeriod(converted, pData);
}

// EIM_1kHz_MaxPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_1kHz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MaxPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1kHz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1kHz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1kHz_MaxPeriod(converted, pData);
}

// EIM_1kHz_MinPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_EIM_SetSRaw_EIM_1kHz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MinPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1kHz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1kHz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1kHz_MinPeriod(converted, pData);
}

// EIM_1kHz_AvgPeriod
void CANTX_EIM_SetSRawFromFrame_EIM_1kHz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_1kHz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_AvgPeriod(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_1kHz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_1kHz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_1kHz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_1kHz_AvgPeriod(converted, pData);
}

// EIM_CpuStatsMux
void CANTX_EIM_SetSRawFromFrame_EIM_CpuStatsMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_CpuStatsMux((uint8_t)rawVal, pData);
}

// EIM_ServoStatusMux
void CANTX_EIM_SetSRawFromFrame_EIM_ServoStatusMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_EIM_SetSFromFrame_EIM_ServoStatusMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ServoStatusMux((uint8_t)rawVal, pData);
}

// EIM_Servo_Voltage
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Voltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_Servo_Voltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Voltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_Voltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 51.0F ? 51.0F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.2F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Voltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Voltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_Voltage(converted, pData);
}

// EIM_Servo_Temp
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Temp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_Servo_Temp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Temp(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_Temp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 205 ? 205 : (converted < -50 ? -50 : converted));
        rawVal = (uint8_t)((convertedSat - -50) / 1);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Temp((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Temp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_Temp(converted, pData);
}

// EIM_Servo_Position
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Position(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] &= (uint8_t)(~0x3F);
    pData[3] |= (uint8_t)((((rawVal) >> 8) & 0x3F));
}
void CANTX_EIM_SetSRaw_EIM_Servo_Position(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Position(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_Position(const float_q converted, uint8_t * const pData)
{
    int16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 8192; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.8F ? -204.8F : converted));
        rawVal = (int16_t)((convertedSat - 0.0F) / 0.025F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Position((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Position(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_Position(converted, pData);
}

// EIM_Servo_LossOfCommTimeout
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommTimeout(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 255U ? 255U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_LossOfCommTimeout(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommTimeout(converted, pData);
}

// EIM_Servo_LossOfCommPosition
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
    pData[5] &= (uint8_t)(~0x3F);
    pData[5] |= (uint8_t)((((rawVal) >> 8) & 0x3F));
}
void CANTX_EIM_SetSRaw_EIM_Servo_LossOfCommPosition(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommPosition(const float_q converted, uint8_t * const pData)
{
    int16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 8192; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.8F ? -204.8F : converted));
        rawVal = (int16_t)((convertedSat - 0.0F) / 0.025F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommPosition((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_LossOfCommPosition(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommPosition(converted, pData);
}

// EIM_Servo_Id
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Id(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_Servo_Id(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Id(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_Id(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 255U ? 255U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Id((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Id(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_Id(converted, pData);
}

// EIM_Servo_Current
void CANTX_EIM_SetSRawFromFrame_EIM_Servo_Current(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_Servo_Current(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Current(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_Servo_Current(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Current((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Current(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_Servo_Current(converted, pData);
}

// EIM_EngineStatusMux
void CANTX_EIM_SetSRawFromFrame_EIM_EngineStatusMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_EIM_SetSFromFrame_EIM_EngineStatusMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_EngineStatusMux((uint8_t)rawVal, pData);
}

// EIM_ECM_VehicleSpeed
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_VehicleSpeed(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_VehicleSpeed(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_VehicleSpeed(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_VehicleSpeed(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 255U ? 255U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_VehicleSpeed((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_VehicleSpeed(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_VehicleSpeed(converted, pData);
}

// EIM_ECM_TpsVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_TpsVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsVoltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsVoltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_TpsVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_TpsVoltage(converted, pData);
}

// EIM_ECM_TpsAngle
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsAngle(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_TpsAngle(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsAngle(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsAngle(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 127.5F ? 127.5F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsAngle((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_TpsAngle(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_TpsAngle(converted, pData);
}

// EIM_ECM_Rpm
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_Rpm(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_Rpm(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_Rpm(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_Rpm(const uint32_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 65535U ? 65535U : converted);
        rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_Rpm((uint16_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_Rpm(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_Rpm(converted, pData);
}

// EIM_ECM_MapVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_MapVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapVoltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapVoltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_MapVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_MapVoltage(converted, pData);
}

// EIM_ECM_MapPressure
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapPressure(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_MapPressure(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapPressure(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapPressure(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 255U ? 255U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapPressure((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_MapPressure(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_MapPressure(converted, pData);
}

// EIM_ECM_IatVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_IatVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatVoltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatVoltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_IatVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_IatVoltage(converted, pData);
}

// EIM_ECM_IatTemp
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_IatTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatTemp(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 215 ? 215 : (converted < -40 ? -40 : converted));
        rawVal = (uint8_t)((convertedSat - -40) / 1);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatTemp((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_IatTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_IatTemp(converted, pData);
}

// EIM_ECM_EctVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_EctVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctVoltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctVoltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_EctVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_EctVoltage(converted, pData);
}

// EIM_ECM_EctTemp
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_EctTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctTemp(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 215 ? 215 : (converted < -40 ? -40 : converted));
        rawVal = (uint8_t)((convertedSat - -40) / 1);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctTemp((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_EctTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_EctTemp(converted, pData);
}

// EIM_ECM_BatteryVoltage
void CANTX_EIM_SetSRawFromFrame_EIM_ECM_BatteryVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_EIM_SetSRaw_EIM_ECM_BatteryVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_BatteryVoltage(rawVal, pData);
}
void CANTX_EIM_SetSFromFrame_EIM_ECM_BatteryVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_BatteryVoltage((uint8_t)rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_BatteryVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_BatteryVoltage(converted, pData);
}

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_EIM_Init(void)
{

    // EIM_CpuStats
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        0U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M0_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        1U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M1_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        2U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M2_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        3U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M3_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        4U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M4_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_CpuStatsMux(
        5U,
        &gEIM_CpuStats_TX_ARR[CANTX_EIM_EIM_CpuStats_M5_ARR_IDX][0U]
    );

    // EIM_ServoStatus
    CANTX_EIM_SetSFromFrame_EIM_ServoStatusMux(
        0U,
        &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_ServoStatusMux(
        1U,
        &gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX][0U]
    );

    // EIM_EngineStatus
    CANTX_EIM_SetSFromFrame_EIM_EngineStatusMux(
        0U,
        &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U]
    );
    CANTX_EIM_SetSFromFrame_EIM_EngineStatusMux(
        1U,
        &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX][0U]
    );

    return true;
}

} // namespace CanGen
