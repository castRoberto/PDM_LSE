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
 * @file m_bsp_stm32f4_buttons.h
 *
 * @brief Push button Manager Module
 *
 * This module acts as a facade for higher level layers that require
 * controlling hardware buttons, therefore exposing functions that
 * contain a business logic context as well as a hardware generalization.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */

#ifndef __M_BSP_STM32F4_BUTTONS_H__
#define __M_BSP_STM32F4_BUTTONS_H__


/* IncludesS */
#include "m_bsp_stm32_system_config.h"
#include "m_ddt_button_data_types.h"



/**
 * This enumeration defines a set of references
 * to instances of system buttons.
 */
typedef enum {

	E_BUTTON1 = 0,

	E_START_STOP_BUTTON = E_BUTTON1,

	E_FIRST_BUTTON = E_BUTTON1,
	E_LAST_BUTTON = NUM_BUTTONS

} Button_e;



/**
 * Prototypes of public functions for system button
 * control. Related to business logic.
 */
void BSP_PBM_InitButtons (void);
void BSP_PBM_DeInitButtons (void);
ButtonState_t BSP_PBM_ReadStartStopButton (void);

ButtonState_t BSP_PBM_ReadButton (Button_e button);

#endif /* __M_BSP_STM32F4_BUTTONS_H__ */
