/**
 * @file task.h
 * @author Aman Singh (aman756m@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_TASKS               ( 10U )
#define TCB_STACK_SIZE          ( 128U )
#define STF_LENGTH              ( 0x0FUL + 0x18UL ) /* Take care of stack alignment */

#define STF_OFFSET_ST0          ( 0U )
#define STF_VAL_ST0             ( 0x008CU )
#define STF_OFFSET_ST1          ( 8U )
#define STF_VAL_ST1             ( 0x8A08U )
#define STF_OFFSET_DP           ( 9U )
#define STF_VAL_DP              ( 0x02ABU )
#define STF_OFFSET_IER          ( 10U )
#define STF_VAL_IER             ( 0x0001U )
#define STF_OFFSET_PC           ( 12U )

typedef void ( * TASK_PTR_t )( void );

typedef struct
{
    uint16_t u16Stack[ TCB_STACK_SIZE ];
    uint32_t u32StackPtr;
    TASK_PTR_t fpTaskFnPtr;
    uint16_t u16Priority;
    uint16_t u16Id;
    uint32_t u32Period;
} TCB_t;

extern TCB_t * pxTaskControlBlock[ MAX_TASKS ];
extern int16_t s16nTasksRegistered;

void Task_Init( void );
bool Task_RegisterTcb( TCB_t * pxTcb, TASK_PTR_t fpTaskPtr, uint16_t u16Priority, uint32_t u32Period );

#endif
