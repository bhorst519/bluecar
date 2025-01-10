#include "EIM_canTransmitter.h"
#include "EIM_messageInfo.h"
#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Transmit message storage
//--------------------------------------------------------------------------------------------------
static uint8_t gEIM_ServoStatus_TX_ARR[CANTX_EIM_EIM_ServoStatus_ARR_LEN][CAN_EIM_EIM_ServoStatus_DLC];
static uint8_t gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_ARR_LEN][CAN_EIM_EIM_EngineStatus_DLC];

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
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
// EIM_ServoStatusMux
void CANTX_EIM_SetSRawFromFrame_EIM_ServoStatusMux(const uint8_t rawVal, uint8_t * const pData)
{
    pData[0] &= (uint8_t)(~0x0F);
    pData[0] |= (uint8_t)(((rawVal) & 0x0F));
}
void CANTX_EIM_SetSFromFrame_EIM_ServoStatusMux(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 15U ? 15U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_ServoStatusMux(rawVal, pData);
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_Voltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 51.0F ? 51.0F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.2F);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Voltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Voltage(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_Temp(const int32_t converted, uint8_t * const pData)
{
    const int32_t convertedSat = (converted > 205 ? 205 : (converted < -50 ? -50 : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - -50) / 1);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Temp(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Temp(const int32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_Position(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.8F ? -204.8F : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0.0F) / 0.025F);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Position(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Position(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommTimeout(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommTimeout(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_LossOfCommTimeout(const uint32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_LossOfCommPosition(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 204.775F ? 204.775F : (converted < -204.8F ? -204.8F : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0.0F) / 0.025F);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_LossOfCommPosition(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_LossOfCommPosition(const float converted)
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
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Id(rawVal, pData);
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
void CANTX_EIM_SetSFromFrame_EIM_Servo_Current(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_Servo_Current(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_Servo_Current(const float converted)
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
    const uint32_t convertedSat = (converted > 15U ? 15U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_EngineStatusMux(rawVal, pData);
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_VehicleSpeed(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_VehicleSpeed(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_VehicleSpeed(const uint32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsVoltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsVoltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_TpsVoltage(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_TpsAngle(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 127.5F ? 127.5F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.5F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_TpsAngle(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_TpsAngle(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_Rpm(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 65535U ? 65535U : (converted < 0U ? 0U : converted));
    const uint16_t rawVal = (uint16_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_Rpm(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_Rpm(const uint32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapVoltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapVoltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_MapVoltage(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_MapPressure(const uint32_t converted, uint8_t * const pData)
{
    const uint32_t convertedSat = (converted > 255U ? 255U : (converted < 0U ? 0U : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0U) / 1U);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_MapPressure(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_MapPressure(const uint32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatVoltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatVoltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_IatVoltage(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_IatTemp(const int32_t converted, uint8_t * const pData)
{
    const int32_t convertedSat = (converted > 215 ? 215 : (converted < -40 ? -40 : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - -40) / 1);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_IatTemp(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_IatTemp(const int32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctVoltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctVoltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_EctVoltage(const float converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_EctTemp(const int32_t converted, uint8_t * const pData)
{
    const int32_t convertedSat = (converted > 215 ? 215 : (converted < -40 ? -40 : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - -40) / 1);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_EctTemp(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_EctTemp(const int32_t converted)
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
void CANTX_EIM_SetSFromFrame_EIM_ECM_BatteryVoltage(const float converted, uint8_t * const pData)
{
    const float convertedSat = (converted > 5.1F ? 5.1F : (converted < 0.0F ? 0.0F : converted));
    const uint8_t rawVal = (uint8_t)((convertedSat - 0.0F) / 0.02F);
    CANTX_EIM_SetSRawFromFrame_EIM_ECM_BatteryVoltage(rawVal, pData);
}
void CANTX_EIM_SetS_EIM_ECM_BatteryVoltage(const float converted)
{
    uint8_t * const pData = &gEIM_EngineStatus_TX_ARR[CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX][0U];
    CANTX_EIM_SetSFromFrame_EIM_ECM_BatteryVoltage(converted, pData);
}

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_EIM_Init(void)
{
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
