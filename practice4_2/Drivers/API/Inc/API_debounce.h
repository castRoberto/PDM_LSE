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
 * @file API_debounce.h
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

#include "API_DataTypes.h"
#include "API_delay.h"


/*
 * Rebound stabilization time
 */
#define DEBOUNCE_STABILIZATION_TIME_40MS 40


/**
 * Prototype of public functions of the package
 */
bool_t API_debounceReadKey (void);
void API_debounceFsmInit (void);
void API_debounceFsmUpdate (void);


#endif /* __API_DEBOUNCE_H__ */
