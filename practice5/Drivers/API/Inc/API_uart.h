/*
 * API_uart.h
 *
 *  Created on: Mar 31, 2024
 *      Author: operador
 */

#ifndef __API_UART_H__
#define __API_UART_H__

#include <string.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "API_DataTypes.h"


#define MAX_WAIT_UART_TX 500

/**
 * Uart constants definitions
 */
#define UART_INSTANCE USART3
#define UART_BAUD_RATE 9600
#define UART_WORD_LEN UART_WORDLENGTH_8B
#define UART_STOP_BITS UART_STOPBITS_1
#define UART_PARITY UART_PARITY_NONE


/**
 * Public Functions of module
 */
bool_t API_uartInit (void);
void API_uartSendString (uint8_t* pstring);
void API_uartSendStringSize (uint8_t* pstring, uint16_t size);
void API_uartReceiveStringSize (uint8_t* pstring, uint16_t size);


#endif /* __API_UART_H__ */
