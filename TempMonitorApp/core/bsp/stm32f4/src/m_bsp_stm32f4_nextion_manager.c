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
 * @file m_bsp_stm32f4_nextion_manager.c
 *
 * @brief Nextion Manager Module
 *
 * This module acts as a facade for the higher level layers that require
 * controlling the display of information on a hardware display, therefore
 * exposing functions that contain a business logic context as well as a
 * generalization of the hardware.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */


#include "m_bsp_stm32f4_nextion_manager.h"

#include "stm32f4xx_hal.h"

#include "m_bsp_stm32_system_config.h"

#include "m_driver_nextion.h"
#include "m_driver_nextion_port.h"



/**
 * Constants related to nextion
 * display operation.
 */
#define MAIN_PAGE 0

#define TEMP_GRAPH_ID 4
#define TEMP_GRAPH_CH 0
#define GRAPH_MAX_TEMP_VALUE 255

#define NULL_VALUE 0


/**
 * Constants denoting the color of nextion visuals, their
 * identification text, and their display value.
 */
static uint8_t NEXTION_SENSOR_CONNECT_OBJNAME[] = "state";

static uint8_t NEXTION_TEMP_ALARM_OBJNAME[] = "tempAlarm";

static uint8_t NEXTION_NUMBER_CELCIUS_OBJNAME[] = "celcius";

static uint8_t NEXTION_NUMBER_KELVIN_OBJNAME[] = "kelvin";

static uint8_t NEXTION_NUMBER_FAREN_OBJNAME[] = "faren";


// Connected Disconnected Sensor Object Attributes
static uint8_t NEXTION_SENSOR_CONNECT_MSG[] = "\"Connect\"";

static uint8_t NEXTION_SENSOR_DISCONNECT_MSG[] = "\"Disconnect\"";

static uint16_t NEXTION_SENSOR_CONNECT_COLOR = 843;

static uint16_t NEXTION_SENSOR_DISCONNECT_COLOR = 59968;


// High or low temperature object attributes
static uint8_t NEXTION_HIGH_TEMP_ALERT_MSG[] = "\"High Temp\"";

static uint8_t NEXTION_LOW_TEMP_ALERT_MSG[] = "\"Norm Temp\"";

static uint16_t NEXTION_HIGH_TEMP_ALERT_COLOR = 59968;

static uint16_t NEXTION_LOW_TEMP_ALERT_COLOR = 1019;


/* System display handler instance */
static UART_HandleTypeDef displayUartHandler;

/**
 * Nextion screen visuals related to business logic
 */
static NextionObject_t nextionObjs [NUM_NEXTION_OBJS] = { NULL_VALUE };


/**
 * Vector that contains all the ports of the system displays,
 * at this point the handlers and function pointers are assigned.
 */
static NEXTION_Port_t NEXTION_DISPLAYS [NUM_DISPLAYS] = {

		(NEXTION_Port_t) {

			.uartDev = &displayUartHandler,

			/* Pointer to hal function */
			.uartPortWrite = &HAL_UART_Transmit,

		},

};


/**
 * @brief Assigning value and color to text objects
 *
 * This function assigns the color and textual value
 * to any text object contained in the nextion.
 *
 * Once these two attributes are assigned, it calls the
 * nextion driver to update this information on the display.
 *
 *
 * @param ref: Reference to nextion Object
 * @param color: Color to assign to the object
 * @param msg: Textual value to assign to the object
 *
 * @return None
 */
static void setVisualIndicatorValues (ObjectReference_e ref, uint16_t color, uint8_t* msg) {

	if (msg != NULL && ref >= E_FIRST_OBJECT && ref <= E_LAST_OBJECT) {

		memset((char*) nextionObjs[ref].txt, NULL_CHAR, OBJ_TEXT_VALUE_LEN);

		nextionObjs[ref].bco = color;

		strcat
			((char*) nextionObjs[ref].txt,
			 (str_cast) msg);

		NEXTION_UpdateTextValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[ref]);

		NEXTION_UpdateTextColor(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[ref]);

	}

}


/**
 * @brief Initialize system display
 *
 * This function initializes the UART communication handler of the
 * screen, and also establishes initialization parameters for the
 * display objects.
 *
 * @param None
 *
 * @return result: Configuration result
 */
bool_t BSP_NM_ConfigureDisplay (void) {

	bool_t result = true;

	displayUartHandler.Instance = NEXTION_UART_DEV;
	displayUartHandler.Init.BaudRate = NEXTION_UART_BAUDRATE;
	displayUartHandler.Init.WordLength = NEXTION_UART_WORD_LEN;
	displayUartHandler.Init.StopBits = NEXTION_UART_STOP_BITS;
	displayUartHandler.Init.Parity = NEXTION_UART_PARITY;
	displayUartHandler.Init.Mode = UART_MODE_TX_RX;
	displayUartHandler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	displayUartHandler.Init.OverSampling = UART_OVERSAMPLING_16;


	nextionObjs[E_TEMP_GRAPH].type = E_WAVE_FORM;
	nextionObjs[E_TEMP_GRAPH].id = TEMP_GRAPH_ID;
	nextionObjs[E_TEMP_GRAPH].channel = TEMP_GRAPH_CH;

	// E_STATE_SENSOR_INDICATOR
	strcat
		((char*) nextionObjs[E_STATE_SENSOR_INDICATOR].objname,
		 (str_cast)NEXTION_SENSOR_CONNECT_OBJNAME);

	nextionObjs[E_STATE_SENSOR_INDICATOR].type = E_TEXT;

	// E_TEMP_ALART_IDICATOR
	strcat
		((char*) nextionObjs[E_TEMP_ALART_IDICATOR].objname,
		 (str_cast)NEXTION_TEMP_ALARM_OBJNAME);

	nextionObjs[E_TEMP_ALART_IDICATOR].type = E_TEXT;

	// E_CELCIUS_INDICATOR
	strcat
		((char*) nextionObjs[E_CELCIUS_INDICATOR].objname,
		 (str_cast)NEXTION_NUMBER_CELCIUS_OBJNAME);

	nextionObjs[E_CELCIUS_INDICATOR].type = E_NUMBER;

	// E_KELVIN_INDICATOR
	strcat
		((char*) nextionObjs[E_KELVIN_INDICATOR].objname,
		 (str_cast)NEXTION_NUMBER_KELVIN_OBJNAME);

	nextionObjs[E_KELVIN_INDICATOR].type = E_NUMBER;

	// E_FARENHEIT_INDICATOR
	strcat
		((char*) nextionObjs[E_FARENHEIT_INDICATOR].objname,
		 (str_cast)NEXTION_NUMBER_FAREN_OBJNAME);

	nextionObjs[E_FARENHEIT_INDICATOR].type = E_NUMBER;



	result &= (HAL_UART_Init (&displayUartHandler) == HAL_OK);

	return result;

}


