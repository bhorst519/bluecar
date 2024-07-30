#ifndef __EIM_H
#define __EIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

uint8_t checkGear(void);
bool checkFaultIndicator(void);
bool checkHESD(void);
bool checkLowOilPressure(void);
bool checkRightTurn(void);
bool checkLeftTurn(void);
bool checkHighbeams(void);
void setHeadlights(bool state);
void setLapRelay(bool state);

#ifdef __cplusplus
}
#endif

#endif