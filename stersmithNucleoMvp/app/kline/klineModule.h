#ifndef KLINE_MODULE_H
#define KLINE_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
*                     P U B L I C   F U N C T I O N   D E C L A R A T I O N S                     *
**************************************************************************************************/
void KlineModuleInit(void);
void KlineModuleRun(void);

uint16_t KlineGetRpm(void);
float KlineGetTpsVoltage(void);
float KlineGetTpsAngle(void);
float KlineGetEctVoltage(void);
float KlineGetEctTemp(void);
float KlineGetIatVoltage(void);
float KlineGetIatTemp(void);
float KlineGetMapVoltage(void);
float KlineGetMapPressure(void);
float KlineGetBatteryVoltage(void);
float KlineGetVehicleSpeed(void);

#ifdef __cplusplus
}
#endif

#endif // KLINE_MODULE_H
