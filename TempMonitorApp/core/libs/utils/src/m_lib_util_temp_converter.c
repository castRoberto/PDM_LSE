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
 * @file m_lib_util_temp_converter.c
 * @brief Temperature conversion
 *
 * Module to convert between different temperature
 * units.
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */

#include "m_lib_util_temp_converter.h"


/**
 * Temperature conversion factors
 */
static const float CELCIUS_TO_KELVIN_FAC = 273.15;
static const float CELCIUS_TO_FAREN_FAC1 = 1.8;
static const float CELCIUS_TO_FAREN_FAC2 = 32.0;



/**
 * @brief Convert temperature from celsius to kelvin
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Celsius to Kelvin.
 *
 *
 * @param tempData: Temperature converted to Kelvin
 *
 * @return None.
 */
void LIB_TC_celciusToKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			tempData->temperature = tempData->temperature + CELCIUS_TO_KELVIN_FAC;

			tempData->units = E_KELVIN;

		}

	}

}


/**
 * @brief Convert temperature from kelvin to celsius
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Kelvin to Celsius.
 *
 *
 * @param tempData: Temperature converted to Celsius
 *
 * @return None.
 */
void LIB_TC_kelvinToCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			tempData->temperature = tempData->temperature - CELCIUS_TO_KELVIN_FAC;

			tempData->units = E_CELCIUS;

		}

	}

}


/**
 * @brief Convert temperature from Celsius to Farenheit
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Celsius to Farenheit.
 *
 *
 * @param tempData: Temperature converted to Farenheit
 *
 * @return None.
 */
void LIB_TC_celciusToFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			tempData->temperature =
					(tempData->temperature * CELCIUS_TO_FAREN_FAC1) + CELCIUS_TO_FAREN_FAC2;

			tempData->units = E_FARENHEIT;

		}

	}

}


/**
 * @brief Convert temperature from Farenheit to Celsius
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Farenheit to Celsius.
 *
 *
 * @param tempData: Temperature converted to Celsius
 *
 * @return None.
 */
void LIB_TC_farenheitToCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			tempData->temperature =
					(tempData->temperature - CELCIUS_TO_FAREN_FAC2) / CELCIUS_TO_FAREN_FAC1;

			tempData->units = E_CELCIUS;

		}

	}

}


/**
 * @brief Convert temperature from Kelvin to Farenheit
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Kelvin to Farenheit.
 *
 *
 * @param tempData: Temperature converted to Farenheit
 *
 * @return None.
 */
void LIB_TC_kelvinToFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			LIB_TC_kelvinToCelcius(tempData);

			LIB_TC_celciusToFarenheit(tempData);

		}

	}

}


/**
 * @brief Convert temperature from Farenheit to kelvin
 *
 * Function that verifies whether the source data is valid to perform
 * the conversion calculation from degrees Farenheit to Kelvin.
 *
 *
 * @param tempData: Temperature converted to Kelvin
 *
 * @return None.
 */
void LIB_TC_farenheitToKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			LIB_TC_farenheitToCelcius(tempData);

			LIB_TC_celciusToKelvin(tempData);

		}

	}

}


