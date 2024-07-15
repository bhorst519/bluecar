#include "eim.h"

uint8_t checkGear(void) {
    uint8_t gear = 0xFF;
    uint8_t neutral = HAL_GPIO_ReadPin(NEUTRAL_GPIO_Port, NEUTRAL_Pin);
    uint8_t first = HAL_GPIO_ReadPin(FIRST_GPIO_Port, FIRST_Pin);
    uint8_t second = HAL_GPIO_ReadPin(SECOND_GPIO_Port, SECOND_Pin);
    uint8_t third = HAL_GPIO_ReadPin(THIRD_GPIO_Port, THIRD_Pin);
    uint8_t fourth = HAL_GPIO_ReadPin(FOURTH_GPIO_Port, FOURTH_Pin);
    uint8_t fifth = HAL_GPIO_ReadPin(FIFTH_GPIO_Port, FIFTH_Pin);
    uint8_t sixth = HAL_GPIO_ReadPin(SIXTH_GPIO_Port, SIXTH_Pin);

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

