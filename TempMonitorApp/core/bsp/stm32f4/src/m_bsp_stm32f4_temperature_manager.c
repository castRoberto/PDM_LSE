/*
 * m_bsp_stm32f4_temperature_manager.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */
#include "m_bsp_stm32f4_temperature_manager.h"


static SPI_HandleTypeDef motorTempSensorSpiHandler;

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

	if (temperatureSensor->hspi->Instance == MOTOR_TEMP_SENSOR_MAX6675_SPI_DEV) {

		spiHandler = temperatureSensor->hspi;

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
