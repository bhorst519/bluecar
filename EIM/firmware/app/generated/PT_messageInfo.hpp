#ifndef MESSAGE_INFO_HPP
#define MESSAGE_INFO_HPP

//--------------------------------------------------------------------------------------------------
// Transmit message info macros
//--------------------------------------------------------------------------------------------------
// EIM_CpuStats
#define CAN_PT_EIM_CpuStats_MID (1792U)
#define CAN_PT_EIM_CpuStats_DLC (8U)
#define CAN_PT_EIM_CpuStats_MAX_MUX_IDX (5U)
#define CANTX_PT_EIM_CpuStats_M0_ARR_IDX (0U)
#define CANTX_PT_EIM_CpuStats_M1_ARR_IDX (1U)
#define CANTX_PT_EIM_CpuStats_M2_ARR_IDX (2U)
#define CANTX_PT_EIM_CpuStats_M3_ARR_IDX (3U)
#define CANTX_PT_EIM_CpuStats_M4_ARR_IDX (4U)
#define CANTX_PT_EIM_CpuStats_M5_ARR_IDX (5U)
#define CANTX_PT_EIM_CpuStats_ARR_LEN (6U)
#define CANTX_PT_EIM_CpuStats_CYCLE_TIME (1000U)

// EIM_EngineStatus
#define CAN_PT_EIM_EngineStatus_MID (1800U)
#define CAN_PT_EIM_EngineStatus_DLC (8U)
#define CAN_PT_EIM_EngineStatus_MAX_MUX_IDX (1U)
#define CANTX_PT_EIM_EngineStatus_M0_ARR_IDX (0U)
#define CANTX_PT_EIM_EngineStatus_M1_ARR_IDX (1U)
#define CANTX_PT_EIM_EngineStatus_ARR_LEN (2U)
#define CANTX_PT_EIM_EngineStatus_CYCLE_TIME (1000U)

// EIM_PcbaVitals
#define CAN_PT_EIM_PcbaVitals_MID (1032U)
#define CAN_PT_EIM_PcbaVitals_DLC (8U)
#define CAN_PT_EIM_PcbaVitals_MAX_MUX_IDX (5U)
#define CANTX_PT_EIM_PcbaVitals_M0_ARR_IDX (0U)
#define CANTX_PT_EIM_PcbaVitals_M1_ARR_IDX (1U)
#define CANTX_PT_EIM_PcbaVitals_M2_ARR_IDX (2U)
#define CANTX_PT_EIM_PcbaVitals_M3_ARR_IDX (3U)
#define CANTX_PT_EIM_PcbaVitals_M4_ARR_IDX (4U)
#define CANTX_PT_EIM_PcbaVitals_M5_ARR_IDX (5U)
#define CANTX_PT_EIM_PcbaVitals_ARR_LEN (6U)
#define CANTX_PT_EIM_PcbaVitals_CYCLE_TIME (100U)

// EIM_ServoStatus
#define CAN_PT_EIM_ServoStatus_MID (1024U)
#define CAN_PT_EIM_ServoStatus_DLC (8U)
#define CAN_PT_EIM_ServoStatus_MAX_MUX_IDX (1U)
#define CANTX_PT_EIM_ServoStatus_M0_ARR_IDX (0U)
#define CANTX_PT_EIM_ServoStatus_M1_ARR_IDX (1U)
#define CANTX_PT_EIM_ServoStatus_ARR_LEN (2U)
#define CANTX_PT_EIM_ServoStatus_CYCLE_TIME (100U)

//--------------------------------------------------------------------------------------------------
// Receive message info macros
//--------------------------------------------------------------------------------------------------
#define CANRX_PT_NUM_MESSAGES (2U)

// TESTER_request
#define CAN_PT_TESTER_request_MID (519U)
#define CAN_PT_TESTER_request_DLC (4U)
#define CAN_PT_TESTER_request_MAX_MUX_IDX (0U)
#define CANRX_PT_TESTER_request_ARR_LEN (1U)

// VCU_PcbaVitals
#define CAN_PT_VCU_PcbaVitals_MID (1033U)
#define CAN_PT_VCU_PcbaVitals_DLC (8U)
#define CAN_PT_VCU_PcbaVitals_MAX_MUX_IDX (1U)
#define CANRX_PT_VCU_PcbaVitals_M0_ARR_IDX (0U)
#define CANRX_PT_VCU_PcbaVitals_M1_ARR_IDX (1U)
#define CANRX_PT_VCU_PcbaVitals_ARR_LEN (2U)

#endif // MESSAGE_INFO_HPP
