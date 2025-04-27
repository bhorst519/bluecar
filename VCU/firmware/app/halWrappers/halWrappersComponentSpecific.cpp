/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "cmsis_os.h"
#include "EIM_canReceiverHook.h"
#include "halWrappersComponentSpecific.hpp"
#include "profiler.h"

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
namespace Vcu
{

static constexpr HalWrappers_Gpio_Info_S gGpioInfo[MAX_NUM_GPIO] = {
    // Outputs
    /* GPIO_LED_DEV_G       */  {.id = GPIO_PIN_0,  .periph = GPIOB},
    /* GPIO_LED_DEV_B       */  {.id = GPIO_PIN_7,  .periph = GPIOB},
    /* GPIO_LED_DEV_R       */  {.id = GPIO_PIN_14, .periph = GPIOB},
    /* GPIO_LED_R           */  {.id = GPIO_PIN_7,  .periph = GPIOD},
    /* GPIO_LED_G           */  {.id = GPIO_PIN_6,  .periph = GPIOD},

    // Inputs
    /* GPIO_ENG_ENABLE      */  {.id = GPIO_PIN_3,  .periph = GPIOF},
    /* GPIO_ENG_START       */  {.id = GPIO_PIN_5,  .periph = GPIOF},
    /* GPIO_USER_SWITCH     */  {.id = GPIO_PIN_10, .periph = GPIOF},
    /* GPIO_BRAKE_SWITCH    */  {.id = GPIO_PIN_3,  .periph = GPIOC},
};

static constexpr HalWrappers_Adc_Info_S gAdcInfo[MAX_NUM_ANALOG] = {
    /* ANALOG_APS_1 */  {.ch = ADC_CHANNEL_3,   .scale = 1.0F,  .offset = 0.0F},
    /* ANALOG_APS_2 */  {.ch = ADC_CHANNEL_10,  .scale = 1.0F,  .offset = 0.0F},

};

HalWrappers gHalWrappers {
      gHalWrappersConfig
    , gGpioInfo
    , gAdcInfo
};

/***************************************************************************************************
*                                 M E T H O D  D E F I N I T I O N S                               *
***************************************************************************************************/
void HalWrappers::Init(void)
{
    (void)HAL_TIM_Base_Start(gHalWrappersConfig.pUsTim);
}

} // namespace Vcu

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// ISR callbacks
//--------------------------------------------------------------------------------------------------
extern "C" {

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
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
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
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
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    (void)hadc;
    Vcu::gHalWrappers.AdcProcessConversion();

    if (Vcu::gHalWrappers.AdcGetFinished())
    {
        ProfilerCheckOut(PROFILER_ADC_CONV, true);
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    Vcu::gHalWrappers.TimerIrq(htim);
}

} // extern "C"
