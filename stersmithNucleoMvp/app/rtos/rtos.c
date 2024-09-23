/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "halMacros.h"
#include "rtos.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define MAX_SERIAL_BUFFER_BYTES (16U)

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
Rtos_Init_S * pRtosInit;
uint8_t serialBytesTx[MAX_SERIAL_BUFFER_BYTES];
uint8_t serialBytesRx[MAX_SERIAL_BUFFER_BYTES];

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void RtosInit(Rtos_Init_S * const pRtosInitArg)
{
  pRtosInit = pRtosInitArg;
  (void)HAL_UARTEx_ReceiveToIdle_IT(pRtosInit->pSerial, &serialBytesRx[0U], MAX_SERIAL_BUFFER_BYTES);
}

void RtosRunTask10Hz(void)
{
  uint32_t currentTick = osKernelSysTick();

  TIM_OC_InitTypeDef sConfigOC = {0};
  uint16_t pulse = 0U;
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.Pulse = pulse;
  (void)HAL_TIM_PWM_Start(pRtosInit->pPwmTim, PWM_CHANNEL);

  for(;;)
  {
    osDelayUntil(&currentTick, TASK_10HZ_MS_TO_DELAY);
    HAL_GPIO_TogglePin(LED_1_PERIPH, LED_1_PIN);

    (void)HAL_TIM_PWM_ConfigChannel(pRtosInit->pPwmTim, &sConfigOC, PWM_CHANNEL);
    pulse += 5600U;
    if (pulse > 56000U) pulse = 0U;
    sConfigOC.Pulse = pulse;
  }
}

void RtosRunTask1Hz(void)
{
  uint32_t currentTick = osKernelSysTick();

  for(;;)
  {
    osDelayUntil(&currentTick, TASK_1HZ_MS_TO_DELAY);
    HAL_GPIO_TogglePin(LED_2_PERIPH, LED_2_PIN);
  }
}

//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  const uint16_t numRxBytes = (Size > 16U) ? 16U : Size;

  for (uint16_t i = 0U; i < numRxBytes; i++)
  {
    serialBytesTx[i] = serialBytesRx[i];
  }

  (void)HAL_UART_Transmit_IT(huart, &serialBytesTx[0U], numRxBytes);
  // Prepare another RX
  (void)HAL_UARTEx_ReceiveToIdle_IT(huart, &serialBytesRx[0U], MAX_SERIAL_BUFFER_BYTES);
}

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
// {
// }
