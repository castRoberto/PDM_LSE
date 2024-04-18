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
 * @file m_bsp_stm32f4.c
 * @brief Inclusion header file
 *
 * This header file is used to include all submodules of the bsp layer.
 *
 * @author Roberto Castro
 * @date March 21 2024
 *
 */


#include "m_bsp_stm32f4.h"


/**
 * @brief Provides a tick value in millisecond.
 * @note This function is declared as _weak to be overwritten in case of other
 * 	     implementations in user file
 * @retval tick value
 */
uint32_t BSP_GetCurrentTime (void) {

	return HAL_GetTick ();

}
