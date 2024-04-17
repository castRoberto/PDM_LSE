/*
 * m_ddt_temperature_data_types.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_DDT_TEMPERATURE_DATA_TYPES_H__
#define __M_DDT_TEMPERATURE_DATA_TYPES_H__

#include "m_ddt_common_types.h"

#define MAX_TEMP 255
#define MIN_TEMP 0

typedef enum {

	E_DISCONNECTED = 0,
	E_CONNECTED = 1,

} SensorStatus_e;


typedef enum {

	E_UNKNOWN_UNITS = 0,
	E_CELCIUS = 1,
	E_KELVIN = 2,
	E_FARENHEIT = 3,

} TemperatureUnits_e;


typedef struct {

	float temperature;
	TemperatureUnits_e units;
	SensorStatus_e sensorStatus;

} TemperatureData_t;


#endif /* __M_DDT_TEMPERATURE_DATA_TYPES_H__ */
