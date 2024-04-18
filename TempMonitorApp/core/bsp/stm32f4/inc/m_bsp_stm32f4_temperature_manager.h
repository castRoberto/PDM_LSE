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
 * @file m_bsp_stm32f4_temperature_manager.h
 *
 * @brief Temperature manager Module
 *
 * This module acts as a facade for higher level layers that
 * require temperature information from the hardware, therefore
 * exposing functions that contain a business logic context as
 * well as a hardware generalization..
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */

#ifndef __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__
#define __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__


/* Includes */
#include "m_bsp_stm32_system_config.h"
#include "m_ddt_temperature_data_types.h"


/**
 * This enumeration defines a set of references to
 * instances of the system's temperature sensors.
 */
typedef enum {

	E_MOTOR_TEMP_SENSOR = 0,

	E_FIRTS_TEMP_SENSOR = E_MOTOR_TEMP_SENSOR,
	E_LAST_TEMP_SENSOR = NUM_TEMPERATURE_SENSORS,

} TempSensor_e;


/**
 * Prototypes of public functions for the control of
 * system temperature sensors. Related to the business logic.
 */
bool_t BSP_TM_InitTemperatureSensors (void);
void BSP_TM_GetTemperatureData (TemperatureData_t* tempData);
SensorStatus_e BSP_TM_GetSensorStatus (void);


#endif /* __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__ */
