/******************************************************************************
 * Copyright (C) 2024 by Roberto Castro
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Roberto Castro are not liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file TimeManager.h
 * @brief Non-blocking delay manipulation
 *
 * This header file provides an abstraction for manipulating
 * non-blocking delays through function calls.
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */

#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

typedef uint32_t tick_t;
typedef bool bool_t;


typedef struct{

   tick_t startTime;
   tick_t duration;
   bool_t running;

} delay_t;

void TM_delayInit( delay_t * delay, tick_t duration );

bool_t TM_delayRead( delay_t * delay );

void TM_delayWrite( delay_t * delay, tick_t duration );


#endif /* __TIME_MANAGER_H__ */
