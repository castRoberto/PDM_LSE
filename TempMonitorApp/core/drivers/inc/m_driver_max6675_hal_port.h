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
 * @file m_driver_max6675_hal_port.h
 * @brief SPI communication port for MAX6675 devices
 *
 * This module provides a type that models a physical SPI port of the
 * embedded platform in use, exposing functions and parameters that
 * intervene in SPI communication.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DRIVER_MAX6675_PORT_H__
#define __M_DRIVER_MAX6675_PORT_H__


#include <stdint.h>

#include "stm32f4xx_hal.h"


/**
 * This structure models a platform-specific SPI communication port,
 * containing the information necessary to carry out communication
 * under the SPI protocol.
 */
typedef struct {

	// Pointer to SPI Handler
	SPI_HandleTypeDef* hspi;
	// Pointer to SS pin port
	GPIO_TypeDef* spiSsPinPort;
	// SS pin
	uint32_t spiSsPin;

	/*---------------------- Pointers to functions -------------------*/
	/**
	 * Pointer to a low-level function for reading SPI port
	 */
	HAL_StatusTypeDef (*spiPortRead)
		(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t size, uint32_t timeOut);

	/**
	 * Pointer to a low-level function for selecting and releasing the SS pic
	 */
	void (*spiSsWrite)
		(GPIO_TypeDef* ssPort, uint16_t GPIO_Pin, GPIO_PinState PinState);

} Max6675_Port_t;


#endif /* __M_DRIVER_MAX6675_PORT_H__ */
