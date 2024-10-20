#ifndef CAN_RECEIVER_H
#define CAN_RECEIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t CANRX_SAMPLE_GetMidFromIdx(const uint32_t muxIdx);

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
// SAMPLE_B_alertID
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertID(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_alertID(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertID(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_alertID(void);

// SAMPLE_B_alertState
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_alertState(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_alertState(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_alertState(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_alertState(void);

// SAMPLE_B_a005_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data1(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_data1(void);

// SAMPLE_B_a005_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_data2(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_data2(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_data2(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_data2(void);

// SAMPLE_B_a006_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data1(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_data1(void);

// SAMPLE_B_a006_data2
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_data2(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_data2(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_data2(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_data2(void);

// SAMPLE_B_a008_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data1(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data1(void);

// SAMPLE_B_a008_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data2(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data2(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data2(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data2(void);

// SAMPLE_B_a008_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data3(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data3(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data3(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data3(void);

// SAMPLE_B_a008_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data4(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data4(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data4(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data4(void);

// SAMPLE_B_a008_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_data5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_data5(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_data5(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_data5(void);

// SAMPLE_B_a009_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data1(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data1(void);

// SAMPLE_B_a009_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data2(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data2(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data2(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data2(void);

// SAMPLE_B_a009_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data3(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data3(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data3(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data3(void);

// SAMPLE_B_a009_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data4(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data4(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data4(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data4(void);

// SAMPLE_B_a009_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_data5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_data5(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_data5(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_data5(void);

// SAMPLE_B_a020_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data1(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_data1(void);

// SAMPLE_B_a020_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data2(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data2(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data2(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data2(void);

// SAMPLE_B_a020_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data3(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data3(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data3(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_data3(void);

// SAMPLE_B_a020_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data4(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data4(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data4(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data4(void);

// SAMPLE_B_a020_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_data5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_data5(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_data5(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a020_data5(void);

// SAMPLE_B_a021_data1
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data1(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data1(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data1(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data1(void);

// SAMPLE_B_a021_data2
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data2(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data2(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data2(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a021_data2(void);

// SAMPLE_B_a021_data3
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data3(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data3(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data3(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data3(void);

// SAMPLE_B_a021_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data4(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data4(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data4(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a021_data4(void);

// SAMPLE_B_a021_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data5(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data5(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data5(void);

// SAMPLE_B_a021_data6
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_data6(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_data6(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_data6(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_data6(void);

// SAMPLE_B_a047_data1
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data1(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data1(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data1(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data1(void);

// SAMPLE_B_a047_data2
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data2(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data2(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data2(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data2(void);

// SAMPLE_B_a047_data3
uint16_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data3(const uint8_t * const pData);
uint16_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data3(void);
int32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data3(const uint8_t * const pData);
int32_t CANRX_SAMPLE_GetS_SAMPLE_B_a047_data3(void);

// SAMPLE_B_a047_data4
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data4(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data4(void);
float CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data4(const uint8_t * const pData);
float CANRX_SAMPLE_GetS_SAMPLE_B_a047_data4(void);

// SAMPLE_B_a047_data5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a047_data5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a047_data5(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a047_data5(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a047_data5(void);

// SAMPLE_B_matrixIndex
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_matrixIndex(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_matrixIndex(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_matrixIndex(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_matrixIndex(void);

// SAMPLE_B_a005_alert5
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a005_alert5(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a005_alert5(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a005_alert5(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a005_alert5(void);

// SAMPLE_B_a006_alert6
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a006_alert6(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a006_alert6(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a006_alert6(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a006_alert6(void);

// SAMPLE_B_a007_alert7
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a007_alert7(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a007_alert7(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a007_alert7(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a007_alert7(void);

// SAMPLE_B_a008_alert8
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a008_alert8(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a008_alert8(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a008_alert8(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a008_alert8(void);

// SAMPLE_B_a009_alert9
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a009_alert9(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a009_alert9(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a009_alert9(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a009_alert9(void);

// SAMPLE_B_a020_alert20
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a020_alert20(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a020_alert20(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a020_alert20(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a020_alert20(void);

// SAMPLE_B_a021_alert21
uint8_t CANRX_SAMPLE_GetSRawFromFrame_SAMPLE_B_a021_alert21(const uint8_t * const pData);
uint8_t CANRX_SAMPLE_GetSRaw_SAMPLE_B_a021_alert21(void);
uint32_t CANRX_SAMPLE_GetSFromFrame_SAMPLE_B_a021_alert21(const uint8_t * const pData);
uint32_t CANRX_SAMPLE_GetS_SAMPLE_B_a021_alert21(void);

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
bool CANRX_SAMPLE_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData);

#ifdef __cplusplus
}
#endif

#endif // CAN_RECEIVER_H
