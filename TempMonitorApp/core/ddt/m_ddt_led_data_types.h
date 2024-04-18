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
 * @file m_ddt_led_data_types.h
 * @brief Defining types for leds
 *
 * This header file provides the data types useful for
 * working with a leds.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */


#ifndef __M_DDT_LED_DATA_TYPES_H__
#define __M_DDT_LED_DATA_TYPES_H__


#include "m_ddt_common_types.h"


/**
 * Type to model the possible states of a led
 */
typedef enum {

	E_LED_RESET = 0,
	E_LED_SET = 1,
	E_UNKNOWN_VI_STATE = 2,

} LedState_t;

#endif /* __M_DDT_LED_DATA_TYPES_H__ */
