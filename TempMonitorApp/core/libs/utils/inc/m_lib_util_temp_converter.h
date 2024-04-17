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
 * @file m_lib_util_temp_converter.h
 * @brief Temperature conversion
 *
 * Module to convert between different temperature
 * units.
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */

#ifndef __M_LIB_UTIL_TEMP_CONVERTER_H__
#define __M_LIB_UTIL_TEMP_CONVERTER_H__

#include "m_ddt_temperature_data_types.h"



/**
 * Public prototypes of temperature conversion functions
 */
void LIB_TC_celciusToKelvin (TemperatureData_t* tempData);
void LIB_TC_kelvinToCelcius (TemperatureData_t* tempData);

void LIB_TC_celciusToFarenheit (TemperatureData_t* tempData);
void LIB_TC_farenheitToCelcius (TemperatureData_t* tempData);

void LIB_TC_kelvinToFarenheit (TemperatureData_t* tempData);
void LIB_TC_farenheitToKelvin (TemperatureData_t* tempData);


#endif /* __M_LIB_UTIL_TEMP_CONVERTER_H__ */
