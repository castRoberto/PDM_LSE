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
 * @file m_bsp_stm32f4_setup.h
 * @brief Hardware configuration module
 *
 * This header file is used as an interface to expose functions that
 * configure the application hardware.
 *
 * @author Roberto Castro
 * @date March 21 2024
 *
 */

#ifndef __M_BSP_STM32F4_SETUP_H__
#define __M_BSP_STM32F4_SETUP_H__

/*---------------------- Includes ----------------- */
#include "stm32f4xx_hal.h"
#include "m_ddt_button_data_types.h"
#include "m_bsp_stm32f4_visual_indicators_manager.h"
#include "m_bsp_stm32f4_push_buttons_manager.h"
#include "m_bsp_stm32f4_temperature_manager.h"
#include "m_bsp_stm32f4_nextion_manager.h"


/**
 * Prototype of function by hardware error handler
 */
void BSP_Error_Handler (void);

/**
 * Prototypes of the services provided by the BSP layer configuration
 * module
 */
bool_t BSP_HardwareSetup (void);

#endif /* __M_BSP_STM32F4_SETUP_H__ */
