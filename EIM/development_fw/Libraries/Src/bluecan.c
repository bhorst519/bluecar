#include "bluecan.h"

CAN_TxHeaderTypeDef   TxHeader;
uint8_t               TxData[8];
uint32_t              TxMailbox;


void startCAN(void) {
    HAL_CAN_Start(&hcan);
}

void sendCAN_engine_gear(uint8_t gear) {
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.StdId = 0x100;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = 1; 
    TxData[0] = gear;
    HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox);
}