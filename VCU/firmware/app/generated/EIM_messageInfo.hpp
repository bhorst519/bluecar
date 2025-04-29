#ifndef MESSAGE_INFO_HPP
#define MESSAGE_INFO_HPP

//--------------------------------------------------------------------------------------------------
// Transmit message info macros
//--------------------------------------------------------------------------------------------------
// VCU_CpuStats
#define CAN_EIM_VCU_CpuStats_MID (1793U)
#define CAN_EIM_VCU_CpuStats_DLC (8U)
#define CAN_EIM_VCU_CpuStats_MAX_MUX_IDX (5U)
#define CANTX_EIM_VCU_CpuStats_M0_ARR_IDX (0U)
#define CANTX_EIM_VCU_CpuStats_M1_ARR_IDX (1U)
#define CANTX_EIM_VCU_CpuStats_M2_ARR_IDX (2U)
#define CANTX_EIM_VCU_CpuStats_M3_ARR_IDX (3U)
#define CANTX_EIM_VCU_CpuStats_M4_ARR_IDX (4U)
#define CANTX_EIM_VCU_CpuStats_M5_ARR_IDX (5U)
#define CANTX_EIM_VCU_CpuStats_ARR_LEN (6U)

// VCU_PcbaVitals
#define CAN_EIM_VCU_PcbaVitals_MID (1033U)
#define CAN_EIM_VCU_PcbaVitals_DLC (8U)
#define CAN_EIM_VCU_PcbaVitals_MAX_MUX_IDX (0U)
#define CANTX_EIM_VCU_PcbaVitals_M0_ARR_IDX (0U)
#define CANTX_EIM_VCU_PcbaVitals_ARR_LEN (1U)

//--------------------------------------------------------------------------------------------------
// Receive message info macros
//--------------------------------------------------------------------------------------------------
#define CANRX_EIM_NUM_MESSAGES (0U)

#endif // MESSAGE_INFO_HPP
