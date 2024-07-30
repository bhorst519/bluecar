#include "eim.h"

uint8_t checkGear(void) {
    uint8_t gear = 0xFF;
    //bool neutral = HAL_GPIO_ReadPin(NEUTRAL_GPIO_Port, NEUTRAL_Pin);
    bool neutral = 0;    //forced to zero due to bad mosfet on dev board
    bool first = HAL_GPIO_ReadPin(FIRST_GPIO_Port, FIRST_Pin);
    bool second = HAL_GPIO_ReadPin(SECOND_GPIO_Port, SECOND_Pin);
    bool third = HAL_GPIO_ReadPin(THIRD_GPIO_Port, THIRD_Pin);
    bool fourth = HAL_GPIO_ReadPin(FOURTH_GPIO_Port, FOURTH_Pin);
    bool fifth = HAL_GPIO_ReadPin(FIFTH_GPIO_Port, FIFTH_Pin);
    bool sixth = HAL_GPIO_ReadPin(SIXTH_GPIO_Port, SIXTH_Pin);

    if (neutral + first + second + third + fourth + fifth + sixth == 1) {     //evaluates true if only one gear triggers
        if (neutral == 1) {
            gear = 0;
        }
        else {
            gear = first * 1 + second * 2 + third * 3 + fourth * 4 + fifth * 5 + sixth * 6;
        }
    }
    else {
        gear = 0xFF;    //error
    }
    return gear;
}

bool checkFaultIndicator(void) {
    return HAL_GPIO_ReadPin(FAULT_INDICATOR_GPIO_Port, FAULT_INDICATOR_Pin);
}

bool checkHESD(void) {
    return HAL_GPIO_ReadPin(HESD_GPIO_Port, HESD_Pin);
}

bool checkLowOilPressure(void) {
    return HAL_GPIO_ReadPin(OIL_GPIO_Port, OIL_Pin);
}

bool checkRightTurn(void) {
    return HAL_GPIO_ReadPin(TURN_R_GPIO_Port, TURN_R_Pin);
}

bool checkLeftTurn(void) {
    return HAL_GPIO_ReadPin(TURN_L_GPIO_Port, TURN_L_Pin);
}

bool checkHighbeams(void) {
    return HAL_GPIO_ReadPin(HIGHBEAM_GPIO_Port, HIGHBEAM_Pin);
}

void setHeadlights(bool state) {
    if (state) {
        HAL_GPIO_WritePin(HEADLIGHT_RELAY_GPIO_Port, HEADLIGHT_RELAY_Pin, GPIO_PIN_SET);
    }
    else {
        HAL_GPIO_WritePin(HEADLIGHT_RELAY_GPIO_Port, HEADLIGHT_RELAY_Pin, GPIO_PIN_RESET);
    }
}

void setLapRelay(bool state) {
    if (state) {
        HAL_GPIO_WritePin(LAP_RELAY_GPIO_Port, LAP_RELAY_Pin, GPIO_PIN_SET);
    }
    else {
        HAL_GPIO_WritePin(LAP_RELAY_GPIO_Port, LAP_RELAY_Pin, GPIO_PIN_RESET);
    }
}
