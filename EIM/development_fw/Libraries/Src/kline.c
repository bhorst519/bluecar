#include "kline.h"

void sendECUWakeupPulse() {
    HAL_UART_DeInit(&huart1);
    setTXPinAsOutput();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
    HAL_Delay(70);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    HAL_Delay(130);
    HAL_UART_Init(&huart1);
}
void pingECU() {
    uint8_t ECU_WAKEUP_MESSAGE[] = {0xFE, 0x04, 0x72, 0x8C}; 
    HAL_UART_Transmit(&huart1, ECU_WAKEUP_MESSAGE, sizeof(ECU_WAKEUP_MESSAGE), HAL_MAX_DELAY);
    HAL_Delay(50);
    uint8_t rx_buff[10];
    if(HAL_UART_Receive(&huart1, rx_buff, 10, 1000) == HAL_OK) {
        printf("Ping response: ");
        HAL_UART_Transmit(&huart2, rx_buff, sizeof(rx_buff), HAL_MAX_DELAY);
    }
}

void requestECUState() {
    uint8_t ECU_INIT_MESSAGE[] = {0x72, 0x05, 0x71, 0x00, 0x18};
    HAL_UART_Transmit(&huart1, ECU_INIT_MESSAGE, sizeof(ECU_INIT_MESSAGE), HAL_MAX_DELAY);
    HAL_Delay(50);
    uint8_t rx_buff[10];
    HAL_UART_Receive(&huart1, rx_buff, 10, 1000);
    if(HAL_UART_Receive(&huart1, rx_buff, 10, 1000) == HAL_OK) {
        printf("ECU state response: ");
        HAL_UART_Transmit(&huart2, rx_buff, sizeof(rx_buff), HAL_MAX_DELAY);
    }
}