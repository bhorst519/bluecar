#ifndef RTOS_H
#define RTOS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define TASK_1KHZ_MS_TO_DELAY   (1U)
#define TASK_100HZ_MS_TO_DELAY  (10U)
#define TASK_10HZ_MS_TO_DELAY   (100U)
#define TASK_1HZ_MS_TO_DELAY    (1000U)

/**************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                     *
**************************************************************************************************/
void RtosInit(void);
void RtosRunTask1kHz(void);
void RtosRunTask100Hz(void);
void RtosRunTask10Hz(void);
void RtosRunTask1Hz(void);

#ifdef __cplusplus
}
#endif

#endif // RTOS_H
