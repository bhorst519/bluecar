#ifndef MESSAGE_INFO_H
#define MESSAGE_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------------------------
// Transmit message info macros
//--------------------------------------------------------------------------------------------------
// SAMPLE_A_alertLog
#define SAMPLE_A_alertLog_MID (256U)
#define SAMPLE_A_alertLog_DLC (8U)

// SAMPLE_A_alertMatrix
#define SAMPLE_A_alertMatrix_MID (257U)
#define SAMPLE_A_alertMatrix_DLC (8U)

// SAMPLE_B_debug
#define SAMPLE_B_debug_MID (1792U)
#define SAMPLE_B_debug_DLC (8U)

//--------------------------------------------------------------------------------------------------
// Receive message info macros
//--------------------------------------------------------------------------------------------------
// SAMPLE_A_alertLog
#define SAMPLE_A_alertLog_MID (256U)
#define SAMPLE_A_alertLog_DLC (8U)
#define SAMPLE_A_alertLog_M5_RX_ARR_IDX (0U)
#define SAMPLE_A_alertLog_M6_RX_ARR_IDX (1U)
#define SAMPLE_A_alertLog_M8_RX_ARR_IDX (2U)
#define SAMPLE_A_alertLog_M9_RX_ARR_IDX (3U)
#define SAMPLE_A_alertLog_M20_RX_ARR_IDX (4U)
#define SAMPLE_A_alertLog_M21_RX_ARR_IDX (5U)
#define SAMPLE_A_alertLog_RX_ARR_LEN (6U)

// SAMPLE_A_alertMatrix
#define SAMPLE_A_alertMatrix_MID (257U)
#define SAMPLE_A_alertMatrix_DLC (8U)
#define SAMPLE_A_alertMatrix_RX_ARR_LEN (1U)

// SAMPLE_B_debug
#define SAMPLE_B_debug_MID (1792U)
#define SAMPLE_B_debug_DLC (8U)
#define SAMPLE_B_debug_M0_RX_ARR_IDX (0U)
#define SAMPLE_B_debug_M1_RX_ARR_IDX (1U)
#define SAMPLE_B_debug_M2_RX_ARR_IDX (2U)
#define SAMPLE_B_debug_M3_RX_ARR_IDX (3U)
#define SAMPLE_B_debug_M4_RX_ARR_IDX (4U)
#define SAMPLE_B_debug_M5_RX_ARR_IDX (5U)
#define SAMPLE_B_debug_M6_RX_ARR_IDX (6U)
#define SAMPLE_B_debug_M7_RX_ARR_IDX (7U)
#define SAMPLE_B_debug_M8_RX_ARR_IDX (8U)
#define SAMPLE_B_debug_M9_RX_ARR_IDX (9U)
#define SAMPLE_B_debug_RX_ARR_LEN (10U)

#ifdef __cplusplus
}
#endif

#endif // MESSAGE_INFO_H
