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
 * @file API_uart.h
 * @brief Module for managing communications via UART
 *
 * This header file provides an abstraction for handling serial
 * communications via the UART electrical protocol.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */

#ifndef __API_UART_H__
#define __API_UART_H__

#include <string.h>
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "API_DataTypes.h"


/**
 * Uart constants definitions
 */
#define UART_INSTANCE USART3
#define UART_BAUD_RATE 9600
#define UART_WORD_LEN UART_WORDLENGTH_8B
#define UART_STOP_BITS UART_STOPBITS_1
#define UART_PARITY UART_PARITY_NONE

#define MAX_WAIT_UART_TX 500


/**
 * Public Functions of module
 */
bool_t API_uartInit (void);
void API_uartSendString (uint8_t* pstring);
void API_uartSendStringSize (uint8_t* pstring, uint16_t size);
void API_uartReceiveStringSize (uint8_t* pstring, uint16_t size);


#endif /* __API_UART_H__ */