/**
 * @brief Updates object of type wave_form
 *
 * Data validations are carried out to assign wave_form type
 * components the temperature value to be displayed, finally
 * sending this update event to the nextion driver.
 *
 * @param tempData: Variable with temperature information
 *
 * @return None
 */
void BSP_NM_updateTempGraph (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		nextionObjs[E_TEMP_GRAPH].val = (uint8_t)tempData->temperature;

		if (tempData->temperature > GRAPH_MAX_TEMP_VALUE) {

			nextionObjs[E_TEMP_GRAPH].val = GRAPH_MAX_TEMP_VALUE;

		}

		NEXTION_UpdateWaveFormValue
			(&NEXTION_DISPLAYS[E_MAIN_DISPLAY],
			 &nextionObjs[E_TEMP_GRAPH]);

	}

}


/**
 * @brief Show temperature in Celsius
 *
 * This function can validate the incoming data, and assign the
 * temperature value in degrees Celsius to a numeric object of
 * the nextion, finally sending the update event to the nextion
 * driver.
 *
 * @param tempData: Variable with temperature information
 *
 * @return None
 */
void BSP_NM_ShowTemperatureCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			nextionObjs[E_CELCIUS_INDICATOR].val = (uint8_t)tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_CELCIUS_INDICATOR]);

		}

	}

}


/**
 * @brief Show temperature in Kelvin
 *
 * This function can validate the incoming data, and assign the
 * temperature value in degrees Kelvin to a numeric object of
 * the nextion, finally sending the update event to the nextion
 * driver.
 *
 * @param tempData: Variable with temperature information
 *
 * @return None
 */
void BSP_NM_ShowTemperatureKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			nextionObjs[E_KELVIN_INDICATOR].val = tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_KELVIN_INDICATOR]);

		}

	}

}


/**
 * @brief Show temperature in Farenheit
 *
 * This function can validate the incoming data, and assign the
 * temperature value in degrees Farenheit to a numeric object of
 * the nextion, finally sending the update event to the nextion
 * driver.
 *
 * @param tempData: Variable with temperature information
 *
 * @return None
 */
void BSP_NM_ShowTemperatureFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			nextionObjs[E_FARENHEIT_INDICATOR].val = tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_FARENHEIT_INDICATOR]);

		}

	}

}


/**
 * @brief Activate temperature alert
 *
 * This function activates the temperature alert indicator
 * on the nextion screen, so that it can be viewed on the
 * display
 *
 * @param None
 *
 * @return None
 */
void BSP_NM_activateTempAlarmIndicator (void) {

	setVisualIndicatorValues
		(E_TEMP_ALART_IDICATOR,
		 NEXTION_HIGH_TEMP_ALERT_COLOR,
		 NEXTION_HIGH_TEMP_ALERT_MSG);

}


/**
 * @brief Deactivate temperature alert
 *
 * This function deactivates the temperature alert indicator
 * on the nextion screen, so that it can be viewed on the
 * display
 *
 * @param None
 *
 * @return None
 */
void BSP_NM_deActivateTempAlarmIndicator (void) {

	setVisualIndicatorValues
		(E_TEMP_ALART_IDICATOR,
		 NEXTION_LOW_TEMP_ALERT_COLOR,
		 NEXTION_LOW_TEMP_ALERT_MSG);

}


/**
 * @brief Activate state sensor
 *
 * This function activates the state sensor indicator
 * on the nextion screen, so that it can be viewed on the
 * display
 *
 * @param None
 *
 * @return None
 */
void BSP_NM_activateStateSensorIndicator (void) {

	setVisualIndicatorValues
		(E_STATE_SENSOR_INDICATOR,
		 NEXTION_SENSOR_DISCONNECT_COLOR,
		 NEXTION_SENSOR_DISCONNECT_MSG);

}


/**
 * @brief Deactivate state sensor
 *
 * This function deactivates the state sensor indicator
 * on the nextion screen, so that it can be viewed on the
 * display
 *
 * @param None
 *
 * @return None
 */
void BSP_NM_deActivateStateSensorIndicator (void) {

	setVisualIndicatorValues
		(E_STATE_SENSOR_INDICATOR,
		 NEXTION_SENSOR_CONNECT_COLOR,
		 NEXTION_SENSOR_CONNECT_MSG);

}
