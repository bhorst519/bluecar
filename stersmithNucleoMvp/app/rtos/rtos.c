/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "canModule.h"
#include "cmsis_os.h"
#include "halWrappers.h"
#include "klineModule.h"
#include "rtos.h"

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void RtosInit(HalWrappers_Init_S * const pHalWrappersInitArg)
{
    HalWrappersInit(pHalWrappersInitArg);
    CanModuleInit();
    KlineModuleInit();
}

void RtosRunTask1kHz(void)
{
    uint32_t currentTick = osKernelSysTick();
    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1KHZ_MS_TO_DELAY);
        CanModuleRun();
        HalWrappersGpioToggle(GPIO_DEBUG_2);
    }
}

void RtosRunTask10Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    float pulse = 0.0F;
    float pulseInc = 0.1F;

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_10HZ_MS_TO_DELAY);
        HalWrappersGpioToggle(GPIO_LED_1);

        HalWrappersSetPwm(pulse);
        pulse += pulseInc;
        if ((pulse > 1.01F) || (pulse < 0.0F))
        {
            pulseInc = pulseInc * -1.0F;
        }
    }
}

void RtosRunTask1Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1HZ_MS_TO_DELAY);
        KlineModuleRun();
        HalWrappersGpioToggle(GPIO_LED_2);
    }
}
