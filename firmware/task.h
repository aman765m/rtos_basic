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
#include <cpy_tbl.h>

#define TCB_STACK_SIZE          ( 128U )
#define STF_LENGTH              ( 0x0FUL )

#define STF_OFFSET_ST0          ( 0U )
#define STF_VAL_ST0             ( 0x008CU )
#define STF_OFFSET_ST1          ( 8U )
#define STF_VAL_ST1             ( 0x8A08U )
#define STF_OFFSET_DP           ( 9U )
#define STF_VAL_DP              ( 0x02ABU )
#define STF_OFFSET_IER          ( 10U )
#define STF_VAL_IER             ( 0x0001U )
#define STF_OFFSET_PC           ( 12U )
#define STF_VAL_PC_T1           ( ( uint32_t )Task1 )
#define STF_VAL_PC_T2           ( ( uint32_t )Task2 )

#define TCB_SP_OFFSET           ( TCB_STACK_SIZE )



typedef void ( * TASK_PTR_t )( void );

typedef struct
{
    uint16_t u16Stack[ TCB_STACK_SIZE ];
    uint32_t u32StackPtr;
    TASK_PTR_t fpTaskFnPtr;
} TCB_t;

extern TCB_t TcbTask1;
extern TCB_t TcbTask2;

void Task_Init( void );

#endif
