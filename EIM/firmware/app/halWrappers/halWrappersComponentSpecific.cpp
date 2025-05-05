/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "PT_canReceiverHook.h"
#include "PT_canTransmitterHook.h"
#include "halWrappersComponentSpecific.hpp"
#include "profiler.h"
#include "tachComponent.h"

/***************************************************************************************************
*                    P R I V A T E   F U N C T I O N   D E C L A R A T I O N S                     *
***************************************************************************************************/
namespace Eim
{

static void HalWrappersKlineUartCallback(UART_HandleTypeDef *huart);
static void HalWrappersServoUartCallback(UART_HandleTypeDef *huart);
static void HalWrappersServoUartTxComplete(UART_HandleTypeDef *huart);

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static constexpr HalWrappers_Gpio_Info_S gGpioInfo[MAX_NUM_GPIO] = {
    // Outputs
    /* GPIO_MAIN_RELAY_EN */        {.id = GPIO_PIN_3,  .periph = GPIOF},
    /* GPIO_HEADLIGHT_RELAY_EN */   {.id = GPIO_PIN_13, .periph = GPIOE},
    /* GPIO_ENG_ON_EN */            {.id = GPIO_PIN_4,  .periph = GPIOF},
    /* GPIO_ENG_START_EN */         {.id = GPIO_PIN_5,  .periph = GPIOF},
    /* GPIO_BRAKE_LIGHT_EN */       {.id = GPIO_PIN_6,  .periph = GPIOF},
    /* GPIO_TURN_R_EN */            {.id = GPIO_PIN_9,  .periph = GPIOF},
    /* GPIO_TURN_L_EN */            {.id = GPIO_PIN_8,  .periph = GPIOF},
    /* GPIO_HIGH_BEAM_EN */         {.id = GPIO_PIN_7,  .periph = GPIOF},
    /* GPIO_HORN_EN */              {.id = GPIO_PIN_10, .periph = GPIOF},
    /* GPIO_KLINE_EN */             {.id = GPIO_PIN_2,  .periph = GPIOF},
    /* GPIO_KLINE_TX */             {.id = GPIO_PIN_9,  .periph = GPIOA},
    /* GPIO_KLINE_RX */             {.id = GPIO_PIN_10, .periph = GPIOA},
    /* GPIO_SERVO_COMM_DIR */       {.id = GPIO_PIN_4,  .periph = GPIOD},
    /* GPIO_SERVO_TX */             {.id = GPIO_PIN_5,  .periph = GPIOD},
    /* GPIO_SERVO_RX */             {.id = GPIO_PIN_6,  .periph = GPIOD},

    // Inputs
    /* GPIO_TACH */                 {.id = GPIO_PIN_12, .periph = GPIOF},
    /* GPIO_GEAR_N */               {.id = GPIO_PIN_13, .periph = GPIOF},
    /* GPIO_GEAR_1 */               {.id = GPIO_PIN_12, .periph = GPIOE},
    /* GPIO_GEAR_2 */               {.id = GPIO_PIN_11, .periph = GPIOE},
    /* GPIO_GEAR_3 */               {.id = GPIO_PIN_10, .periph = GPIOE},
    /* GPIO_GEAR_4 */               {.id = GPIO_PIN_9,  .periph = GPIOE},
    /* GPIO_GEAR_5 */               {.id = GPIO_PIN_8,  .periph = GPIOE},
    /* GPIO_GEAR_6 */               {.id = GPIO_PIN_7,  .periph = GPIOE},
    /* GPIO_TURN_R  */              {.id = GPIO_PIN_1,  .periph = GPIOG},
    /* GPIO_TURN_L  */              {.id = GPIO_PIN_0,  .periph = GPIOG},
    /* GPIO_LOW_BEAM */             {.id = GPIO_PIN_14, .periph = GPIOF},
    /* GPIO_HIGH_BEAM */            {.id = GPIO_PIN_15, .periph = GPIOF},
    /* GPIO_FAULT_IND */            {.id = GPIO_PIN_5,  .periph = GPIOC},
    /* GPIO_OIL_P_LOW */            {.id = GPIO_PIN_11, .periph = GPIOF},
};

static constexpr HalWrappers_Pwm_Info_S gPwmInfo[MAX_NUM_PWM] = {
    /* PWM_LED_1 */     {.ch = TIM_CHANNEL_3},
    /* PWM_LED_2R */    {.ch = TIM_CHANNEL_1},
    /* PWM_LED_2G */    {.ch = TIM_CHANNEL_2},
    /* PWM_LED_2B */    {.ch = TIM_CHANNEL_4},
};

static constexpr HalWrappers_Adc_Info_S gAdcInfo[MAX_NUM_ANALOG] = {
    /* ANALOG_12V                */ {.ch = ADC_CHANNEL_9,          .scale = 4.6F, .offset = 0.0F}, // Vout = Vin * (1 / 4.6)
    /* ANALOG_SERVO_12V          */ {.ch = ADC_CHANNEL_7,          .scale = 4.6F, .offset = 0.0F}, // Vout = Vin * (1 / 4.6)
    /* ANALOG_ENG_12V            */ {.ch = ADC_CHANNEL_3,          .scale = 4.6F, .offset = 0.0F}, // Vout = Vin * (1 / 4.6)
    /* ANALOG_ENG_TEMP           */ {.ch = ADC_CHANNEL_6,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_FUEL_LEVEL         */ {.ch = ADC_CHANNEL_4,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_FUEL_LOW           */ {.ch = ADC_CHANNEL_5,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_EXTRA              */ {.ch = ADC_CHANNEL_8,          .scale = 1.0F, .offset = 0.0F},
    /* ANALOG_DIE_TEMP           */ {.ch = ADC_CHANNEL_TEMPSENSOR, .scale = 400.0F, .offset = -279.0F}, // 2.5mV / degC, .76V @ 25degC
    /* ANALOG_ENG_ON_ISENSE      */ {.ch = ADC_CHANNEL_10,         .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_ENG_START_ISENSE   */ {.ch = ADC_CHANNEL_2,          .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_BRAKE_LIGHT_ISENSE */ {.ch = ADC_CHANNEL_1,          .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_TURN_R_ISENSE      */ {.ch = ADC_CHANNEL_12,         .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_TURN_L_ISENSE      */ {.ch = ADC_CHANNEL_13,         .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_HIGH_BEAM_ISENSE   */ {.ch = ADC_CHANNEL_0,          .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor
    /* ANALOG_HORN_ISENSE        */ {.ch = ADC_CHANNEL_11,         .scale = 21.2766F, .offset = 0.0F}, // I scaled down by 10000, over 470Ohm resistor

};

static constexpr HalWrappers_Uart_Info_S gUartInfo[MAX_NUM_UART] = {
    /* UART_KLINE */  { .rxPin = GPIO_KLINE_RX,
                        .txPin = GPIO_KLINE_TX,
                        .txCompleteCallback = nullptr,
                        .notifyCallback = HalWrappersKlineUartCallback
                      },
    /* UART_SERVO */  { .rxPin = GPIO_SERVO_RX,
                        .txPin = GPIO_SERVO_TX,
                        .txCompleteCallback = HalWrappersServoUartTxComplete,
                        .notifyCallback = HalWrappersServoUartCallback
                      },
};

HalWrappers gHalWrappers {
      gHalWrappersConfig
    , gGpioInfo
    , gPwmInfo
    , gAdcInfo
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

static void HalWrappersServoUartTxComplete(UART_HandleTypeDef *huart)
{
    (void)HAL_UART_UnRegisterCallback(huart, HAL_UART_TX_COMPLETE_CB_ID);

    // Enable servo UART for receive
    gHalWrappers.GpioSet(GPIO_SERVO_COMM_DIR, false);
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
// CAN transmit hook
//--------------------------------------------------------------------------------------------------
extern "C" {

void CANTX_PT_Transmit(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)
{
    Eim::gHalWrappers.CanTransmit(CAN_1, mid, dlc, pData);
}

//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == gHalWrappersConfig.pCan[CAN_1])
    {
        (void)CANRX_PT_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t data[8U];
    (void)HAL_CAN_GetRxMessage(hcan, 0U, &rxHeader, &data[0U]);

    if (hcan == gHalWrappersConfig.pCan[CAN_1])
    {
        (void)CANRX_PT_Receive(rxHeader.StdId, rxHeader.DLC, &data[0U]);
    }
    else
    {
        // Invalid pointer
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    (void)hadc;
    Eim::gHalWrappers.AdcProcessConversion();

    if (Eim::gHalWrappers.AdcGetFinished())
    {
        ProfilerCheckOut(PROFILER_ADC_CONV, true);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == Eim::gGpioInfo[GPIO_TACH].id)
    {
        TachComponentCheckIn();
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    Eim::gHalWrappers.TimerIrq(htim);
}

} // extern "C"
