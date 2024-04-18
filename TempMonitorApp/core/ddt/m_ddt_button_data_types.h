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
 * @file m_ddt_button_data_types.h
 * @brief Defining types for buttons
 *
 * This header file provides the data types useful for
 * working with a button.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DDT_BUTTON_DATA_TYPES_H__
#define __M_DDT_BUTTON_DATA_TYPES_H__

#include "m_ddt_common_types.h"


/**
 * Type to model the possible states of a button
 */
typedef enum {

	E_BUTTON_RESET = 0,
	E_BUTTON_SET = 1,
	E_UNKNOWN_PB_STATE = 2,

} ButtonState_t;

#endif /* __M_DDT_BUTTON_DATA_TYPES_H__ */
