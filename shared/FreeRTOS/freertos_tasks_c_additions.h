// This file will be injected into FreeRTOS tasks.c as source.
// It will be consumed elsewhere as a header.

#ifndef FREERTOS_TASK_ADDITIONS_AS_HEADER
#define FREERTOS_TASK_ADDITIONS_AS_HEADER (0)
#endif

//--------------------------------------------------------------------------------------------------
// As header
//--------------------------------------------------------------------------------------------------
#if FREERTOS_TASK_ADDITIONS_AS_HEADER

#ifndef FREERTOS_TASKS_C_ADDITIONS_H
#define FREERTOS_TASKS_C_ADDITIONS_H

#ifdef __cplusplus
extern "C" {
#endif

uint32_t ulTaskGetRunTimeCounter( const TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

#ifdef __cplusplus
}
#endif

#endif // FREERTOS_TASKS_C_ADDITIONS_H

//--------------------------------------------------------------------------------------------------
// As source
//--------------------------------------------------------------------------------------------------
#else

uint32_t ulTaskGetRunTimeCounter( const TaskHandle_t xTask )
{
    TCB_t const *pxTCB;

    /* If null is passed in here then it is the priority of the task
    that called uxTaskPriorityGet() that is being queried. */
    pxTCB = prvGetTCBFromHandle( xTask );

    return pxTCB->ulRunTimeCounter;
}

#endif
