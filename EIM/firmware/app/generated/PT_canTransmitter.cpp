#include "PT_canTransmitter.hpp"
#include "PT_messageInfo.hpp"
#include "canUtil.hpp"
#include "stdbool.h"
#include "stdint.h"

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Transmit message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_ARR_LEN][CAN_PT_EIM_CpuStats_DLC];
static uint8_t gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_ARR_LEN][CAN_PT_EIM_EngineStatus_DLC];
static uint8_t gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_ARR_LEN][CAN_PT_EIM_PcbaVitals_DLC];
static uint8_t gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_ARR_LEN][CAN_PT_EIM_ServoStatus_DLC];

//--------------------------------------------------------------------------------------------------
// Transmit message cycle time storage
//--------------------------------------------------------------------------------------------------
using MuxTransmitter_S = CanUtil::MuxTransmitter_S;

static MuxTransmitter_S gEIM_CpuStats_muxTransmitter = {
    .m_periodMs = CANTX_PT_EIM_CpuStats_CYCLE_TIME,
    .m_numMuxes = (CAN_PT_EIM_CpuStats_MAX_MUX_IDX + 1U),
    .m_counter = 0U,
};

static MuxTransmitter_S gEIM_EngineStatus_muxTransmitter = {
    .m_periodMs = CANTX_PT_EIM_EngineStatus_CYCLE_TIME,
    .m_numMuxes = (CAN_PT_EIM_EngineStatus_MAX_MUX_IDX + 1U),
    .m_counter = 0U,
};

static MuxTransmitter_S gEIM_PcbaVitals_muxTransmitter = {
    .m_periodMs = CANTX_PT_EIM_PcbaVitals_CYCLE_TIME,
    .m_numMuxes = (CAN_PT_EIM_PcbaVitals_MAX_MUX_IDX + 1U),
    .m_counter = 0U,
};

static MuxTransmitter_S gEIM_ServoStatus_muxTransmitter = {
    .m_periodMs = CANTX_PT_EIM_ServoStatus_CYCLE_TIME,
    .m_numMuxes = (CAN_PT_EIM_ServoStatus_MAX_MUX_IDX + 1U),
    .m_counter = 0U,
};

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_PT_GetTxStorage_EIM_CpuStats(const uint32_t muxIdx)
{
    return &gEIM_CpuStats_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_PT_GetTxStorage_EIM_EngineStatus(const uint32_t muxIdx)
{
    return &gEIM_EngineStatus_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_PT_GetTxStorage_EIM_PcbaVitals(const uint32_t muxIdx)
{
    return &gEIM_PcbaVitals_TX_ARR[muxIdx][0U];
}

uint8_t * CANTX_PT_GetTxStorage_EIM_ServoStatus(const uint32_t muxIdx)
{
    return &gEIM_ServoStatus_TX_ARR[muxIdx][0U];
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
uint32_t CANTX_PT_GetMuxFromIdx_EIM_CpuStats(const uint32_t muxIdx)
{
    return gEIM_CpuStats_MuxFromIdx[muxIdx];
}
uint32_t gEIM_EngineStatus_MuxFromIdx[] = {
    0U,
    1U,
};
uint32_t CANTX_PT_GetMuxFromIdx_EIM_EngineStatus(const uint32_t muxIdx)
{
    return gEIM_EngineStatus_MuxFromIdx[muxIdx];
}
uint32_t gEIM_PcbaVitals_MuxFromIdx[] = {
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
};
uint32_t CANTX_PT_GetMuxFromIdx_EIM_PcbaVitals(const uint32_t muxIdx)
{
    return gEIM_PcbaVitals_MuxFromIdx[muxIdx];
}
uint32_t gEIM_ServoStatus_MuxFromIdx[] = {
    0U,
    1U,
};
uint32_t CANTX_PT_GetMuxFromIdx_EIM_ServoStatus(const uint32_t muxIdx)
{
    return gEIM_ServoStatus_MuxFromIdx[muxIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// EIM_100Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_EIM_100Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_100Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_100Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_100Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_100Hz_AvgPeriod(converted, pData);
}

// EIM_100Hz_Load
void CANTX_PT_SetSRawFromFrame_EIM_100Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0xF0);
    pData[3] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[4] &= (uint8_t)(~0x3F);
    pData[4] |= (uint8_t)((((rawVal) >> 4) & 0x3F));
}
void CANTX_PT_SetSRaw_EIM_100Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_100Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_100Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_100Hz_Load(converted, pData);
}

// EIM_100Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_EIM_100Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_100Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_100Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_100Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_100Hz_MaxPeriod(converted, pData);
}

