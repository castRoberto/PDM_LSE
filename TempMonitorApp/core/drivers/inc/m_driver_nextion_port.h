/*
 * m_driver_nextion_port.h
 *
 *  Created on: Apr 11, 2024
 *      Author: rober
 */

#ifndef __M_DRIVER_NEXTION_PORT_H__
#define __M_DRIVER_NEXTION_PORT_H__


#include <stdint.h>

#include "stm32f4xx_hal.h"


typedef struct {

	UART_HandleTypeDef* uartDev;


	/*------- Pointers to functions -------*/
	HAL_StatusTypeDef (*uartPortWrite)
		(UART_HandleTypeDef *huart, const uint8_t* pData, uint16_t size, uint32_t timeOut);

} NEXTION_Port_t;


#endif /* __M_DRIVER_NEXTION_PORT_H__ */
