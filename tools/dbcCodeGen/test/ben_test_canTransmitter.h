#ifndef CAN_TRANSMITTER_H
#define CAN_TRANSMITTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Transmit message storage getters
//--------------------------------------------------------------------------------------------------
uint8_t * CANTX_ben_test_GetTxStorage_SAMPLE_B_alertLog(const uint32_t muxIdx);
uint8_t * CANTX_ben_test_GetTxStorage_SAMPLE_B_alertMatrix(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Mux index getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANTX_ben_test_GetMuxFromIdx_SAMPLE_B_alertLog(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal transmit setter functions
//--------------------------------------------------------------------------------------------------
// SAMPLE_B_alertID
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertID(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertID(const uint32_t converted, uint8_t * const pData);

// SAMPLE_B_alertState
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_alertState(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_alertState(const uint32_t converted, uint8_t * const pData);

// SAMPLE_B_a005_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data1(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_data1(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a005_data1(const uint32_t converted);

// SAMPLE_B_a005_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_data2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_data2(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_data2(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a005_data2(const uint32_t converted);

// SAMPLE_B_a006_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data1(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_data1(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a006_data1(const uint32_t converted);

// SAMPLE_B_a006_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_data2(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_data2(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_data2(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a006_data2(const uint32_t converted);

// SAMPLE_B_a008_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data1(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data1(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_data1(const uint32_t converted);

// SAMPLE_B_a008_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data2(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data2(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_data2(const uint32_t converted);

// SAMPLE_B_a008_data3
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data3(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data3(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data3(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_data3(const uint32_t converted);

// SAMPLE_B_a008_data4
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data4(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data4(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_data4(const uint32_t converted);

// SAMPLE_B_a008_data5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_data5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_data5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_data5(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_data5(const uint32_t converted);

// SAMPLE_B_a009_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data1(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data1(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_data1(const uint32_t converted);

// SAMPLE_B_a009_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data2(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data2(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_data2(const uint32_t converted);

// SAMPLE_B_a009_data3
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data3(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data3(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data3(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_data3(const uint32_t converted);

// SAMPLE_B_a009_data4
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data4(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data4(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_data4(const uint32_t converted);

// SAMPLE_B_a009_data5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_data5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_data5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_data5(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_data5(const uint32_t converted);

// SAMPLE_B_a020_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data1(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data1(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_data1(const uint32_t converted);

// SAMPLE_B_a020_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data2(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data2(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_data2(const float converted);

// SAMPLE_B_a020_data3
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data3(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data3(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data3(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_data3(const uint32_t converted);

// SAMPLE_B_a020_data4
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data4(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data4(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_data4(const float converted);

// SAMPLE_B_a020_data5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_data5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_data5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_data5(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_data5(const float converted);

// SAMPLE_B_a021_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data1(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data1(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data1(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data1(const uint32_t converted);

// SAMPLE_B_a021_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data2(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data2(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data2(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data2(const float converted);

// SAMPLE_B_a021_data3
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data3(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data3(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data3(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data3(const uint32_t converted);

// SAMPLE_B_a021_data4
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data4(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data4(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data4(const float converted);

// SAMPLE_B_a021_data5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data5(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data5(const uint32_t converted);

// SAMPLE_B_a021_data6
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_data6(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_data6(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_data6(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_data6(const uint32_t converted);

// SAMPLE_B_a047_data1
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data1(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data1(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data1(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a047_data1(const float converted);

// SAMPLE_B_a047_data2
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data2(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data2(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data2(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a047_data2(const float converted);

// SAMPLE_B_a047_data3
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data3(const uint16_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data3(const uint16_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data3(const int32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a047_data3(const int32_t converted);

// SAMPLE_B_a047_data4
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data4(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data4(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data4(const float converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a047_data4(const float converted);

// SAMPLE_B_a047_data5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a047_data5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a047_data5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a047_data5(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a047_data5(const uint32_t converted);

// SAMPLE_B_matrixIndex
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_matrixIndex(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_matrixIndex(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_matrixIndex(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_matrixIndex(const uint32_t converted);

// SAMPLE_B_a005_alert5
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a005_alert5(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a005_alert5(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a005_alert5(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a005_alert5(const uint32_t converted);

// SAMPLE_B_a006_alert6
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a006_alert6(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a006_alert6(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a006_alert6(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a006_alert6(const uint32_t converted);

// SAMPLE_B_a007_alert7
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a007_alert7(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a007_alert7(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a007_alert7(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a007_alert7(const uint32_t converted);

// SAMPLE_B_a008_alert8
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a008_alert8(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a008_alert8(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a008_alert8(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a008_alert8(const uint32_t converted);

// SAMPLE_B_a009_alert9
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a009_alert9(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a009_alert9(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a009_alert9(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a009_alert9(const uint32_t converted);

// SAMPLE_B_a020_alert20
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a020_alert20(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a020_alert20(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a020_alert20(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a020_alert20(const uint32_t converted);

// SAMPLE_B_a021_alert21
void CANTX_ben_test_SetSRawFromFrame_SAMPLE_B_a021_alert21(const uint8_t rawVal, uint8_t * const pData);
void CANTX_ben_test_SetSRaw_SAMPLE_B_a021_alert21(const uint8_t rawVal);
void CANTX_ben_test_SetSFromFrame_SAMPLE_B_a021_alert21(const uint32_t converted, uint8_t * const pData);
void CANTX_ben_test_SetS_SAMPLE_B_a021_alert21(const uint32_t converted);

//--------------------------------------------------------------------------------------------------
// Message transmit init
//--------------------------------------------------------------------------------------------------
bool CANTX_ben_test_Init(void);

#ifdef __cplusplus
}
#endif

#endif // CAN_TRANSMITTER_H
