/*
 * m_driver_max6675.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */


#include "m_driver_max6675.h"


static const float FACT_TEMPERATURE = 0.25;
static uint8_t data[MAX6675_DATA_SIZE_BYTES];


void MAX6675_updateDataRaw (Max6675_Port_t* port) {

	if (port != NULL) {

		port->spiSsWrite (port->spiSsPinPort, port->spiSsPin, E_SELECTED);

		port->spiPortRead (port->hspi, data, MAX6675_DATA_SIZE_BYTES, TEMP_SENSOR_MAX6675_SPI_TIMEOUT);

		port->spiSsWrite (port->spiSsPinPort, port->spiSsPin, E_NO_SELECTED);

	}

}


float MAX6675_getTemperature (void) {

	uint16_t temperature = 0;
	uint16_t temp_h = data[TEMP_BYTE_H] << TEMP_OFFSET_BITS_H;
	uint16_t temp_l = data[TEMP_BYTE_L];

	temperature = (temp_h | temp_l) >> TEMP_OFFSET_BITS;

	return (float) (temperature * FACT_TEMPERATURE);

}


uint8_t MAX6675_getSensorStatus (void) {

	uint8_t sensorState = data[TEMP_BYTE_L] >> SENSOR_STATE_OFFSET_BITS;

	sensorState = sensorState & SENSOR_STATE_MASK;

	return !sensorState;

}

