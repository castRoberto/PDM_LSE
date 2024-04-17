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
 * @date April 14 2024
 *
 */

#ifndef __M_APP_MAIN_STATE_MACHINE_H__
#define __M_APP_MAIN_STATE_MACHINE_H__



void APP_MSM_init (void);
void APP_MSM_update (void);

#endif /* __M_APP_MAIN_STATE_MACHINE_H__ */
