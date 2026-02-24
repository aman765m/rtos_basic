/**
 * @file task.c
 * @author Aman Singh (aman756m@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "task.h"
#include "interrupt.h"
#include <string.h>
#include "driverlib.h"

TCB_t TcbTask1;
TCB_t TcbTask2;

volatile uint16_t gu16TcbNewSp;

#ifdef _FLASH
extern void _task_copy_table;

/**
 * @brief Function prototypes
 *
 */
#pragma SET_CODE_SECTION( "sec_task1")
void Task1(void);
#pragma SET_CODE_SECTION()

#pragma SET_CODE_SECTION( "sec_task2")
void Task2(void);
#pragma SET_CODE_SECTION()
#else
void Task1(void);
void Task2(void);
#endif
/**
 * @brief
 *
 */
void Task_Init(void)
{
#ifdef _FLASH
    /* Load the tasks into RAM */
    copy_in( ( COPY_TABLE * )&_task_copy_table );
#endif

    memset( ( void * )&TcbTask1.u16Stack, 0, sizeof( TcbTask1.u16Stack ) );
    memset( ( void * )&TcbTask2.u16Stack, 0, sizeof( TcbTask2.u16Stack ) );

    TcbTask1.u16Stack[ STF_OFFSET_ST0 ] = STF_VAL_ST0;
    TcbTask1.u16Stack[ STF_OFFSET_ST1 ] = STF_VAL_ST1;
    TcbTask1.u16Stack[ STF_OFFSET_DP ]  = STF_VAL_DP;
    TcbTask1.u16Stack[ STF_OFFSET_IER ] = STF_VAL_IER;
    TcbTask1.u16Stack[ STF_OFFSET_PC ]  = STF_VAL_PC_T1;

    TcbTask2.u16Stack[ STF_OFFSET_ST0 ] = STF_VAL_ST0;
    TcbTask2.u16Stack[ STF_OFFSET_ST1 ] = STF_VAL_ST1;
    TcbTask2.u16Stack[ STF_OFFSET_DP ]  = STF_VAL_DP;
    TcbTask2.u16Stack[ STF_OFFSET_IER ] = STF_VAL_IER;
    TcbTask2.u16Stack[ STF_OFFSET_PC ]  = STF_VAL_PC_T2;

    TcbTask1.fpTaskFnPtr = ( TASK_PTR_t )Task1;
    TcbTask1.u32StackPtr = ( ( uint32_t )TcbTask1.u16Stack + STF_LENGTH );

    TcbTask2.fpTaskFnPtr = ( TASK_PTR_t )Task2;
    TcbTask2.u32StackPtr = ( ( uint32_t )TcbTask2.u16Stack + STF_LENGTH );


}

/**
 * @brief
 *
 */
void Task1(void)
{
    for(;;)
    {
        /* Toggle GPIO 33 */
        *((uint32_t *)((uintptr_t)0x7f0e)) = 2U;
        
        int32_t a;
        for( a = 0; a< 0x5fffff; a++ )
        {;}
    }
}

/**
 * @brief
 *
 */
void Task2(void)
{
    for(;;)
    {
        /* Toggle GPIO 33 */
        *((uint32_t *)((uintptr_t)0x7f0e)) = 2U;
        
        int32_t a;
        for( a = 0; a< 0xfffff; a++ )
        {;}
    }
}