// EIM_100Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_EIM_100Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_100Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_100Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_100Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_100Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_100Hz_MinPeriod(converted, pData);
}

// EIM_10Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_EIM_10Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_10Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_10Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_10Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_10Hz_AvgPeriod(converted, pData);
}

// EIM_10Hz_Load
void CANTX_PT_SetSRawFromFrame_EIM_10Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] &= (uint8_t)(~0xC0);
    pData[4] |= (uint8_t)((((rawVal) << 6) & 0xC0));
    pData[5] = (uint8_t)((((rawVal) >> 2) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_10Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_10Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_10Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_10Hz_Load(converted, pData);
}

// EIM_10Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_EIM_10Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_10Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_10Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_10Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_10Hz_MaxPeriod(converted, pData);
}

// EIM_10Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_EIM_10Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_10Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_10Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_10Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_10Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_10Hz_MinPeriod(converted, pData);
}

// EIM_1Hz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1Hz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_1Hz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1Hz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1Hz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1Hz_AvgPeriod(converted, pData);
}

// EIM_1Hz_Load
void CANTX_PT_SetSRawFromFrame_EIM_1Hz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
    pData[7] &= (uint8_t)(~0x03);
    pData[7] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_EIM_1Hz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1Hz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1Hz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1Hz_Load(converted, pData);
}

// EIM_1Hz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1Hz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_1Hz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1Hz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1Hz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1Hz_MaxPeriod(converted, pData);
}

// EIM_1Hz_MinPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1Hz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_1Hz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1Hz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1Hz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1Hz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1Hz_MinPeriod(converted, pData);
}

// EIM_1kHz_AvgPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1kHz_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_1kHz_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1kHz_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1kHz_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1kHz_AvgPeriod(converted, pData);
}

// EIM_1kHz_Load
void CANTX_PT_SetSRawFromFrame_EIM_1kHz_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0xFC);
    pData[2] |= (uint8_t)((((rawVal) << 2) & 0xFC));
    pData[3] &= (uint8_t)(~0x0F);
    pData[3] |= (uint8_t)((((rawVal) >> 6) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_1kHz_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1kHz_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1kHz_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1kHz_Load(converted, pData);
}

// EIM_1kHz_MaxPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1kHz_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_1kHz_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1kHz_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1kHz_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1kHz_MaxPeriod(converted, pData);
}

// EIM_1kHz_MinPeriod
void CANTX_PT_SetSRawFromFrame_EIM_1kHz_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_1kHz_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_1kHz_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_1kHz_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_1kHz_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_1kHz_MinPeriod(converted, pData);
}

// EIM_ADC_AvgPeriod
void CANTX_PT_SetSRawFromFrame_EIM_ADC_AvgPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0xF0);
    pData[0] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[1] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ADC_AvgPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ADC_AvgPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ADC_AvgPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ADC_AvgPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ADC_AvgPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ADC_AvgPeriod(converted, pData);
}

