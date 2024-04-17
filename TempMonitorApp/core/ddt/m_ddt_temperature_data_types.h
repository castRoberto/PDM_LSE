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
 * @file m_ddt_temperature_data_types.h
 * @brief Temperature data types
 *
 * This header file provides the data types useful for
 * working with a temperature sensor.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */


#ifndef __M_DDT_TEMPERATURE_DATA_TYPES_H__
#define __M_DDT_TEMPERATURE_DATA_TYPES_H__


#include "m_ddt_common_types.h"


/**
 * Definition of operational
 * temperature limits
 */
#define MAX_TEMP 255
#define MIN_TEMP 0


/**
 * Defines the possible physical connection states
 *  of the temperature sensor
 */
typedef enum {

	E_DISCONNECTED = 0,
	E_CONNECTED = 1,

} SensorStatus_e;


/**
 * Defines the possible temperature units that the system
 * can manipulate
 */
typedef enum {

	E_UNKNOWN_UNITS = 0,
	E_CELCIUS = 1,
	E_KELVIN = 2,
	E_FARENHEIT = 3,

} TemperatureUnits_e;


/**
 * Definition of structure that models a sample of temperature
 * data
 */
typedef struct {

	float temperature;
	TemperatureUnits_e units;
	SensorStatus_e sensorStatus;

} TemperatureData_t;


#endif /* __M_DDT_TEMPERATURE_DATA_TYPES_H__ */
