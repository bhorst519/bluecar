#ifndef MESSAGE_INFO_H
#define MESSAGE_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------------------------
// Transmit message info macros
//--------------------------------------------------------------------------------------------------
// SAMPLE_B_alertLog
#define CAN_ben_test_SAMPLE_B_alertLog_MID (258U)
#define CAN_ben_test_SAMPLE_B_alertLog_DLC (8U)
#define CAN_ben_test_SAMPLE_B_alertLog_MAX_MUX_IDX (6U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M5_ARR_IDX (0U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M6_ARR_IDX (1U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M8_ARR_IDX (2U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M9_ARR_IDX (3U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M20_ARR_IDX (4U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M21_ARR_IDX (5U)
#define CANTX_ben_test_SAMPLE_B_alertLog_M47_ARR_IDX (6U)
#define CANTX_ben_test_SAMPLE_B_alertLog_ARR_LEN (7U)

// SAMPLE_B_alertMatrix
#define CAN_ben_test_SAMPLE_B_alertMatrix_MID (259U)
#define CAN_ben_test_SAMPLE_B_alertMatrix_DLC (8U)
#define CAN_ben_test_SAMPLE_B_alertMatrix_MAX_MUX_IDX (0U)
#define CANTX_ben_test_SAMPLE_B_alertMatrix_ARR_LEN (1U)

//--------------------------------------------------------------------------------------------------
// Receive message info macros
//--------------------------------------------------------------------------------------------------
#define CANRX_ben_test_NUM_MESSAGES (2U)

// SAMPLE_A_alertLog
#define CAN_ben_test_SAMPLE_A_alertLog_MID (256U)
#define CAN_ben_test_SAMPLE_A_alertLog_DLC (8U)
#define CAN_ben_test_SAMPLE_A_alertLog_MAX_MUX_IDX (6U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M5_ARR_IDX (0U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M6_ARR_IDX (1U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M8_ARR_IDX (2U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M9_ARR_IDX (3U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M20_ARR_IDX (4U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M21_ARR_IDX (5U)
#define CANRX_ben_test_SAMPLE_A_alertLog_M47_ARR_IDX (6U)
#define CANRX_ben_test_SAMPLE_A_alertLog_ARR_LEN (7U)

// SAMPLE_A_alertMatrix
#define CAN_ben_test_SAMPLE_A_alertMatrix_MID (257U)
#define CAN_ben_test_SAMPLE_A_alertMatrix_DLC (8U)
#define CAN_ben_test_SAMPLE_A_alertMatrix_MAX_MUX_IDX (0U)
#define CANRX_ben_test_SAMPLE_A_alertMatrix_ARR_LEN (1U)

#ifdef __cplusplus
}
#endif

#endif // MESSAGE_INFO_H