// EIM_ADC_MaxPeriod
void CANTX_PT_SetSRawFromFrame_EIM_ADC_MaxPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[5] &= (uint8_t)(~0xF0);
    pData[5] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[6] = (uint8_t)((((rawVal) >> 4) & 0xFF));
    pData[7] = (uint8_t)((((rawVal) >> 12) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ADC_MaxPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ADC_MaxPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ADC_MaxPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ADC_MaxPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ADC_MaxPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ADC_MaxPeriod(converted, pData);
}

// EIM_ADC_MinPeriod
void CANTX_PT_SetSRawFromFrame_EIM_ADC_MinPeriod(const uint32_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 16) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_ADC_MinPeriod(const uint32_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ADC_MinPeriod(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ADC_MinPeriod(const float converted, uint8_t * const pData)
{
    uint32_t rawVal;
    {
        const float convertedSat = (converted > 1048.575F ? 1048.575F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint32_t)((convertedSat - 0.0F) / 0.001F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ADC_MinPeriod((uint32_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ADC_MinPeriod(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ADC_MinPeriod(converted, pData);
}

// EIM_CPU_Load
void CANTX_PT_SetSRawFromFrame_EIM_CPU_Load(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] &= (uint8_t)(~0x03);
    pData[2] |= (uint8_t)((((rawVal) >> 8) & 0x03));
}
void CANTX_PT_SetSRaw_EIM_CPU_Load(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_CPU_Load(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_CPU_Load(const float converted, uint8_t * const pData)
{
    uint16_t rawVal;
    {
        const float convertedSat = (converted > 102.3F ? 102.3F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.1F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_CPU_Load((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_CPU_Load(const float converted)
{
    uint8_t * const pData = &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_CPU_Load(converted, pData);
}

// EIM_CpuStatsMux
void CANTX_PT_SetSRawFromFrame_EIM_CpuStatsMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_CpuStatsMux((uint8_t)rawVal, pData);
}

// EIM_ECM_BatteryVoltage
void CANTX_PT_SetSRawFromFrame_EIM_ECM_BatteryVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_BatteryVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_BatteryVoltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_BatteryVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_BatteryVoltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_BatteryVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_BatteryVoltage(converted, pData);
}

// EIM_ECM_EctTemp
void CANTX_PT_SetSRawFromFrame_EIM_ECM_EctTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_EctTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_EctTemp(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_EctTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 214 ? 214 : (converted < -40 ? -40 : converted));
        rawVal = (uint8_t)((convertedSat - -40) / 1);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_EctTemp((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_EctTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_EctTemp(converted, pData);
}

// EIM_ECM_EctVoltage
void CANTX_PT_SetSRawFromFrame_EIM_ECM_EctVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_EctVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_EctVoltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_EctVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_EctVoltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_EctVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_EctVoltage(converted, pData);
}

// EIM_ECM_IatTemp
void CANTX_PT_SetSRawFromFrame_EIM_ECM_IatTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_IatTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_IatTemp(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_IatTemp(const int32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 214 ? 214 : (converted < -40 ? -40 : converted));
        rawVal = (uint8_t)((convertedSat - -40) / 1);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_IatTemp((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_IatTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_IatTemp(converted, pData);
}

// EIM_ECM_IatVoltage
void CANTX_PT_SetSRawFromFrame_EIM_ECM_IatVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_IatVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_IatVoltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_IatVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_IatVoltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_IatVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_IatVoltage(converted, pData);
}

// EIM_ECM_MapPressure
void CANTX_PT_SetSRawFromFrame_EIM_ECM_MapPressure(const uint8_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_MapPressure(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_MapPressure(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_MapPressure(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 254U ? 254U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_MapPressure((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_MapPressure(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_MapPressure(converted, pData);
}

// EIM_ECM_MapVoltage
void CANTX_PT_SetSRawFromFrame_EIM_ECM_MapVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_MapVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_MapVoltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_MapVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_MapVoltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_MapVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_MapVoltage(converted, pData);
}

// EIM_ECM_Rpm
void CANTX_PT_SetSRawFromFrame_EIM_ECM_Rpm(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_Rpm(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_Rpm(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_Rpm(const uint32_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 65534U ? 65534U : converted);
        rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_Rpm((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_Rpm(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_Rpm(converted, pData);
}

// EIM_ECM_TpsAngle
void CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsAngle(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_TpsAngle(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsAngle(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_TpsAngle(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 127.0F ? 127.0F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsAngle((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_TpsAngle(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_TpsAngle(converted, pData);
}

// EIM_ECM_TpsVoltage
void CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsVoltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_TpsVoltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsVoltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_TpsVoltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_TpsVoltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_TpsVoltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_TpsVoltage(converted, pData);
}

// EIM_ECM_VehicleSpeed
void CANTX_PT_SetSRawFromFrame_EIM_ECM_VehicleSpeed(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_ECM_VehicleSpeed(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_ECM_VehicleSpeed(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_ECM_VehicleSpeed(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 254U ? 254U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ECM_VehicleSpeed((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_ECM_VehicleSpeed(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_ECM_VehicleSpeed(converted, pData);
}

// EIM_EngineStatusMux
void CANTX_PT_SetSRawFromFrame_EIM_EngineStatusMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_EIM_EngineStatusMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_EngineStatusMux((uint8_t)rawVal, pData);
}

// EIM_PCBA_12V
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_12V(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] &= (uint8_t)(~0x0F);
    pData[3] |= (uint8_t)((((rawVal) >> 8) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_PCBA_12V(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_12V(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_12V(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 4095U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 20.47F ? 20.47F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_12V((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_12V(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_12V(converted, pData);
}

// EIM_PCBA_BrakeLightCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_BrakeLightCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_BrakeLightCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_BrakeLightCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_BrakeLightCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_BrakeLightCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_BrakeLightCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_BrakeLightCurrent(converted, pData);
}

// EIM_PCBA_DieTemp
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_DieTemp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_DieTemp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_DieTemp(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_DieTemp(const int32_q converted, uint8_t * const pData)
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
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_DieTemp((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_DieTemp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_DieTemp(converted, pData);
}

// EIM_PCBA_Eng12V
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Eng12V(const uint16_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
    pData[6] &= (uint8_t)(~0x0F);
    pData[6] |= (uint8_t)((((rawVal) >> 8) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Eng12V(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Eng12V(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Eng12V(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 4095U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 20.47F ? 20.47F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Eng12V((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Eng12V(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Eng12V(converted, pData);
}

// EIM_PCBA_EngOnCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngOnCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_EngOnCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngOnCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_EngOnCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngOnCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_EngOnCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_EngOnCurrent(converted, pData);
}

// EIM_PCBA_EngStartCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngStartCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_EngStartCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngStartCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_EngStartCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngStartCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_EngStartCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_EngStartCurrent(converted, pData);
}

// EIM_PCBA_EngTempV
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngTempV(const uint16_t rawVal, uint8_t * const pData)
{
    pData[6] &= (uint8_t)(~0xF0);
    pData[6] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[7] = (uint8_t)((((rawVal) >> 4) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_EngTempV(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngTempV(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_EngTempV(const float_q converted, uint8_t * const pData)
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
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_EngTempV((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_EngTempV(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_EngTempV(converted, pData);
}

// EIM_PCBA_FaultIndicator
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_FaultIndicator(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x01);
    pData[3] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_PT_SetSRaw_EIM_PCBA_FaultIndicator(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FaultIndicator(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_FaultIndicator(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FaultIndicator((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_FaultIndicator(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_FaultIndicator(converted, pData);
}

// EIM_PCBA_FuelLevelV
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLevelV(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
    pData[5] &= (uint8_t)(~0x0F);
    pData[5] |= (uint8_t)((((rawVal) >> 8) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_PCBA_FuelLevelV(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLevelV(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_FuelLevelV(const float_q converted, uint8_t * const pData)
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
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLevelV((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_FuelLevelV(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_FuelLevelV(converted, pData);
}

// EIM_PCBA_FuelLowV
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLowV(const uint16_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
    pData[7] &= (uint8_t)(~0x0F);
    pData[7] |= (uint8_t)((((rawVal) >> 8) & 0x0F));
}
void CANTX_PT_SetSRaw_EIM_PCBA_FuelLowV(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLowV(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_FuelLowV(const float_q converted, uint8_t * const pData)
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
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_FuelLowV((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_FuelLowV(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_FuelLowV(converted, pData);
}

// EIM_PCBA_Gear1
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear1(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x02);
    pData[1] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear1(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear1(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear1(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear1((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear1(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear1(converted, pData);
}

// EIM_PCBA_Gear2
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear2(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x04);
    pData[1] |= (uint8_t)((((rawVal) << 2) & 0x04));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear2(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear2(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear2(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear2((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear2(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear2(converted, pData);
}

// EIM_PCBA_Gear3
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear3(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x08);
    pData[1] |= (uint8_t)((((rawVal) << 3) & 0x08));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear3(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear3(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear3(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear3((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear3(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear3(converted, pData);
}

// EIM_PCBA_Gear4
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear4(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x10);
    pData[1] |= (uint8_t)((((rawVal) << 4) & 0x10));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear4(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear4(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear4(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear4((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear4(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear4(converted, pData);
}

// EIM_PCBA_Gear5
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear5(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x20);
    pData[1] |= (uint8_t)((((rawVal) << 5) & 0x20));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear5(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear5(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear5(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear5((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear5(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear5(converted, pData);
}

// EIM_PCBA_Gear6
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear6(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x40);
    pData[1] |= (uint8_t)((((rawVal) << 6) & 0x40));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Gear6(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear6(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Gear6(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Gear6((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Gear6(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Gear6(converted, pData);
}

// EIM_PCBA_GearN
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearN(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] &= (uint8_t)(~0x01);
    pData[1] |= (uint8_t)(((rawVal) & 0x01));
}
void CANTX_PT_SetSRaw_EIM_PCBA_GearN(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearN(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_GearN(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearN((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_GearN(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_GearN(converted, pData);
}

// EIM_PCBA_GearSelect
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearSelect(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] &= (uint8_t)(~0x07);
    pData[2] |= (uint8_t)(((rawVal) & 0x07));
}
void CANTX_PT_SetSRaw_EIM_PCBA_GearSelect(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearSelect(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_GearSelect(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 7U ? 7U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_GearSelect((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_GearSelect(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_GearSelect(converted, pData);
}

// EIM_PCBA_HighBeam
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeam(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x08);
    pData[3] |= (uint8_t)((((rawVal) << 3) & 0x08));
}
void CANTX_PT_SetSRaw_EIM_PCBA_HighBeam(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeam(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_HighBeam(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeam((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_HighBeam(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_HighBeam(converted, pData);
}

// EIM_PCBA_HighBeamCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeamCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_HighBeamCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeamCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_HighBeamCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HighBeamCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_HighBeamCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_HighBeamCurrent(converted, pData);
}

// EIM_PCBA_HornCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_HornCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_HornCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HornCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_HornCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_HornCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_HornCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_HornCurrent(converted, pData);
}

// EIM_PCBA_LowBeam
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_LowBeam(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x04);
    pData[3] |= (uint8_t)((((rawVal) << 2) & 0x04));
}
void CANTX_PT_SetSRaw_EIM_PCBA_LowBeam(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_LowBeam(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_LowBeam(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_LowBeam((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_LowBeam(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_LowBeam(converted, pData);
}

// EIM_PCBA_OilPressureLow
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_OilPressureLow(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x02);
    pData[3] |= (uint8_t)((((rawVal) << 1) & 0x02));
}
void CANTX_PT_SetSRaw_EIM_PCBA_OilPressureLow(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_OilPressureLow(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_OilPressureLow(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_OilPressureLow((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_OilPressureLow(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_OilPressureLow(converted, pData);
}

// EIM_PCBA_Servo12V
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_Servo12V(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0xF0);
    pData[3] |= (uint8_t)((((rawVal) << 4) & 0xF0));
    pData[4] = (uint8_t)((((rawVal) >> 4) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_Servo12V(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Servo12V(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_Servo12V(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 4095U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 20.47F ? 20.47F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_Servo12V((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_Servo12V(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_Servo12V(converted, pData);
}

// EIM_PCBA_TachFreq
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachFreq(const uint16_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
    pData[2] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TachFreq(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachFreq(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TachFreq(const uint32_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 65534U ? 65534U : converted);
        rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachFreq((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TachFreq(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TachFreq(converted, pData);
}

// EIM_PCBA_TachRpm
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachRpm(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TachRpm(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachRpm(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TachRpm(const uint32_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 65534U ? 65534U : converted);
        rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TachRpm((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TachRpm(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TachRpm(converted, pData);
}

// EIM_PCBA_TurnLCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[5] = (uint8_t)(((rawVal) & 0xFF));
    pData[6] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TurnLCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TurnLCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TurnLCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TurnLCurrent(converted, pData);
}

// EIM_PCBA_TurnLeft
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLeft(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x20);
    pData[3] |= (uint8_t)((((rawVal) << 5) & 0x20));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TurnLeft(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLeft(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TurnLeft(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnLeft((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TurnLeft(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TurnLeft(converted, pData);
}

// EIM_PCBA_TurnRCurrent
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRCurrent(const uint16_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
    pData[4] = (uint8_t)((((rawVal) >> 8) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TurnRCurrent(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRCurrent(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TurnRCurrent(const float_q converted, uint8_t * const pData)
{
    uint16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 65535U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 327.67F ? 327.67F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint16_t)((convertedSat - 0.0F) / 0.005F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRCurrent((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TurnRCurrent(const float_q converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TurnRCurrent(converted, pData);
}

// EIM_PCBA_TurnRight
void CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRight(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] &= (uint8_t)(~0x10);
    pData[3] |= (uint8_t)((((rawVal) << 4) & 0x10));
}
void CANTX_PT_SetSRaw_EIM_PCBA_TurnRight(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRight(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_PCBA_TurnRight(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 1U ? 1U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PCBA_TurnRight((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_PCBA_TurnRight(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_PCBA_TurnRight(converted, pData);
}

// EIM_PcbaVitalsMux
void CANTX_PT_SetSRawFromFrame_EIM_PcbaVitalsMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_PcbaVitalsMux((uint8_t)rawVal, pData);
}

// EIM_ServoStatusMux
void CANTX_PT_SetSRawFromFrame_EIM_ServoStatusMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_PT_SetSFromFrame_EIM_ServoStatusMux(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 15U ? 15U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_ServoStatusMux((uint8_t)rawVal, pData);
}

// EIM_Servo_Current
void CANTX_PT_SetSRawFromFrame_EIM_Servo_Current(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_Servo_Current(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Current(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_Current(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 5.08F ? 5.08F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Current((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_Current(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_Current(converted, pData);
}

// EIM_Servo_Id
void CANTX_PT_SetSRawFromFrame_EIM_Servo_Id(const uint8_t rawVal, uint8_t * const pData)
{
    pData[1] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_Servo_Id(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Id(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_Id(const uint32_t converted, uint8_t * const pData)
{
    uint8_t rawVal;
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const uint32_t convertedSat = (converted > 255U ? 255U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Id((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_Id(const uint32_t converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_Id(converted, pData);
}

// EIM_Servo_LossOfCommPosition
void CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(const uint16_t rawVal, uint8_t * const pData)
{
    pData[4] = (uint8_t)(((rawVal) & 0xFF));
    pData[5] &= (uint8_t)(~0x3F);
    pData[5] |= (uint8_t)((((rawVal) >> 8) & 0x3F));
}
void CANTX_PT_SetSRaw_EIM_Servo_LossOfCommPosition(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_LossOfCommPosition(const float_q converted, uint8_t * const pData)
{
    int16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 8192; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.775F ? -204.775F : converted));
        rawVal = (int16_t)((convertedSat - 0.0F) / 0.025F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommPosition((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_LossOfCommPosition(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_LossOfCommPosition(converted, pData);
}

// EIM_Servo_LossOfCommTimeout
void CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal, uint8_t * const pData)
{
    pData[6] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_Servo_LossOfCommTimeout(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_LossOfCommTimeout(const uint32_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        // min = 0U and converted type is unsigned, so don't need to check
        const decltype(converted.Val()) convertedSat = (converted > 254U ? 254U : converted);
        rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_LossOfCommTimeout(const uint32_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_LossOfCommTimeout(converted, pData);
}

// EIM_Servo_Position
void CANTX_PT_SetSRawFromFrame_EIM_Servo_Position(const uint16_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
    pData[3] &= (uint8_t)(~0x3F);
    pData[3] |= (uint8_t)((((rawVal) >> 8) & 0x3F));
}
void CANTX_PT_SetSRaw_EIM_Servo_Position(const uint16_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Position(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_Position(const float_q converted, uint8_t * const pData)
{
    int16_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 8192; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.775F ? -204.775F : converted));
        rawVal = (int16_t)((convertedSat - 0.0F) / 0.025F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Position((uint16_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_Position(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_Position(converted, pData);
}

// EIM_Servo_Temp
void CANTX_PT_SetSRawFromFrame_EIM_Servo_Temp(const uint8_t rawVal, uint8_t * const pData)
{
    pData[2] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_Servo_Temp(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Temp(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_Temp(const int32_q converted, uint8_t * const pData)
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
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Temp((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_Temp(const int32_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_Temp(converted, pData);
}

// EIM_Servo_Voltage
void CANTX_PT_SetSRawFromFrame_EIM_Servo_Voltage(const uint8_t rawVal, uint8_t * const pData)
{
    pData[3] = (uint8_t)(((rawVal) & 0xFF));
}
void CANTX_PT_SetSRaw_EIM_Servo_Voltage(const uint8_t rawVal)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Voltage(rawVal, pData);
}
void CANTX_PT_SetSFromFrame_EIM_Servo_Voltage(const float_q converted, uint8_t * const pData)
{
    uint8_t rawVal;
    if (!converted.Valid())
    {
        rawVal = 255U; // SNA value
    }
    else
    {
        const decltype(converted.Val()) convertedSat = (converted > 50.8F ? 50.8F : (converted < 0.0F ? 0.0F : converted));
        rawVal = (uint8_t)((convertedSat - 0.0F) / 0.2F);
    }
    CANTX_PT_SetSRawFromFrame_EIM_Servo_Voltage((uint8_t)rawVal, pData);
}
void CANTX_PT_SetS_EIM_Servo_Voltage(const float_q converted)
{
    uint8_t * const pData = &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U];
    CANTX_PT_SetSFromFrame_EIM_Servo_Voltage(converted, pData);
}

//--------------------------------------------------------------------------------------------------
// Message transmit init and run
//--------------------------------------------------------------------------------------------------
bool CANTX_PT_Init(void)
{
    // EIM_CpuStats
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        0U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        1U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M1_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        2U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M2_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        3U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M3_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        4U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M4_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_CpuStatsMux(
        5U,
        &gEIM_CpuStats_TX_ARR[CANTX_PT_EIM_CpuStats_M5_ARR_IDX][0U]
    );

    // EIM_EngineStatus
    CANTX_PT_SetSFromFrame_EIM_EngineStatusMux(
        0U,
        &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_EngineStatusMux(
        1U,
        &gEIM_EngineStatus_TX_ARR[CANTX_PT_EIM_EngineStatus_M1_ARR_IDX][0U]
    );

    // EIM_PcbaVitals
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        0U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        1U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        2U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        3U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        4U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_PcbaVitalsMux(
        5U,
        &gEIM_PcbaVitals_TX_ARR[CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX][0U]
    );

    // EIM_ServoStatus
    CANTX_PT_SetSFromFrame_EIM_ServoStatusMux(
        0U,
        &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M0_ARR_IDX][0U]
    );
    CANTX_PT_SetSFromFrame_EIM_ServoStatusMux(
        1U,
        &gEIM_ServoStatus_TX_ARR[CANTX_PT_EIM_ServoStatus_M1_ARR_IDX][0U]
    );

    // Signals SNA on init
    CANTX_PT_SetS_EIM_ECM_BatteryVoltage(float_q{});
    CANTX_PT_SetS_EIM_ECM_EctTemp(int32_q{});
    CANTX_PT_SetS_EIM_ECM_EctVoltage(float_q{});
    CANTX_PT_SetS_EIM_ECM_IatTemp(int32_q{});
    CANTX_PT_SetS_EIM_ECM_IatVoltage(float_q{});
    CANTX_PT_SetS_EIM_ECM_MapPressure(uint32_q{});
    CANTX_PT_SetS_EIM_ECM_MapVoltage(float_q{});
    CANTX_PT_SetS_EIM_ECM_Rpm(uint32_q{});
    CANTX_PT_SetS_EIM_ECM_TpsAngle(float_q{});
    CANTX_PT_SetS_EIM_ECM_TpsVoltage(float_q{});
    CANTX_PT_SetS_EIM_ECM_VehicleSpeed(uint32_q{});
    CANTX_PT_SetS_EIM_PCBA_12V(float_q{});
    CANTX_PT_SetS_EIM_PCBA_BrakeLightCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_DieTemp(int32_q{});
    CANTX_PT_SetS_EIM_PCBA_Eng12V(float_q{});
    CANTX_PT_SetS_EIM_PCBA_EngOnCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_EngStartCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_EngTempV(float_q{});
    CANTX_PT_SetS_EIM_PCBA_FuelLevelV(float_q{});
    CANTX_PT_SetS_EIM_PCBA_FuelLowV(float_q{});
    CANTX_PT_SetS_EIM_PCBA_HighBeamCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_HornCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_Servo12V(float_q{});
    CANTX_PT_SetS_EIM_PCBA_TachFreq(uint32_q{});
    CANTX_PT_SetS_EIM_PCBA_TachRpm(uint32_q{});
    CANTX_PT_SetS_EIM_PCBA_TurnLCurrent(float_q{});
    CANTX_PT_SetS_EIM_PCBA_TurnRCurrent(float_q{});
    CANTX_PT_SetS_EIM_Servo_Current(float_q{});
    CANTX_PT_SetS_EIM_Servo_LossOfCommPosition(float_q{});
    CANTX_PT_SetS_EIM_Servo_LossOfCommTimeout(uint32_q{});
    CANTX_PT_SetS_EIM_Servo_Position(float_q{});
    CANTX_PT_SetS_EIM_Servo_Temp(int32_q{});
    CANTX_PT_SetS_EIM_Servo_Voltage(float_q{});

    return true;
}

void CANTX_PT_Run1ms(void)
{
    uint32_t muxIdx = 0U;

    // EIM_CpuStats
    if (gEIM_CpuStats_muxTransmitter.ShouldTransmitMuxNow(muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_EIM_CpuStats(muxIdx);
        CANTX_PT_Transmit(CAN_PT_EIM_CpuStats_MID, CAN_PT_EIM_CpuStats_DLC, pCanData);
    }

    // EIM_EngineStatus
    if (gEIM_EngineStatus_muxTransmitter.ShouldTransmitMuxNow(muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_EIM_EngineStatus(muxIdx);
        CANTX_PT_Transmit(CAN_PT_EIM_EngineStatus_MID, CAN_PT_EIM_EngineStatus_DLC, pCanData);
    }

    // EIM_PcbaVitals
    if (gEIM_PcbaVitals_muxTransmitter.ShouldTransmitMuxNow(muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_EIM_PcbaVitals(muxIdx);
        CANTX_PT_Transmit(CAN_PT_EIM_PcbaVitals_MID, CAN_PT_EIM_PcbaVitals_DLC, pCanData);
    }

    // EIM_ServoStatus
    if (gEIM_ServoStatus_muxTransmitter.ShouldTransmitMuxNow(muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_EIM_ServoStatus(muxIdx);
        CANTX_PT_Transmit(CAN_PT_EIM_ServoStatus_MID, CAN_PT_EIM_ServoStatus_DLC, pCanData);
    }

}

} // namespace CanGen
