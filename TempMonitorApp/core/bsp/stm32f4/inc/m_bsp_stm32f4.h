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
 * @file m_bsp_stm32f4.h
 * @brief Inclusion header file
 *
 * This header file is used to include all submodules of the bsp layer.
 *
 * @author Roberto Castro
 * @date March 21 2024
 *
 */

#ifndef __M_BSP_STM32F4_H__
#define __M_BSP_STM32F4_H__

#include <stdint.h>

#include "m_bsp_stm32f4_setup.h"

/**
 * Prototypes of common functions of a bsp
 */
uint32_t BSP_GetCurrentTime (void);

#endif /* __M_BSP_STM32F4_H__ */
