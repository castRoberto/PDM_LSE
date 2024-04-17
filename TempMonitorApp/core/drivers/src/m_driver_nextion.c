/*
 * m_driver_nextion.c
 *
 *  Created on: Apr 10, 2024
 *      Author: rober
 */


#include "m_driver_nextion.h"

/* Type Redefinition */
typedef const char * str_cast;


static char buff[SEND_BUFF_LEN] = { NULL_CHAR };


static const char WAVE_FORM_VALUE_COMMAND_FORMAT[] = "add %u,%u,%u%s";
static const char TEXT_VALUE_COMMAND_FORMAT[] = "%s.txt=%s%s";
static const char TEXT_COLOR_COMMAND_FORMAT[] = "%s.bco=%u%s";
static const char NUMBER_VALUE_COMMAND_FORMAT[] = "%s.val=%u%s";
uint8_t END_OF_MSG[] = {END_MSG_CHAR, END_MSG_CHAR, END_MSG_CHAR, NULL_CHAR};


static void sendCommand (NEXTION_Port_t* port) {

	uint16_t len = (uint16_t) strlen ((str_cast) buff);

	/* Send command */
	port->uartPortWrite
		(port->uartDev,
		 (uint8_t*)buff,
		 len,
		 NEXTION_UART_TIMEOUT);

}


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

