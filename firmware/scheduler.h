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

void Scheduler_Init(void);

#endif
