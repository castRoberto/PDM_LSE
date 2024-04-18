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
 * @file m_driver_max6675.c
 * @brief Driver for the MAX6675 module
 *
 * This driver allows you to manage low-level communications with the
 * MAX6675 temperature measurement module. It has complete management
 * of the byte frame format, which allows you to know the real temperature
 * value and the connection status of the transducer.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */


#include "m_driver_max6675.h"


/**
 * Constants inherent to the temperature conversion
 * process from binary format to degrees Celsius format
 */
#define MAX6675_DATA_SIZE_BYTES 2
#define TEMP_BYTE_H 0
#define TEMP_BYTE_L 1
#define TEMP_OFFSET_BITS 3
#define TEMP_OFFSET_BITS_H 8

#define SENSOR_STATE_MASK 0x01
#define SENSOR_STATE_OFFSET_BITS 2

#define TEMP_SENSOR_MAX6675_SPI_TIMEOUT 100


/**
 * Definition of the conversion factor from binary integer
 * to temperature in celcius and raw data array.
 */
static const float FACT_TEMPERATURE = 0.25;
static uint8_t data[MAX6675_DATA_SIZE_BYTES];


/**
 * @brief Raw data update
 *
 * Function that invokes the routines of an SPI communication
 * port for communication with the device, is responsible for
 * selecting the slave, reading the port and releasing the
 * slave, thereby obtaining new data from the sensor.
 *
 *
 * @param port: Pointer to an SPI port for sensor reading
 *
 * @return None
 */
void MAX6675_updateDataRaw (Max6675_Port_t* port) {

	if (port != NULL) {

		port->spiSsWrite (port->spiSsPinPort, port->spiSsPin, E_SELECTED);

		port->spiPortRead (port->hspi, data, MAX6675_DATA_SIZE_BYTES, TEMP_SENSOR_MAX6675_SPI_TIMEOUT);

		port->spiSsWrite (port->spiSsPinPort, port->spiSsPin, E_NO_SELECTED);

	}

}


/**
 * @brief Returns the instantaneous temperature data
 *
 * This function takes the hard data array and divides it into
 * two 16-bit integers, one with the most significant part of the
 * frame and one with the least significant part. The upper part is
 * moved 8 positions to the left and joined with the lower part
 * using an or operation. Then the resulting integer is shifted three
 * positions to the right and the result is multiplied by 0.25, thus
 * obtaining the temperature variable. This can be verified in the
 * module datasheet.
 *
 *
 * @param None
 *
 * @return Temperature: Measured temperature
 */
float MAX6675_getTemperature (void) {

	uint16_t temperature = 0;
	uint16_t temp_h = data[TEMP_BYTE_H] << TEMP_OFFSET_BITS_H;
	uint16_t temp_l = data[TEMP_BYTE_L];

	temperature = (temp_h | temp_l) >> TEMP_OFFSET_BITS;

	return (float) (temperature * FACT_TEMPERATURE);

}


/**
 * @brief Returns the transducer connection status
 *
 * This function takes the lower part of the hard data latch and shifts
 * it two positions to the right, then applies an and operation with a bit
 * mask to turn off the non-relevant bits, negates the result, and this
 * represents the state of the data latch. transducer.
 * Check the device datasheet where you will find more details
 *
 * Reading bit 2 of the data lock indicates to the system the
 * connection/disconnection status of the type k thermocouple, if
 * the bit has a state of "0" the sensor is operating correctly,
 * otherwise it will be disconnected
 *
 *
 * @param None
 *
 * @return sensorState: Transducer status
 */
uint8_t MAX6675_getSensorStatus (void) {

	uint8_t sensorState = data[TEMP_BYTE_L] >> SENSOR_STATE_OFFSET_BITS;

	sensorState = sensorState & SENSOR_STATE_MASK;

	return !sensorState;

}

