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
 * @file m_app_main_state_machine.h
 * @brief Finite state machine to manage the application
 *
 * This header file provides an abstraction to handle the internal states
 * of the electric motor temperature monitoring application.
 *
 * @author Roberto Castro
 * @date April 14 2024
 *
 */

#ifndef __M_APP_MAIN_STATE_MACHINE_H__
#define __M_APP_MAIN_STATE_MACHINE_H__


/**
 * Public functions of the main state machine of the system
 */
void APP_MSM_init (void);
void APP_MSM_update (void);

#endif /* __M_APP_MAIN_STATE_MACHINE_H__ */
