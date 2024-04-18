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
 * @file m_driver_nextion.h
 * @brief Driver to control nextion display
 *
 * This implementation file provides the main functions to update
 * an x/y plot, display information in text, button and numeric components
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DRIVER_NEXTION_H__
#define __M_DRIVER_NEXTION_H__


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "m_driver_nextion_port.h"


/**
 * Definition of the driver's public constants
 */
#define OBJNAME_LEN 28
#define OBJ_TEXT_VALUE_LEN 15

#define NULL_CHAR '\0'


/**
 * Definition of all types of objects that the
 * nextion can have.
 *
 * As the driver adds more functionality, more objects
 * must be added.
 */
typedef enum {

	E_WAVE_FORM = 0,
	E_TEXT = 1,
	E_BUTTON = 2,
	E_NUMBER = 3,

} TypeObject_e;


/**
 * This structure models a nextion object, with the most
 * relevant properties, not all of them contain the same
 * attributes, so a common one was created and if it does
 * not use that value, it is set to null
 */
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



/**
 * Prototypes of the public functions of the driver to manage the update of the nextion components
 */
void NEXTION_UpdateWaveFormValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateTextValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateTextColor (NEXTION_Port_t* port, NextionObject_t* nextionObj);
void NEXTION_UpdateNumberValue (NEXTION_Port_t* port, NextionObject_t* nextionObj);

#endif /* __M_DRIVER_NEXTION_H__ */
