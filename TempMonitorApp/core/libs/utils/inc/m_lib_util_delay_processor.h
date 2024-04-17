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
 * @file m_lib_util_delay.h
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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "stm32f4xx_hal.h"
#include "m_bsp_stm32_hardware_config.h"
#include "m_bsp_stm32f4.h"
#include "m_ddt_common_types.h"

// Defining data types
typedef uint32_t tick_t;

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
 * @brief Time initializer
 *
 * Function that initializes a time structure with
 * default values
 *
 * @param delay: Time structure
 * @param duration: Default wait
 *
 * @return void.
 */
void LIB_DP_delayInit( delay_t * delay, tick_t duration );


/**
 * @brief Check elapsed time
 *
 * Function that checks if for a given time structure,
 * the timeout has been met
 *
 * @param delay: Time structure
 *
 * @return timeOut.
 */
bool_t LIB_DP_delayRead( delay_t * delay );


/**
 * @brief Delay updater
 *
 * This function updates the timeout duration
 *
 * @param delay: Time structure
 * @param duration: New waiting time
 *
 * @return void.
 */
void LIB_DP_delayWrite( delay_t * delay, tick_t duration );

#endif /* __M_LIB_UTIL_DELAY_H__ */
