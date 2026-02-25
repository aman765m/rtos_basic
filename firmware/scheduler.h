/**
 * @file scheduler.h
 * @author Aman Singh (aman756m@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

extern volatile uint16_t gu16TcbNewSp;

static inline void prvScheduleTask_cb( void )
{  
    static uint16_t u16ActiveTask = 0;

    if( u16ActiveTask == 0 )
    {
        /* Load the task's stack pointer value into SP */
        gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;
        // __asm(" MOV  SP, @_gu16TcbNewSp ");
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  ACC, *XAR0 ");
        __asm(" MOV  SP, AL");
        /* Pop the task's context from stack */
        /* Call IRET for remaining POP and branching */
    }
}

void Scheduler_Init(void);

#endif
