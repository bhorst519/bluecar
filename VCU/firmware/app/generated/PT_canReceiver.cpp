#include "PT_canReceiver.hpp"
#include "PT_messageInfo.hpp"
#include "stdbool.h"
#include "stdint.h"

// Used for atomic operations
#define MEM_ORDER __ATOMIC_SEQ_CST

namespace CanGen
{

//--------------------------------------------------------------------------------------------------
// Receive message storage
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Receive message ID getters for iteration
//--------------------------------------------------------------------------------------------------
uint32_t gMidFromIdx[CANRX_PT_NUM_MESSAGES] = {
};
uint32_t CANRX_PT_GetMidFromIdx(const uint32_t msgIdx)
{
    return gMidFromIdx[msgIdx];
}

//--------------------------------------------------------------------------------------------------
// Signal receive unpack functions
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Message receive storage functions
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// Message receive init and run
//--------------------------------------------------------------------------------------------------
bool CANRX_PT_Init(void)
{
    return true;
}

void CANRX_PT_Run1ms(void)
{
}

} // namespace CanGen

//--------------------------------------------------------------------------------------------------
// Message receive hook
//--------------------------------------------------------------------------------------------------
extern "C" {

bool CANRX_PT_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    (void)dlc;
    (void)pData;
    bool success = true;

    switch (mid)
    {
        default:
        {
            success = false;
            break;
        }
    }

    return success;
}

} // extern "C"
