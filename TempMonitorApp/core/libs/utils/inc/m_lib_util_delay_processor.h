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
 * @file m_lib_util_delay_processor.h
 * @brief Non-blocking delay manipulation
 *
 * This header file provides an abstraction for manipulating
 * non-blocking delays through function calls.
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */

#ifndef __M_LIB_UTIL_DELAY_H__
#define __M_LIB_UTIL_DELAY_H__


#include "m_ddt_common_types.h"

/**
 * Consts definitions
 */
#define DEFAULT_PERIOD_10MS 10


/**
 * structure to contain information for delay
 * management
 */
typedef struct{

   tick_t startTime;
   tick_t duration;
   bool_t running;

} delay_t;
//


/**
 * Prototypes of public functions of the module
 */
void LIB_DP_delayInit( delay_t * delay, tick_t duration );
bool_t LIB_DP_delayRead( delay_t * delay );
void LIB_DP_delayWrite( delay_t * delay, tick_t duration );

#endif /* __M_LIB_UTIL_DELAY_H__ */
