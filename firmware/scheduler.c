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
    static uint16_t u16TaskId = 0;
    static bool bTask2First = true;

    gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;

    if( u16TaskId == 0 )
    {
        u16TaskId = 2;
        // __asm(" MOV  SP, @_gu16TcbNewSp ");
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  ACC, *XAR0 ");
        __asm(" MOV  SP, AL");

        EALLOW;
        HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
        EDIS;

        /* ISR prologue */
        __asm(" IRET ");

    }
    else if( u16TaskId == 1 )
    {   
        u16TaskId = 2;
        __asm(" MOV  AL, SP ");
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  *XAR0, ACC ");
        TcbTask2.u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );

        /** TODO: The below line is getting skipped causing the control to remain in task2 always
        Find out the reason*/
        gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  ACC, *XAR0 ");
        __asm(" MOV  SP, AL");

        EALLOW;
        HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
        EDIS;
    }
    else if( u16TaskId == 2 )
    {
        u16TaskId = 1;
        __asm(" MOV  AL, SP ");
        __asm(" MOVL  XAR0, #gu16TcbNewSp ");
        __asm(" MOVL  *XAR0, ACC ");
        TcbTask1.u32StackPtr = (uint32_t)( gu16TcbNewSp & 0xFFFFU );

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
    // uint32_t * u32StackEdit =
    // *(uint32_t *)(0x411) = (uint16_t)0xA607;
    // #endif
    // EALLOW;
    // HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
    // EDIS;
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
