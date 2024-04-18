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
 * @file m_driver_nextion.c
 * @brief Driver to control nextion display
 *
 * This implementation file provides the main functions to update
 * an x/y plot, display information in text, button and numeric components
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */


#include "m_driver_nextion.h"

/**
 * Definition of driver constants
 */
#define SEND_BUFF_LEN 50
#define END_MSG_CHAR 0XFF

#define NEXTION_UART_TIMEOUT 100

/* Type Redefinition */
typedef const char * str_cast;


/**
 * Buffer that will contain all the commands to send to the nextion
 */
static char buff[SEND_BUFF_LEN] = { NULL_CHAR };


/**
 * Format of the commands supported by the nextion display
 */
static const char WAVE_FORM_VALUE_COMMAND_FORMAT[] = "add %u,%u,%u%s";
static const char TEXT_VALUE_COMMAND_FORMAT[] = "%s.txt=%s%s";
static const char TEXT_COLOR_COMMAND_FORMAT[] = "%s.bco=%u%s";
static const char NUMBER_VALUE_COMMAND_FORMAT[] = "%s.val=%u%s";
/**
 * All nextion commands must end with three 0XFFs, this string contains them
 */
uint8_t END_OF_MSG[] = {END_MSG_CHAR, END_MSG_CHAR, END_MSG_CHAR, NULL_CHAR};


/**
 * @brief Send the commands to the nextion by serial
 *
 * This function sends update commands to the nextion
 * display via uart port.
 *
 *
 * @param port: Port with uart_dev and necessary functions
 *
 * @return None
 */
static void sendCommand (NEXTION_Port_t* port) {

	uint16_t len = (uint16_t) strlen ((str_cast) buff);

	/* Send command */
	port->uartPortWrite
		(port->uartDev,
		 (uint8_t*)buff,
		 len,
		 NEXTION_UART_TIMEOUT);

}


/**
 * @brief Update a wave_form on the display
 *
 * This function constructs and sends to the display the
 * update value of the X vs Y curve.
 *
 *
 * @param port: Port with uart_dev and necessary functions
 * @param nextionObj: Object visible in the nextion to which
 * 					  the update will be made
 *
 * @return None
 */
void NEXTION_UpdateWaveFormValue
	(NEXTION_Port_t* port, NextionObject_t* nextionObj) {

	if (port != NULL && nextionObj != NULL) {

		if (nextionObj->type == E_WAVE_FORM) {

			memset (buff, NULL_CHAR, SEND_BUFF_LEN);

			sprintf
				(buff,
				 WAVE_FORM_VALUE_COMMAND_FORMAT,
				 nextionObj->id,
				 nextionObj->channel,
				 (uint8_t)nextionObj->val,
				 END_OF_MSG);

			sendCommand (port);
		}

	}

}


/**
 * @brief Update a Text object on the display
 *
 * This function constructs and sends to the display the
 * update value of a Text component.
 *
 *
 * @param port: Port with uart_dev and necessary functions
 * @param nextionObj: Object visible in the nextion to which
 * 					  the update will be made
 *
 * @return None
 */
void NEXTION_UpdateTextValue (NEXTION_Port_t* port, NextionObject_t* nextionObj) {

	if (port != NULL && nextionObj != NULL) {

		if (nextionObj->type == E_TEXT) {

			memset (buff, NULL_CHAR, SEND_BUFF_LEN);

			sprintf
				(buff,
				 TEXT_VALUE_COMMAND_FORMAT,
				 nextionObj->objname,
				 nextionObj->txt,
				 END_OF_MSG);

			sendCommand (port);

		}

	}
}


/**
 * @brief Update the color of a Text object on the display
 *
 * This function constructs and sends the command to the display
 * to update the color of a text component.
 *
 *
 * @param port: Port with uart_dev and necessary functions
 * @param nextionObj: Object visible in the nextion to which
 * 					  the update will be made
 *
 * @return None
 */
void NEXTION_UpdateTextColor (NEXTION_Port_t* port, NextionObject_t* nextionObj) {

	if (port != NULL && nextionObj != NULL) {

		if (nextionObj->type == E_TEXT) {

			memset (buff, NULL_CHAR, SEND_BUFF_LEN);

			sprintf
				(buff,
				 TEXT_COLOR_COMMAND_FORMAT,
				 nextionObj->objname,
				 nextionObj->bco,
				 END_OF_MSG);

			sendCommand (port);

		}

	}

}


/**
 * @brief Update the value of a Numeric object on the display
 *
 * This function constructs and sends the command to the display
 * to update the Value of a Numeric component.
 *
 *
 * @param port: Port with uart_dev and necessary functions
 * @param nextionObj: Object visible in the nextion to which
 * 					  the update will be made
 *
 * @return None
 */
void NEXTION_UpdateNumberValue (NEXTION_Port_t* port, NextionObject_t* nextionObj) {

	if (port != NULL && nextionObj != NULL) {

		if (nextionObj->type == E_NUMBER) {

			memset (buff, NULL_CHAR, SEND_BUFF_LEN);

			sprintf
				(buff,
				 NUMBER_VALUE_COMMAND_FORMAT,
				 nextionObj->objname,
				 nextionObj->val,
				 END_OF_MSG);

			sendCommand (port);

		}

	}

}

