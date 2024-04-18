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
 * @file m_bsp_stm32f4_temperature_manager.c
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


/* Includes */
#include "m_bsp_stm32f4_temperature_manager.h"

#include "stm32f4xx_hal.h"

#include "m_driver_max6675.h"
#include "m_driver_max6675_hal_port.h"


/**
 * Engine temperature sensor handler instance
 */
static SPI_HandleTypeDef motorTempSensorSpiHandler;


/**
 * Vector that contains all the temperature sensor ports of the
 * system, at this point the handlers, slave selection pins and
 * function pointers are assigned.
 */
static Max6675_Port_t TEMP_SENSOR_PORTS [NUM_TEMPERATURE_SENSORS] = {

		(Max6675_Port_t) {
				.hspi = &motorTempSensorSpiHandler,
				.spiSsPinPort = MOTOR_TEMP_SENSOR_MAX6675_SPI_SS_PORT,
				.spiSsPin = MOTOR_TEMP_SENSOR_MAX6675_SPI_SS,

				/* Pointer to hal function */
				.spiPortRead = &HAL_SPI_Receive,
				.spiSsWrite = &HAL_GPIO_WritePin,
		},

};



/**
 * @brief Temperature sensor initialization
 *
 * This function initializes the handler of each port with the
 * parameters given by the configuration file depending on the
 * instance. It also initializes the slave selection pins of each
 * port. This happens at the chip level.
 *
 *
 * @param temperatureSensor: Temperature sensor port
 *
 * @return successfulConfig: Configuration result
 */
static bool_t initTemperatureSensor (Max6675_Port_t* temperatureSensor) {

	SPI_HandleTypeDef* spiHandler;
	GPIO_InitTypeDef  GPIO_InitStruct;
	bool_t successfulConfig = true;

	/* Enable the GPIO_LED Clock */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/* Engine temperature sensor instance */
	if (temperatureSensor->hspi->Instance == MOTOR_TEMP_SENSOR_MAX6675_SPI_DEV) {

		spiHandler = temperatureSensor->hspi;

		/* System configuration parameters */
		spiHandler->Init.Mode = MOTOR_TEMP_SENSOR_MAX6675_SPI_MODE;
		spiHandler->Init.Direction = SPI_DIRECTION_2LINES;
		spiHandler->Init.DataSize = MOTOR_TEMP_SENSOR_MAX6675_SPI_DATA_SIZE;
		spiHandler->Init.CLKPolarity = MOTOR_TEMP_SENSOR_MAX6675_SPI_CPOL;
		spiHandler->Init.CLKPhase = MOTOR_TEMP_SENSOR_MAX6675_SPI_CPHA;
		spiHandler->Init.NSS = SPI_NSS_SOFT;
		spiHandler->Init.BaudRatePrescaler = MOTOR_TEMP_SENSOR_MAX6675_SPI_PRESCALER;
		spiHandler->Init.FirstBit = MOTOR_TEMP_SENSOR_MAX6675_SPI_ENDIANNESS;
		spiHandler->Init.TIMode = SPI_TIMODE_DISABLE;
		spiHandler->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		spiHandler->Init.CRCPolynomial = 10;


		HAL_GPIO_WritePin
			(temperatureSensor->spiSsPinPort,
			 temperatureSensor->spiSsPin, GPIO_PIN_RESET);

		/* Configure the GPIO_LED pin */
		GPIO_InitStruct.Pin = temperatureSensor->spiSsPin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	}

	HAL_GPIO_Init (temperatureSensor->spiSsPinPort, &GPIO_InitStruct);

	HAL_GPIO_WritePin
		(temperatureSensor->spiSsPinPort,
		 temperatureSensor->spiSsPin, GPIO_PIN_SET);

	successfulConfig &= (HAL_SPI_Init (temperatureSensor->hspi) == HAL_OK);

	return successfulConfig;

}


/**
 * @brief Temperature sensors initialization
 *
 * This function sequentially configures all the temperature
 * sensor instances in the system, and also defines the
 * instance of each sensor based on the reference.
 *
 *
 * @param None
 *
 * @return result: Configuration result
 */
bool_t BSP_TM_InitTemperatureSensors (void) {

	bool_t result = true;
	Max6675_Port_t* temperatureSensor = { 0 };

	for (int8_t i = E_FIRTS_TEMP_SENSOR; i < E_LAST_TEMP_SENSOR; i++) {

		temperatureSensor = &TEMP_SENSOR_PORTS[i];

		switch (i) {

			case E_MOTOR_TEMP_SENSOR: {

				temperatureSensor->hspi->Instance = MOTOR_TEMP_SENSOR_MAX6675_SPI_DEV;
				break;

			}

			default:
				temperatureSensor->hspi->Instance = NULL;
				break;

		};

		result &= initTemperatureSensor (temperatureSensor);

	}

	return result;

}



/**
 * @brief Calculate current temperature data
 *
 * This function calculates the current temperature data
 * for the motor temperature sensor, it does this by invoking
 * the driver's own routines for MAX6675 devices.
 *
 *
 * @param tempData: Current temperature data
 *
 * @return None
 */
void BSP_TM_GetTemperatureData (TemperatureData_t* tempData) {

	if (tempData != NULL) {

		MAX6675_updateDataRaw(&TEMP_SENSOR_PORTS[E_MOTOR_TEMP_SENSOR]);

		*tempData = (TemperatureData_t) {

			.temperature = MAX6675_getTemperature (),
			.units = E_CELCIUS,
			.sensorStatus = MAX6675_getSensorStatus(),

		};

	}

}


/**
 * @brief Gets the connection status of the transducer
 *
 * This function obtains the status of the type k thermocouple
 * by consulting the device driver.
 *
 *
 * @param None
 *
 * @return sensorStatus: Thermocouple connection status
 */
SensorStatus_e BSP_TM_GetSensorStatus (void) {

	MAX6675_updateDataRaw(&TEMP_SENSOR_PORTS[E_MOTOR_TEMP_SENSOR]);

	return MAX6675_getSensorStatus();

}
