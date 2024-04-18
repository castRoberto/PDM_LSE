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
 * @file m_bsp_stm32f4_nextion_manager.h
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

#ifndef __M_BSP_STM32F4_NEXTION_MANAGER_H__
#define __M_BSP_STM32F4_NEXTION_MANAGER_H__


/* Includes */
#include "m_ddt_temperature_data_types.h"


#define NUM_NEXTION_OBJS 6


/**
 * This enumeration defines a set of references
 * to instances of nextion-type objects.
 */
typedef enum {

	E_TEMP_GRAPH = 0,
	E_STATE_SENSOR_INDICATOR = 1,
	E_TEMP_ALART_IDICATOR = 2,
	E_CELCIUS_INDICATOR = 3,
	E_KELVIN_INDICATOR = 4,
	E_FARENHEIT_INDICATOR = 5,

	E_FIRST_OBJECT = E_TEMP_GRAPH,
	E_LAST_OBJECT = NUM_NEXTION_OBJS,

} ObjectReference_e;


/**
 * Esta enumeración define un conjunto de
 * referencias a instancias de displays del
 * sistema.
 */
typedef enum {

	E_MAIN_DISPLAY = 0,

} DisplayReference_e;


/**
 * Prototypes of public functions for the system
 * in nextion objects, Related to business logic.
 */
bool_t BSP_NM_ConfigureDisplay (void);
void BSP_NM_updateTempGraph (TemperatureData_t* tempData);


void BSP_NM_ShowTemperatureCelcius (TemperatureData_t* tempData);
void BSP_NM_ShowTemperatureKelvin (TemperatureData_t* tempData);
void BSP_NM_ShowTemperatureFarenheit (TemperatureData_t* tempData);

void BSP_NM_activateTempAlarmIndicator (void);
void BSP_NM_deActivateTempAlarmIndicator (void);

void BSP_NM_activateStateSensorIndicator (void);
void BSP_NM_deActivateStateSensorIndicator (void);


#endif /* __M_BSP_STM32F4_NEXTION_MANAGER_H__ */
