/*
 * m_bsp_stm32f4_nextion_manager.c
 *
 *  Created on: Mar 22, 2024
 *      Author: operador
 */


#include "m_bsp_stm32f4_nextion_manager.h"

#include "m_bsp_stm32f4_setup.h"
#include "m_bsp_stm32_system_config.h"

#include "m_driver_nextion.h"
#include "m_driver_nextion_port.h"



#define MAIN_PAGE 0

#define TEMP_GRAPH_ID 4
#define TEMP_GRAPH_CH 0
#define GRAPH_MAX_TEMP_VALUE 255

#define NULL_VALUE 0


static uint8_t NEXTION_SENSOR_CONNECT_OBJNAME[] = "state";

static uint8_t NEXTION_TEMP_ALARM_OBJNAME[] = "tempAlarm";

static uint8_t NEXTION_NUMBER_CELCIUS_OBJNAME[] = "celcius";

static uint8_t NEXTION_NUMBER_KELVIN_OBJNAME[] = "kelvin";

static uint8_t NEXTION_NUMBER_FAREN_OBJNAME[] = "faren";



static uint8_t NEXTION_SENSOR_CONNECT_MSG[] = "\"Connect\"";

static uint8_t NEXTION_SENSOR_DISCONNECT_MSG[] = "\"Disconnect\"";

static uint16_t NEXTION_SENSOR_CONNECT_COLOR = 843;

static uint16_t NEXTION_SENSOR_DISCONNECT_COLOR = 59968;



static uint8_t NEXTION_HIGH_TEMP_ALERT_MSG[] = "\"High Temp\"";

static uint8_t NEXTION_LOW_TEMP_ALERT_MSG[] = "\"Norm Temp\"";

static uint16_t NEXTION_HIGH_TEMP_ALERT_COLOR = 59968;

static uint16_t NEXTION_LOW_TEMP_ALERT_COLOR = 1019;



static UART_HandleTypeDef displayUartHandler;

/**
 * Objects
 */
static NextionObject_t nextionObjs [NUM_NEXTION_OBJS] = { NULL_VALUE };


static NEXTION_Port_t NEXTION_DISPLAYS [NUM_DISPLAYS] = {

		(NEXTION_Port_t) {

			.uartDev = &displayUartHandler,

			/* Pointer to hal function */
			.uartPortWrite = &HAL_UART_Transmit,

		},

};


void setVisualIndicatorValues (ObjectReference_e ref, uint16_t color, uint8_t* msg) {

	memset((char*) nextionObjs[ref].txt, NULL_CHAR, OBJ_TEXT_VALUE_LEN);

	nextionObjs[ref].bco = color;

	strcat
		((char*) nextionObjs[ref].txt,
		 (str_cast) msg);

	NEXTION_UpdateTextValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[ref]);

	NEXTION_UpdateTextColor(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[ref]);

}


bool_t BSP_NM_ConfigureDisplay (void) {

	bool_t result = true;

	displayUartHandler.Instance = NEXTION_UART_DEV;
	displayUartHandler.Init.BaudRate = NEXTION_UART_BAUDRATE;
	displayUartHandler.Init.WordLength = UART_WORDLENGTH_8B;
	displayUartHandler.Init.StopBits = UART_STOPBITS_1;
	displayUartHandler.Init.Parity = UART_PARITY_NONE;
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


void BSP_NM_ShowTemperatureCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			nextionObjs[E_CELCIUS_INDICATOR].val = (uint8_t)tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_CELCIUS_INDICATOR]);

		}

	}

}


void BSP_NM_ShowTemperatureKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			nextionObjs[E_KELVIN_INDICATOR].val = tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_KELVIN_INDICATOR]);

		}

	}

}


void BSP_NM_ShowTemperatureFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			nextionObjs[E_FARENHEIT_INDICATOR].val = tempData->temperature;

			NEXTION_UpdateNumberValue(&NEXTION_DISPLAYS[E_MAIN_DISPLAY], &nextionObjs[E_FARENHEIT_INDICATOR]);

		}

	}

}


void BSP_NM_activateTempAlarmIndicator (void) {

	setVisualIndicatorValues
		(E_TEMP_ALART_IDICATOR,
		 NEXTION_HIGH_TEMP_ALERT_COLOR,
		 NEXTION_HIGH_TEMP_ALERT_MSG);

}


void BSP_NM_deActivateTempAlarmIndicator (void) {

	setVisualIndicatorValues
		(E_TEMP_ALART_IDICATOR,
		 NEXTION_LOW_TEMP_ALERT_COLOR,
		 NEXTION_LOW_TEMP_ALERT_MSG);

}


void BSP_NM_activateStateSensorIndicator (void) {

	setVisualIndicatorValues
		(E_STATE_SENSOR_INDICATOR,
		 NEXTION_SENSOR_DISCONNECT_COLOR,
		 NEXTION_SENSOR_DISCONNECT_MSG);

}


void BSP_NM_deActivateStateSensorIndicator (void) {

	setVisualIndicatorValues
		(E_STATE_SENSOR_INDICATOR,
		 NEXTION_SENSOR_CONNECT_COLOR,
		 NEXTION_SENSOR_CONNECT_MSG);

}
