#ifndef MESSAGE_INFO_HPP
#define MESSAGE_INFO_HPP

//--------------------------------------------------------------------------------------------------
// Transmit message info macros
//--------------------------------------------------------------------------------------------------
// EIM_CpuStats
#define CAN_EIM_EIM_CpuStats_MID (1026U)
#define CAN_EIM_EIM_CpuStats_DLC (8U)
#define CAN_EIM_EIM_CpuStats_MAX_MUX_IDX (3U)
#define CANTX_EIM_EIM_CpuStats_M0_ARR_IDX (0U)
#define CANTX_EIM_EIM_CpuStats_M1_ARR_IDX (1U)
#define CANTX_EIM_EIM_CpuStats_M2_ARR_IDX (2U)
#define CANTX_EIM_EIM_CpuStats_M3_ARR_IDX (3U)
#define CANTX_EIM_EIM_CpuStats_ARR_LEN (4U)

// EIM_ServoStatus
#define CAN_EIM_EIM_ServoStatus_MID (1025U)
#define CAN_EIM_EIM_ServoStatus_DLC (8U)
#define CAN_EIM_EIM_ServoStatus_MAX_MUX_IDX (1U)
#define CANTX_EIM_EIM_ServoStatus_M0_ARR_IDX (0U)
#define CANTX_EIM_EIM_ServoStatus_M1_ARR_IDX (1U)
#define CANTX_EIM_EIM_ServoStatus_ARR_LEN (2U)

// EIM_EngineStatus
#define CAN_EIM_EIM_EngineStatus_MID (1024U)
#define CAN_EIM_EIM_EngineStatus_DLC (8U)
#define CAN_EIM_EIM_EngineStatus_MAX_MUX_IDX (1U)
#define CANTX_EIM_EIM_EngineStatus_M0_ARR_IDX (0U)
#define CANTX_EIM_EIM_EngineStatus_M1_ARR_IDX (1U)
#define CANTX_EIM_EIM_EngineStatus_ARR_LEN (2U)

//--------------------------------------------------------------------------------------------------
// Receive message info macros
//--------------------------------------------------------------------------------------------------
#define CANRX_EIM_NUM_MESSAGES (0U)

#endif // MESSAGE_INFO_HPP
