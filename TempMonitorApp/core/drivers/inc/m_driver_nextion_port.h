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
 * @file m_driver_nextion_port.h
 * @brief UART communication port for nextion displays
 *
 * This module provides a type that models a physical UART port of
 * the embedded platform in use, exposing functions and parameters
 * involved in UART communication.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DRIVER_NEXTION_PORT_H__
#define __M_DRIVER_NEXTION_PORT_H__


#include <stdint.h>

#include "stm32f4xx_hal.h"



/**
 * This structure models a platform-specific UART communication port,
 * which contains the information necessary to perform communication
 * under the UART protocol.
 */
typedef struct {

	// Pointer to UART Handler
	UART_HandleTypeDef* uartDev;


	/*------- Pointers to functions -------*/
	/**
	 * Pointer to a low-level function for reading UART port
	 */
	HAL_StatusTypeDef (*uartPortWrite)
		(UART_HandleTypeDef *huart, const uint8_t* pData, uint16_t size, uint32_t timeOut);

} NEXTION_Port_t;


#endif /* __M_DRIVER_NEXTION_PORT_H__ */
