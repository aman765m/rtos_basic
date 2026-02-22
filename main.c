// #############################################################################
//
//  FILE:   empty_sysconfig_main.c
//
//  TITLE:  Empty Pinmux Example
//
//! \addtogroup driver_example_list
//! <h1> Empty SysCfg & Driverlib Example </h1>
//!
//! This example is an empty project setup for SysConfig and Driverlib
//! development.
//
// #############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
// #############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
// #include <hw_ints.h>
#include "interrupt.h"

void InitCPUTimer0(void);

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure ePWM1, ePWM2, and TZ GPIOs/Modules
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    // Enter code here
    GPIO_setDirectionMode(33, GPIO_DIR_MODE_OUT);
    InitCPUTimer0();
    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for (;;)
    {
        // Enter code here
    }
}

__interrupt void Timer0_ISR(void)
{
    GPIO_togglePin(33);
    EALLOW;
    HWREGH( PIECTRL_BASE + PIE_O_ACK ) |= 1U;
    EDIS;
    // uint32_t * u32StackEdit = 
    *(uint32_t *)(0x411) = (uint16_t)0xA607;
}

void InitCPUTimer0(void)
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

//
// End of File
//
