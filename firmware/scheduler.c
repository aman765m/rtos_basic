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
 *
 */
__interrupt void Timer0_ISR(void)
{
    // *((uint32_t *)((uintptr_t)0x7f0e)) = 2U;
    // #if 0
    // prvScheduleTask_cb();
    static uint16_t u16TaskId = 1;
    static bool bTask1First = true;
    static bool bTask2First = true;

    /* Save context */
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

    if( u16TaskId == 1 )
    {   
        u16TaskId = 2;
        if( !bTask1First )
        {
            __asm(" MOV  AL, SP ");
            __asm(" MOVL  XAR0, #gu16TcbNewSp ");
            __asm(" MOVL  *XAR0, ACC ");
            TcbTask2.u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );
        }

        /** TODO: The below line is getting skipped causing the control to remain in task2 always
        Find out the reason - After declaring volatile it is working fine!*/
        gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  ACC, *XAR0 ");
        __asm(" MOV  SP, AL");

        EALLOW;
        HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
        EDIS;

        if( bTask1First )
        {
            bTask1First = false;
            __asm(" IRET ");
        }
    }
    else if( u16TaskId == 2 )
    {
        u16TaskId = 1;
        if( bTask2First )
        {
            __asm(" MOV  AL, SP ");
            __asm(" MOVL  XAR0, #gu16TcbNewSp ");
            __asm(" MOVL  *XAR0, ACC ");
            TcbTask1.u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );
        }

        gu16TcbNewSp = ( uint16_t )TcbTask2.u32StackPtr;
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  ACC, *XAR0 ");
        __asm(" MOV  SP, AL");

        EALLOW;
        HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
        EDIS;

        if( bTask2First )
        {
            bTask2First = false;
            __asm(" IRET ");
        }
    }

    /* Restore context */
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
}

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
