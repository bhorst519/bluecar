/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canReceiverHook.h"
#include "halWrappersComponentSpecific.hpp"

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/
namespace Eim
{

static void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart);
static void HalWrappersServoUartCallback(UART_HandleTypeDef *huart);

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static constexpr HalWrappers_Gpio_Info_S gGpioInfo[MAX_NUM_GPIO] = {
    /* GPIO_LED_1 */        {.id = GPIO_PIN_0,  .periph = GPIOB},
    /* GPIO_LED_2 */        {.id = GPIO_PIN_7,  .periph = GPIOB},
    /* GPIO_SERVO_TX_EN */  {.id = GPIO_PIN_13, .periph = GPIOE},
    /* GPIO_KLINE_TX */     {.id = GPIO_PIN_8,  .periph = GPIOD},
    /* GPIO_KLINE_RX */     {.id = GPIO_PIN_9,  .periph = GPIOD},
    /* GPIO_SERVO_TX */     {.id = GPIO_PIN_6,  .periph = GPIOC},
    /* GPIO_SERVO_RX */     {.id = GPIO_PIN_7,  .periph = GPIOC},
    /* GPIO_DEBUG_1 */      {.id = GPIO_PIN_9,  .periph = GPIOG},
    /* GPIO_DEBUG_2 */      {.id = GPIO_PIN_14, .periph = GPIOG},
    /* GPIO_DEBUG_3 */      {.id = GPIO_PIN_15, .periph = GPIOF},
};

static constexpr HalWrappers_Pwm_Info_S gPwmInfo[MAX_NUM_PWM] = {
    /* PWM_LED_1 */ {.ch = TIM_CHANNEL_1},
};

static constexpr HalWrappers_Uart_Info_S gUartInfo[MAX_NUM_UART] = {
    /* UART_KLINE */  { .rxPin = GPIO_KLINE_RX,
                        .txPin = GPIO_KLINE_TX,
                        .txCompleteCallback = nullptr,
                        .notifyCallback = HalWrappersKlineUartCallback
                      },
    /* UART_SERVO */  { .rxPin = GPIO_SERVO_RX,
                        .txPin = GPIO_SERVO_TX,
                        .txCompleteCallback = nullptr,
                        .notifyCallback = HalWrappersServoUartCallback
                      },
};

HalWrappers gHalWrappers {
      gHalWrappersConfig
    , gGpioInfo
    , gPwmInfo
    , gUartInfo
};

/***************************************************************************************************
*                                P R I V A T E   F U N C T I O N S                                 *
***************************************************************************************************/
static void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart)
{
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_RX_COMPLETE_CB_ID);

    // Task notify
    osThreadId taskToNotify = gHalWrappers.UartGetTaskToNotify(UART_KLINE);
    if (NULL != taskToNotify)
    {
        (void)osSignalSet(taskToNotify, 0);
    }

    // Yield if no task assigned
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void HalWrappersServoUartCallback(UART_HandleTypeDef *huart)
{
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID);
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_RX_COMPLETE_CB_ID);

    // Task notify
    osThreadId taskToNotify = gHalWrappers.UartGetTaskToNotify(UART_SERVO);
    if (NULL != taskToNotify)
    {
        (void)osSignalSet(taskToNotify, 0);
    }

    // Yield if no task assigned
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void HalWrappers::Init(void)
{
    // PWM - start, disabled
    for (uint8_t i = 0U; i < static_cast<uint8_t>(MAX_NUM_PWM); ++i)
    {
        (void)HAL_TIM_PWM_Start(gHalWrappersConfig.pPwmTim, gPwmInfo[i].ch);
    }
    (void)HAL_TIM_Base_Start(gHalWrappersConfig.pUsTim);
}

} // namespace Eim

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
extern "C" {

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    Eim::gHalWrappers.GpioToggle(GPIO_DEBUG_1);

    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == gHalWrappersConfig.pCan[CAN_1])
    {
        (void)CANRX_EIM_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }

    Eim::gHalWrappers.GpioToggle(GPIO_DEBUG_1);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    Eim::gHalWrappers.GpioToggle(GPIO_DEBUG_1);

    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == gHalWrappersConfig.pCan[CAN_1])
    {
        (void)CANRX_EIM_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }

    Eim::gHalWrappers.GpioToggle(GPIO_DEBUG_1);
}

} // extern "C"
