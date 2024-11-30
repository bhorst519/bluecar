/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "canModule.hpp"
#include "halWrappers.h"
#include "SAMPLE_canReceiver.h"
#include "SAMPLE_canTransmitter.h"
#include "SAMPLE_messageInfo.h"
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
UTIL_ASSERT(CANRX_SAMPLE_NUM_MESSAGES <= HAL_WRAPPERS_FILTERS_PER_BUS,
    "CAN bus with too many messages for filter config");

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
namespace Eim
{

void CanModule::Init(void)
{
    // Driver and HAL initialization
    CANTX_SAMPLE_Init();

    for (uint32_t i = 0U; i < CANRX_SAMPLE_NUM_MESSAGES; ++i)
    {
        const uint32_t mid = CANRX_SAMPLE_GetMidFromIdx(i);
        HalWrappersCanRegisterRxFilter(CAN_1, mid);
    }
    HalWrappersCanSetRxFilters(CAN_1);
    HalWrappersCanStart(CAN_1);

    // Transmit manager initialization
    m_muxTransmit_SAMPLE_A_alertLog.periodMs = 10U;
    m_muxTransmit_SAMPLE_A_alertLog.numMuxes = (CAN_SAMPLE_SAMPLE_A_alertLog_MAX_MUX_IDX + 1U);
    m_muxTransmit_SAMPLE_A_alertLog.counter = 0U;

    m_muxTransmit_SAMPLE_A_alertMatrix.periodMs = 1000U;
    m_muxTransmit_SAMPLE_A_alertMatrix.numMuxes = (CAN_SAMPLE_SAMPLE_A_alertMatrix_MAX_MUX_IDX + 1U);
    m_muxTransmit_SAMPLE_A_alertMatrix.counter = 0U;
}

void CanModule::Run(void)
{
    uint32_t muxIdx = 0U;

    if (ShouldTransmitMuxNow(m_muxTransmit_SAMPLE_A_alertLog, muxIdx))
    {
        uint8_t * const pCanData = CANTX_SAMPLE_GetTxStorage_SAMPLE_A_alertLog(muxIdx);

        const uint32_t mux = CANTX_SAMPLE_GetMuxFromIdx_SAMPLE_A_alertLog(muxIdx);
        if (mux == 20U)
        {
            static bool alertState = false;
            CANTX_SAMPLE_SetSFromFrame_SAMPLE_A_alertState((uint32_t)alertState, pCanData);
            alertState = !alertState;

            static float data2 = 0.0F;
            static float data4 = 15.0F;
            static float data5 = 37.0F;
            CANTX_SAMPLE_SetS_SAMPLE_A_a020_data2(data2);
            CANTX_SAMPLE_SetS_SAMPLE_A_a020_data4(data4);
            CANTX_SAMPLE_SetS_SAMPLE_A_a020_data5(data5);
            data2 += 10.0F; if (data2 > 100.1F) {data2 = 0.0F;}
            data4 += 10.0F; if (data4 > 100.1F) {data4 = 5.0F;}
            data5 += 10.0F; if (data5 > 100.1F) {data5 = 7.0F;}
        }
        else if (mux == 47U)
        {
            static bool alertState = true;
            CANTX_SAMPLE_SetSFromFrame_SAMPLE_A_alertState((uint32_t)(alertState), pCanData);
            alertState = !alertState;

            static float data1 = 0.0F; static bool data1Up = true;
            static float data2 = 2.33F; static bool data2Up = true;
            static float data3 = 0.0F; static bool data3Up = true;
            CANTX_SAMPLE_SetS_SAMPLE_A_a047_data1(data1); // 0 to 5.115
            CANTX_SAMPLE_SetS_SAMPLE_A_a047_data2(data2); // 0 to 5.115
            CANTX_SAMPLE_SetS_SAMPLE_A_a047_data3((int32_t)data3); // -2560 to 2555
            if (data1Up) {data1 += 0.375F; if (data1 >=  5.625F) {data1 =  5.625F; data1Up = false;} }
            else         {data1 -= 0.375F; if (data1 <= -0.75F)  {data1 = -0.75F;  data1Up = true;} }
            if (data2Up) {data2 += 0.375F; if (data2 >=  5.625F) {data2 =  5.625F; data2Up = false;} }
            else         {data2 -= 0.375F; if (data2 <= -0.75F)  {data2 = -0.75;   data2Up = true;} }
            if (data3Up) {data3 += 212.0F; if (data3 >=  2968.0F) {data3 =  2968.0F; data3Up = false;} }
            else         {data3 -= 212.0F; if (data3 <= -2968.0F) {data3 = -2968.0F; data3Up = true;} }
        }
        else
        {
            // Do nothing
        }

        HalWrappersCanTransmit(CAN_1, CAN_SAMPLE_SAMPLE_A_alertLog_MID, CAN_SAMPLE_SAMPLE_A_alertLog_DLC, pCanData);
    }

    if (ShouldTransmitMuxNow(m_muxTransmit_SAMPLE_A_alertMatrix, muxIdx))
    {
        const uint8_t * const pCanData = CANTX_SAMPLE_GetTxStorage_SAMPLE_A_alertMatrix(muxIdx);
        HalWrappersCanTransmit(CAN_1, CAN_SAMPLE_SAMPLE_A_alertMatrix_MID, CAN_SAMPLE_SAMPLE_A_alertMatrix_DLC, pCanData);
    }

    // Echo demo
    uint32_t intVal;
    float floatVal;
    intVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data1();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data1(intVal);
    floatVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data2();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data2(floatVal);
    intVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data3();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data3(intVal);
    floatVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data4();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data4(floatVal);
    intVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data5();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data5(intVal);
    intVal = CANRX_SAMPLE_GetS_SAMPLE_B_a021_data6();
    CANTX_SAMPLE_SetS_SAMPLE_A_a021_data6(intVal);
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

} // namespace Eim
