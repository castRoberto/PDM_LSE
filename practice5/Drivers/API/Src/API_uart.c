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
 * @file API_uart.c
 * @brief Module for managing communications via UART
 *
 * This implementation file provides an abstraction for handling serial
 * communications via the UART electrical protocol.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */


#include "API_uart.h"

/* UART handler declaration */
static UART_HandleTypeDef huart3;

/* Type Redefinition */
typedef const char * str_cast;


/**
 * Constants for handling character strings
 */
#define LEN_TMP_MSG 10
#define LEN_INIT_MSG 120
#define NUMERIC_BASE 10


/**
 * Auxiliary fields of the initialization message
 */
static const uint8_t INIT_HEADER_MSG[] 		= "[API_UART.INIT]: ";
static const uint8_t INIT_INSTANCE_MSG[] 	= "instance{";
static const uint8_t INIT_BAUD_MSG[] 		= "}, baudRate{";
static const uint8_t INIT_WORD_LEN_MSG[] 	= "}, wordLen{";
static const uint8_t INIT_STOP_BITS_MSG[] 	= "}, stopBits{";
static const uint8_t INIT_PARITY_MSG[] 		= "}, parity{";
static const uint8_t INIT_END_MSG[] 		= "}\r\n";

static const uint8_t CLEAN_CHARACTER 		= '\0';


/**
 * @brief Convert parity to string
 *
 * This function is used to convert the parity attribute of
 * the UART instance to a printable string.
 *
 * @param buff: Temporary conversion buffer
 *
 * @return None
 */
static void getParity (uint8_t* buff) {

	if (buff != NULL) {

		memset(buff, CLEAN_CHARACTER, LEN_TMP_MSG);

		switch (huart3.Init.Parity) {

			case UART_PARITY_NONE: {

				strcat ((char*) buff, (str_cast)"None");
				break;

			}

			case UART_PARITY_EVEN: {

				strcat ((char*) buff, (str_cast)"Even");
				break;

			}

			case UART_PARITY_ODD: {

				strcat ((char*) buff, (str_cast)"Odd");
				break;

			}

			default: {

				strcat ((char*) buff, (str_cast)"unknown");
				break;

			}

		}

	}

}


/**
 * @brief Convert StopBits to string
 *
 * This function is used to convert the StopBits attribute of
 * the UART instance to a printable string.
 *
 * @param buff: Temporary conversion buffer
 *
 * @return None
 */
static void getStopBits (uint8_t* buff) {

	if (buff != NULL) {

		memset(buff, CLEAN_CHARACTER, LEN_TMP_MSG);

		switch (huart3.Init.StopBits) {

			case UART_STOPBITS_1: {

				strcat ((char*) buff, (str_cast)"1 bits");
				break;

			}

			case UART_STOPBITS_2: {

				strcat ((char*) buff, (str_cast)"2 bits");
				break;

			}

			default: {

				strcat ((char*) buff, (str_cast)"unknown");
				break;

			}

		}

	}

}


/**
 * @brief Convert WordLen to string
 *
 * This function is used to convert the WordLen attribute of
 * the UART instance to a printable string.
 *
 * @param buff: Temporary conversion buffer
 *
 * @return None
 */
static void getWordLen (uint8_t* buff) {

	if (buff != NULL) {

		memset(buff, CLEAN_CHARACTER, LEN_TMP_MSG);

		switch (huart3.Init.WordLength) {

			case UART_WORDLENGTH_8B: {

				strcat ((char*) buff, (str_cast)"8 bits");
				break;

			}

			case UART_WORDLENGTH_9B: {

				strcat ((char*) buff, (str_cast)"9 bits");
				break;

			}

			default: {

				strcat ((char*) buff, (str_cast)"unknown");
				break;

			}

		}

	}

}


/**
 * @brief Convert Instance to string
 *
 * This function is used to convert the Instance attribute of
 * the UART instance to a printable string.
 *
 * @param buff: Temporary conversion buffer
 *
 * @return None
 */
static void getUartInstance (uint8_t* buff) {

	if (buff != NULL) {

		memset(buff, CLEAN_CHARACTER, LEN_TMP_MSG);

		if 		(huart3.Instance == USART1)
			strcat ((char*) buff, (str_cast)"UART1");

		else if (huart3.Instance == USART2)
			strcat ((char*) buff, (str_cast)"UART2");

		else if (huart3.Instance == USART3)
			strcat ((char*) buff, (str_cast)"UART3");

		else
			strcat ((char*) buff, (str_cast)"_unknown");
	}

}


