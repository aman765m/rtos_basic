/**
 * @file scheduler.c
 * @author Aman Singh (aman756m@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "driverlib.h"
#include "interrupt.h"
#include "task.h"
#include "scheduler.h"

typedef struct 
{
    int16_t s16NextTaskId;
    int16_t s16PrevTaskId;

} SCHEDULER_INFO_t;

volatile SCHEDULER_INFO_t xSchedulerInfo = {
    .s16NextTaskId = -1,
    .s16PrevTaskId = -1
};


static void prvInitCPUTimer0(void);

/**
 * @brief
 *
 */
void Scheduler_Init(void)
{
    prvInitCPUTimer0();
}

/**
 * @brief
 * Currently context switch is only possible at the event ISR
 * However it will be generally expected for the tasks to be periodic (apart from idle task)
 * hence the periodic tasks shall yeild to allow context switch by other tasks.
 * Tasks with 0 as period will be considered idle tasks and can be executed in round robin fashion.
 */
void Timer0_ISR(void)
{
    DINT;
    // *((uint32_t *)((uintptr_t)0x7f0e)) = 2U;
    // #if 0
    // prvScheduleTask_cb();
    
    /* Save context */
    // __asm(" ASP ");
    __asm(" PUSH    RB ");
    __asm(" PUSH    RPC ");
    __asm(" PUSH    AR1H:AR0H ");
    __asm(" PUSH    XAR2 ");
    __asm(" PUSH    XAR3 ");
    __asm(" PUSH    XAR4 ");
    __asm(" PUSH    XAR5 ");
    __asm(" PUSH    XAR6 ");
    __asm(" PUSH    XAR7 ");
    __asm(" PUSH    XT ");
    __asm(" PUSH    ACC ");
    __asm(" MOV32   *SP++, STF ");

    __asm(" MOV     AL, SP ");
    __asm(" MOVL    XAR0, #gu16TcbNewSp ");
    __asm(" MOVL    *XAR0, ACC ");

    /* A simple round robin scheduler without priority and yeilding */
    xSchedulerInfo.s16NextTaskId = ( xSchedulerInfo.s16NextTaskId + 1 ) % ( s16nTasksRegistered + 1 );
    if( xSchedulerInfo.s16PrevTaskId != -1 )
    {
        pxTaskControlBlock[ xSchedulerInfo.s16PrevTaskId ]->u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );
    }

    gu16TcbNewSp = ( uint16_t )pxTaskControlBlock[ xSchedulerInfo.s16NextTaskId ]->u32StackPtr;

    xSchedulerInfo.s16PrevTaskId = xSchedulerInfo.s16NextTaskId;

    __asm(" MOVL  XAR0, #gu16TcbNewSp ");
    __asm(" MOVL  ACC, *XAR0 ");
    __asm(" MOV  SP, AL");

    /* Restore context */
    __asm(" MOV32  STF, *--SP ");
    __asm(" POP    ACC ");
    __asm(" POP    XT ");
    __asm(" POP    XAR7 ");
    __asm(" POP    XAR6 ");
    __asm(" POP    XAR5 ");
    __asm(" POP    XAR4 ");
    __asm(" POP    XAR3 ");
    __asm(" POP    XAR2 ");
    __asm(" POP    AR1H:AR0H ");
    __asm(" POP    RPC ");
    __asm(" POP    RB ");
    // __asm(" NASP ");


    EALLOW;
    HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
    EDIS;
    EINT;
    __asm(" IRET ");
}

/**! IMPOTANT */
        // s16TaskId = 2;
        // TcbTask2.u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );
        /** TODO: The below line is getting skipped causing the control to remain in task2 always
        // Find out the reason - After declaring volatile it is working fine!*/
        // gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;
/**! IMPOTANT */

/**
 * @brief
 *
 */
static void prvInitCPUTimer0(void)
{
    EALLOW;
    /* TPR - prescaler */
    HWREG(CPUTIMER0_BASE + 6) = 1000;
    /* PRD - period */
    HWREG(CPUTIMER0_BASE + 2) = 500000;

    HWREG(PIEVECTTABLE_BASE + ((0x00260107U >> 16U) * 2U)) = (uint32_t)Timer0_ISR;

    // EDIS;

    Interrupt_enable(0x00260107U);
    // EALLOW;
    /* TCR - control - interrupt enable and start */
    HWREG(CPUTIMER0_BASE + 4) = (1U << 14);
    EDIS;
}
