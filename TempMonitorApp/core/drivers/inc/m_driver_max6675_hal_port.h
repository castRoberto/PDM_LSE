/*
 * m_driver_max6675_hal_port.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_DRIVER_MAX6675_PORT_H__
#define __M_DRIVER_MAX6675_PORT_H__


#include <stdint.h>

#include "stm32f4xx_hal.h"


typedef struct {

	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* spiSsPinPort;
	uint32_t spiSsPin;

	/*---------------------- Pointers to functions -------------------*/
	HAL_StatusTypeDef (*spiPortRead)
		(SPI_HandleTypeDef* hspi, uint8_t* pData, uint16_t size, uint32_t timeOut);

	void (*spiSsWrite)
		(GPIO_TypeDef* ssPort, uint16_t GPIO_Pin, GPIO_PinState PinState);

} Max6675_Port_t;


#endif /* __M_DRIVER_MAX6675_PORT_H__ */