/**
 * @brief Convert UART instance attributes to string
 *
 * Function that creates a printable character string from the
 * attributes of a UART instance
 *
 * @param buff: Conversion buffer
 *
 * @return None
 */
static void createInitMessage (uint8_t* buffer) {

	if (buffer != NULL) {

		uint8_t tmpMsg [LEN_TMP_MSG] = { CLEAN_CHARACTER };

		memset(buffer, CLEAN_CHARACTER, LEN_INIT_MSG);

		/* Header init msg */
		strcat ((char*)buffer, (str_cast)INIT_HEADER_MSG);

		/* Instance uart data */
		strcat ((char*)buffer, (str_cast)INIT_INSTANCE_MSG);
		getUartInstance (tmpMsg);
		strcat ((char*)buffer, (str_cast)tmpMsg);

		/* BaudRate uart data */
		strcat ((char*)buffer, (str_cast)INIT_BAUD_MSG);
		itoa (huart3.Init.BaudRate, (char*)tmpMsg, NUMERIC_BASE);
		strcat ((char*)buffer, (str_cast)tmpMsg);

		/* WordLen uart data */
		strcat ((char*)buffer, (str_cast)INIT_WORD_LEN_MSG);
		getWordLen(tmpMsg);
		strcat ((char*)buffer, (str_cast)tmpMsg);

		/* StopBits uart data */
		strcat ((char*)buffer, (str_cast)INIT_STOP_BITS_MSG);
		getStopBits(tmpMsg);
		strcat ((char*)buffer, (str_cast)tmpMsg);

		/* Parity uart data */
		strcat ((char*)buffer, (str_cast)INIT_PARITY_MSG);
		getParity(tmpMsg);
		strcat ((char*)buffer, (str_cast)tmpMsg);

		/* End init uart msg */
		strcat ((char*)buffer, (str_cast)INIT_END_MSG);

	}

}


/**
 * @brief Initializes an instance of the UART module
 *
 * Function that initializes a UART module and prints
 * its configuration parameters via serial.
 *
 * @param None
 *
 * @return None
 */
bool_t API_uartInit (void) {

	uint8_t buffer[LEN_INIT_MSG] = { CLEAN_CHARACTER };
	bool_t configurationSuccessful = false;

	/* Main config */
	huart3.Instance = UART_INSTANCE;
	huart3.Init.BaudRate = UART_BAUD_RATE;
	huart3.Init.WordLength = UART_WORD_LEN;
	huart3.Init.StopBits = UART_STOP_BITS;
	huart3.Init.Parity = UART_PARITY;

	/* Config no interesting */
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;

	configurationSuccessful = (HAL_UART_Init (&huart3) == HAL_OK);

	/*
	 * This message is only sent if the configuration
	 * was successful
	 */
	if (configurationSuccessful) {

		createInitMessage(buffer);

		API_uartSendString(buffer);

	}

	return configurationSuccessful;
}


/**
 * @brief Send a character string by serial
 *
 * Function that sends a character string via UART serial
 * and calculates its length.
 *
 * @param pstring: String to print
 *
 * @return None
 */
void API_uartSendString (uint8_t* pstring) {

	if (pstring != NULL) {

		uint16_t len = (uint16_t) strlen ((str_cast) pstring);

		HAL_UART_Transmit (&huart3, pstring, len, MAX_WAIT_UART_TX);

	}

}


/**
 * @brief Send a character string by serial
 *
 * Function that sends a character string via UART serial.
 *
 * @param pstring: String to print
 * @param size: Character string length
 *
 * @return None
 */
void API_uartSendStringSize (uint8_t* pstring, uint16_t size) {

	if (pstring != NULL) {

		HAL_UART_Transmit (&huart3, pstring, size, MAX_WAIT_UART_TX);

	}

}


/**
 * @brief Receives a string of characters by serial
 *
 * Function that receives via UART serial a character
 * string of size size
 *
 * @param pstring: Pointer to the space that stores the
 * 					received data
 * @param size: Character string length
 *
 * @return None
 */
void API_uartReceiveStringSize (uint8_t* pstring, uint16_t size) {

	if (pstring != NULL) {

		HAL_UART_Receive (&huart3, (uint8_t*)pstring, size, MAX_WAIT_UART_TX);

	}

}
