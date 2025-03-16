/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "app.hpp"
#include "cmsis_os.h"
#include "halWrappers.hpp"
#include "profiler.h"
#include "rtos.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#define PWM_ON_RGB (0.8F)
#define PWM_OFF_RGB (1.0F)
#define PWM_ON_1 (1.0F)
#define PWM_OFF_1 (0.0F)

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static Eim::App m_app {};

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void RtosInit(HalWrappers_Config_S * const pHalWrappersConfig)
{
    Eim::HalWrappersInit(pHalWrappersConfig);
    m_app.Init();

    Eim::HalWrappersSetPwm(PWM_LED_2R, 1.0F);
    Eim::HalWrappersSetPwm(PWM_LED_2G, 1.0F);
    Eim::HalWrappersSetPwm(PWM_LED_2B, 1.0F);
}

void RtosRunTask1kHz(void)
{
    uint32_t currentTick = osKernelSysTick();

    float pulse = 0.0F;
    float pulseInc = 0.001F;

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1KHZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        m_app.RunTask1kHz();

        Eim::HalWrappersSetPwm(PWM_LED_1, pulse);
        pulse += pulseInc;
        if ((pulse > PWM_ON_1) || (pulse < PWM_OFF_1))
        {
            pulseInc = pulseInc * -1.0F;
        }

        ProfilerScheduledTaskCheckOut();
    }
}

void RtosRunTask100Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_100HZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        m_app.RunTask100Hz();

        ProfilerScheduledTaskCheckOut();
    }
}

void RtosRunTask10Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    bool blink = false;

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_10HZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        m_app.RunTask10Hz();

        Eim::HalWrappersSetPwm(PWM_LED_2B, (blink ? PWM_ON_RGB : PWM_OFF_RGB));
        blink = !blink;

        ProfilerScheduledTaskCheckOut();
    }
}

void RtosRunTask1Hz(void)
{
    uint32_t currentTick = osKernelSysTick();

    bool blink = false;

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1HZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        m_app.RunTask1Hz();

        Eim::HalWrappersSetPwm(PWM_LED_2R, (blink ? PWM_ON_RGB : PWM_OFF_RGB));
        blink = !blink;

        ProfilerUpdateLoad();
        ProfilerScheduledTaskCheckOut();
    }
}
