/*
 * m_lib_util_temp_converter.h
 *
 *  Created on: Apr 14, 2024
 *      Author: rober
 */

#ifndef __M_LIB_UTIL_TEMP_CONVERTER_H__
#define __M_LIB_UTIL_TEMP_CONVERTER_H__

#include "m_ddt_temperature_data_types.h"
#include "m_ddt_common_types.h"


void LIB_TC_celciusToKelvin (TemperatureData_t* tempData);
void LIB_TC_kelvinToCelcius (TemperatureData_t* tempData);

void LIB_TC_celciusToFarenheit (TemperatureData_t* tempData);
void LIB_TC_farenheitToCelcius (TemperatureData_t* tempData);

void LIB_TC_kelvinToFarenheit (TemperatureData_t* tempData);
void LIB_TC_farenheitToKelvin (TemperatureData_t* tempData);


#endif /* __M_LIB_UTIL_TEMP_CONVERTER_H__ */
