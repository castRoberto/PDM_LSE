/*
 * m_ddt_temperature_data_types.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_DDT_TEMPERATURE_DATA_TYPES_H__
#define __M_DDT_TEMPERATURE_DATA_TYPES_H__

typedef enum {

	E_DISCONNECTED = 0,
	E_CONNECTED = 1,

} SensorStatus_e;


typedef enum {

	E_CELCIUS,
	E_KELVIN,
	E_FARENHEIT,

} TemperatureUnits_e;


typedef struct {

	float temperature;
	TemperatureUnits_e units;
	SensorStatus_e sensorStatus;

} TemperatureData_t;


#endif /* __M_DDT_TEMPERATURE_DATA_TYPES_H__ */
