/*
 * m_lib_util_temp_converter.c
 *
 *  Created on: Apr 14, 2024
 *      Author: rober
 */

#include "m_lib_util_temp_converter.h"

static const float CELCIUS_TO_KELVIN_FAC = 273.15;
static const float CELCIUS_TO_FAREN_FAC1 = 1.8;
static const float CELCIUS_TO_FAREN_FAC2 = 32.0;



void LIB_TC_celciusToKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			tempData->temperature = tempData->temperature + CELCIUS_TO_KELVIN_FAC;

			tempData->units = E_KELVIN;

		}

	}

}


void LIB_TC_kelvinToCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			tempData->temperature = tempData->temperature - CELCIUS_TO_KELVIN_FAC;

			tempData->units = E_CELCIUS;

		}

	}

}


void LIB_TC_celciusToFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_CELCIUS) {

			tempData->temperature =
					(tempData->temperature * CELCIUS_TO_FAREN_FAC1) + CELCIUS_TO_FAREN_FAC2;

			tempData->units = E_FARENHEIT;

		}

	}

}


void LIB_TC_farenheitToCelcius (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			tempData->temperature =
					(tempData->temperature - CELCIUS_TO_FAREN_FAC2) / CELCIUS_TO_FAREN_FAC1;

			tempData->units = E_CELCIUS;

		}

	}

}


void LIB_TC_kelvinToFarenheit (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_KELVIN) {

			LIB_TC_kelvinToCelcius(tempData);

			LIB_TC_celciusToFarenheit(tempData);

		}

	}

}


void LIB_TC_farenheitToKelvin (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		if (tempData->units == E_FARENHEIT) {

			LIB_TC_farenheitToCelcius(tempData);

			LIB_TC_celciusToKelvin(tempData);

		}

	}

}


