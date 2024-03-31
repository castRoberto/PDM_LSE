/*
 * API_uart.c
 *
 *  Created on: Mar 31, 2024
 *      Author: operador
 */


#include "API_uart.h"

/* UART handler declaration */
static UART_HandleTypeDef huart3;

typedef const char * str_cast;


/**
 *
 */
#define LEN_TMP_MSG 10
#define LEN_INIT_MSG 120
#define NUMERIC_BASE 10


/**
 * Auxiliary fields of the initialization message
 */
static const uint8_t INIT_HEADER_MSG[] 		= "[API_UART.INIT]: ";
static const uint8_t INIT_INSTANCE_MSG[] 	= "instance{UART";
static const uint8_t INIT_BAUD_MSG[] 		= "}, baudRate{";
static const uint8_t INIT_WORD_LEN_MSG[] 	= "}, wordLen{";
static const uint8_t INIT_STOP_BITS_MSG[] 	= "}, stopBits{";
static const uint8_t INIT_PARITY_MSG[] 		= "}, parity{";
static const uint8_t INIT_END_MSG[] 		= "}\r\n";

static const uint8_t CLEAN_CHARACTER 		= '\0';


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


static void getUartInstance (uint8_t* buff) {

	if (buff != NULL) {

		memset(buff, CLEAN_CHARACTER, LEN_TMP_MSG);

		if 		(huart3.Instance == USART1) buff[0] = '1';
		else if (huart3.Instance == USART2) buff[0] = '2';
		else if (huart3.Instance == USART3) buff[0] = '3';
		else 								strcat (
												(char*)buff,
												(str_cast)"_unknown"
											);
	}

}


static void createInitMessage (uint8_t* buffer) {

	uint8_t tmpMsg [LEN_TMP_MSG] = { CLEAN_CHARACTER };

	memset(buffer, CLEAN_CHARACTER, LEN_INIT_MSG);

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


void API_uartSendString (uint8_t* pstring) {

	if (pstring != NULL) {

		uint16_t len = (uint16_t) strlen ((str_cast) pstring);

		HAL_UART_Transmit (&huart3, pstring, len, MAX_WAIT_UART_TX);

	}

}


void API_uartSendStringSize (uint8_t* pstring, uint16_t size) {

	if (pstring != NULL) {

		HAL_UART_Transmit (&huart3, pstring, size, MAX_WAIT_UART_TX);

	}

}


void API_uartReceiveStringSize (uint8_t* pstring, uint16_t size) {

	if (pstring != NULL) {

		HAL_UART_Receive (&huart3, (uint8_t*)pstring, size, MAX_WAIT_UART_TX);

	}

}
