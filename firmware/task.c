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


volatile uint16_t gu16TcbNewSp;


TCB_t * pxTaskControlBlock[ MAX_TASKS ];
int16_t s16nTasksRegistered = -1;

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

    int16_t s16TaskIdx;

    for( s16TaskIdx = 0; s16TaskIdx <= s16nTasksRegistered; s16TaskIdx++ )
    {
        memset( ( void * )&( pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ 0 ]), 0, ( size_t )TCB_STACK_SIZE );

        pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ STF_OFFSET_ST0 ]    = STF_VAL_ST0;
        pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ STF_OFFSET_ST1 ]    = STF_VAL_ST1;
        pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ STF_OFFSET_DP ]     = STF_VAL_DP;
        pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ STF_OFFSET_IER ]    = STF_VAL_IER;
        pxTaskControlBlock[ s16TaskIdx ]->u16Stack[ STF_OFFSET_PC ]     = ( uint32_t )pxTaskControlBlock[ s16TaskIdx ]->fpTaskFnPtr;
        pxTaskControlBlock[ s16TaskIdx ]->u32StackPtr                   = ( uint32_t )pxTaskControlBlock[ s16TaskIdx ]->u16Stack + STF_LENGTH;
    }
}

/**
 * @brief 
 * 
 * @param pxTcb 
 * @param fpTaskPtr 
 * @param u16Priority 
 * @return true 
 * @return false 
 */
bool Task_RegisterTcb( TCB_t * pxTcb, TASK_PTR_t fpTaskPtr, uint16_t u16Priority, uint32_t u32Period )
{
    bool bStatus;

    /** TODO: Add NULL check for recieved pointers */

    if( ( int16_t )MAX_TASKS > s16nTasksRegistered )
    {
        s16nTasksRegistered++;

        pxTaskControlBlock[ s16nTasksRegistered ] = pxTcb;

        pxTcb->fpTaskFnPtr = fpTaskPtr;
        pxTcb->u16Priority = u16Priority;
        pxTcb->u32Period = u32Period;
        pxTcb->u16Id = s16nTasksRegistered;

        bStatus = true;
    }
    else
    {
        bStatus = false;
    }

    return bStatus;
}
