#ifndef CAN_UTIL_HPP
#define CAN_UTIL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace CanUtil
{

struct MuxTransmitter_S
{
    const uint32_t m_periodMs;
    const uint32_t m_numMuxes;
    uint32_t m_counter;

    bool ShouldTransmitMuxNow(uint32_t& muxIdx)
    {
        bool transmitNow = false;
        const uint32_t muxPeriod = m_periodMs / m_numMuxes;
        const uint32_t maxCountFromTx = muxPeriod * m_numMuxes;
        const uint32_t muxIdxCandidate = m_counter / muxPeriod;

        if (   ((m_counter % muxPeriod) == 0U)
            && (m_counter < maxCountFromTx) )
        {
            muxIdx = muxIdxCandidate;
            transmitNow = true;
        }

        if (++m_counter >= m_periodMs)
        {
            m_counter = 0U;
        }

        return transmitNow;
    }
};

} // namespace CanUtil

#endif  // CAN_UTIL_HPP
