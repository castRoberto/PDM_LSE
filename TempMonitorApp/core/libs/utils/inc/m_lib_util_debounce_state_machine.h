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
 * @file m_lib_util_debounce_state_machine.h
 * @brief Finite state machine for bounce management
 *
 * This header file provides an abstraction for handling debounces
 * in physical pushbuttons on the board.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __API_DEBOUNCE_H__
#define __API_DEBOUNCE_H__

#include "m_ddt_common_types.h"
#include "m_lib_util_delay_processor.h"


/**
 * States for the debounce state machine
 */
typedef enum {

	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING

} DebounceState_t;


/**
 * Type that allows generalizing anti-bounce for any pin
 */
typedef struct {

	bool_t keyPressed;
	DebounceState_t currentState;
	delay_t debounceDelay;
	Button_e pin;

} DebouncePinData_t;


/**
 * Prototype of public functions of the package
 */
bool_t LIB_DSM_debounceReadKey (DebouncePinData_t* debounce);
void LIB_DSM_debounceFsmInit (DebouncePinData_t* debounce);
void LIB_DSM_debounceFsmUpdate (DebouncePinData_t* debounce);


#endif /* __API_DEBOUNCE_H__ */
