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
    // prvScheduleTask_cb();
    gu16TcbNewSp = ( uint16_t )TcbTask1.u32StackPtr;
    // __asm(" MOV  SP, @_gu16TcbNewSp ");
    __asm(" MOVL  XAR0, #gu16TcbNewSp ");
    __asm(" MOVL  ACC, *XAR0 ");
    __asm(" MOV  SP, AL");

    EALLOW;
    HWREGH(PIECTRL_BASE + PIE_O_ACK) |= 1U;
    EDIS;
    // uint32_t * u32StackEdit =
    // *(uint32_t *)(0x411) = (uint16_t)0xA607;
}

/**
 * @brief
 *
 */
static void prvInitCPUTimer0(void)
{
    EALLOW;
    /* TPR - prescaler */
    HWREG(CPUTIMER0_BASE + 6) = 100;
    /* PRD - period */
    HWREG(CPUTIMER0_BASE + 2) = 100000;

    HWREG(PIEVECTTABLE_BASE + ((0x00260107U >> 16U) * 2U)) = (uint32_t)Timer0_ISR;

    // EDIS;

    Interrupt_enable(0x00260107U);
    // EALLOW;
    /* TCR - control - interrupt enable and start */
    HWREG(CPUTIMER0_BASE + 4) = (1U << 14);
    EDIS;
}
