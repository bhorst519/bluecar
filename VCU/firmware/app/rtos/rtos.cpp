/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "app.hpp"
#include "cmsis_os.h"
#include "halWrappersComponentSpecific.hpp"
#include "profiler.h"
#include "rtos.h"

/***************************************************************************************************
*                         P R I V A T E   D A T A   D E F I N I T I O N S                          *
***************************************************************************************************/
static Vcu::App m_app {};

/***************************************************************************************************
*                                 P U B L I C   F U N C T I O N S                                  *
***************************************************************************************************/
void RtosInit(void)
{
    Vcu::gHalWrappers.Init();
    m_app.Init();
}

void RtosRunTask1kHz(void)
{
    uint32_t currentTick = osKernelSysTick();

    for(;;)
    {
        (void)osDelayUntil(&currentTick, TASK_1KHZ_MS_TO_DELAY);
        ProfilerScheduledTaskCheckIn();

        m_app.RunTask1kHz();

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

        Vcu::gHalWrappers.GpioSet(GPIO_LED_DEV_R, blink);
        Vcu::gHalWrappers.GpioSet(GPIO_LED_R, blink);
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

        Vcu::gHalWrappers.GpioSet(GPIO_LED_DEV_G, blink);
        Vcu::gHalWrappers.GpioSet(GPIO_LED_G, blink);
        blink = !blink;

        ProfilerUpdateLoad();
        ProfilerScheduledTaskCheckOut();
    }
}
