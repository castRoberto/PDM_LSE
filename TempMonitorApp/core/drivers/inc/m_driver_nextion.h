/*
 * m_driver_nextion.h
 *
 *  Created on: Apr 10, 2024
 *      Author: rober
 */

#ifndef __M_DRIVER_NEXTION_H__
#define __M_DRIVER_NEXTION_H__


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "m_driver_nextion_port.h"

#define OBJNAME_LEN 28
#define OBJ_TEXT_VALUE_LEN 15

#define SEND_BUFF_LEN 50
#define END_MSG_CHAR 0XFF

#define NULL_CHAR '\0'


#define NEXTION_UART_TIMEOUT 100


typedef enum {

	E_WAVE_FORM = 0,
	E_TEXT = 1,
	E_BUTTON = 2,
	E_NUMBER = 3,

} TypeObject_e;

typedef struct {

	/*---Identification parameters---*/
	uint8_t page;
	uint8_t objname[OBJNAME_LEN];
	uint8_t id;

	/*--- Dynamic parameters ---*/
	uint16_t bco;
	uint8_t channel;
	uint8_t txt[OBJ_TEXT_VALUE_LEN];
	uint16_t val;

	/*--- Internal parameters ---*/
	TypeObject_e type;

} NextionObject_t;



void NEXTION_UpdateWaveFormValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateTextValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateTextColor (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateNumberValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);

#endif /* __M_DRIVER_NEXTION_H__ */
