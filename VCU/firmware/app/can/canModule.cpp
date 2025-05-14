/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "canModule.hpp"
#include "halWrappersComponentSpecific.hpp"
#include "PT_canReceiver.hpp"
#include "PT_canTransmitter.hpp"
#include "PT_messageInfo.hpp"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
namespace Vcu
{

UTIL_ASSERT(CANRX_PT_NUM_MESSAGES <= Shared::HAL_WRAPPERS_FILTERS_PER_BUS,
    "CAN bus with too many messages for filter config");

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
using namespace CanGen;

void CanModule::Init(void)
{
    // Driver and HAL initialization
    CANTX_PT_Init();

    for (uint32_t i = 0U; i < CANRX_PT_NUM_MESSAGES; ++i)
    {
        const uint32_t mid = CANRX_PT_GetMidFromIdx(i);
        gHalWrappers.CanRegisterRxFilter(CAN_1, mid);
    }
    gHalWrappers.CanSetRxFilters(CAN_1);
    gHalWrappers.CanStart(CAN_1);

    // Transmit manager initialization
    m_muxTransmit_VCU_CpuStats.periodMs = 1000U;
    m_muxTransmit_VCU_CpuStats.numMuxes = (CAN_PT_VCU_CpuStats_MAX_MUX_IDX + 1U);
    m_muxTransmit_VCU_CpuStats.counter = 0U;

    m_muxTransmit_VCU_PcbaVitals.periodMs = 10U;
    m_muxTransmit_VCU_PcbaVitals.numMuxes = (CAN_PT_VCU_PcbaVitals_MAX_MUX_IDX + 1U);
    m_muxTransmit_VCU_PcbaVitals.counter = 0U;
}

void CanModule::Run(void)
{
    uint32_t muxIdx = 0U;

    if (ShouldTransmitMuxNow(m_muxTransmit_VCU_CpuStats, muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_VCU_CpuStats(muxIdx);
        gHalWrappers.CanTransmit(CAN_1, CAN_PT_VCU_CpuStats_MID, CAN_PT_VCU_CpuStats_DLC, pCanData);
    }

    if (ShouldTransmitMuxNow(m_muxTransmit_VCU_PcbaVitals, muxIdx))
    {
        uint8_t * const pCanData = CANTX_PT_GetTxStorage_VCU_PcbaVitals(muxIdx);
        gHalWrappers.CanTransmit(CAN_1, CAN_PT_VCU_PcbaVitals_MID, CAN_PT_VCU_PcbaVitals_DLC, pCanData);
    }
}

bool CanModule::ShouldTransmitMuxNow(CanModule_Mux_Transmitter_S& mux, uint32_t& muxIdx) const
{
    bool transmitNow = false;
    const uint32_t muxPeriod = mux.periodMs / mux.numMuxes;
    const uint32_t maxCountFromTx = muxPeriod * mux.numMuxes;
    const uint32_t muxIdxCandidate = mux.counter / muxPeriod;

    if (   ((mux.counter % muxPeriod) == 0U)
        && (mux.counter < maxCountFromTx) )
    {
        muxIdx = muxIdxCandidate;
        transmitNow = true;
    }

    if (++mux.counter >= mux.periodMs)
    {
        mux.counter = 0U;
    }

    return transmitNow;
}

} // namespace Vcu
