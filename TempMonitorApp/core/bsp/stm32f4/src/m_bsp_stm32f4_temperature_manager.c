/*
 * m_bsp_stm32f4_temperature_manager.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */
#include "m_bsp_stm32f4_temperature_manager.h"


static SPI_HandleTypeDef motorTempSensorSpiHandler = {
		.Instance = MOTOR_TEMP_SENSOR_MAX6675_SPI_DEV,
		.Init.Mode = MOTOR_TEMP_SENSOR_MAX6675_SPI_MODE,
		.Init.Direction = SPI_DIRECTION_2LINES,
		.Init.DataSize = MOTOR_TEMP_SENSOR_MAX6675_SPI_DATA_SIZE,
		.Init.CLKPolarity = MOTOR_TEMP_SENSOR_MAX6675_SPI_CPOL,
		.Init.CLKPhase = MOTOR_TEMP_SENSOR_MAX6675_SPI_CPHA,
		.Init.NSS = SPI_NSS_SOFT,
		.Init.BaudRatePrescaler = MOTOR_TEMP_SENSOR_MAX6675_SPI_PRESCALER,
		.Init.FirstBit = MOTOR_TEMP_SENSOR_MAX6675_SPI_ENDIANNESS,
		.Init.TIMode = SPI_TIMODE_DISABLE,
		.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
		.Init.CRCPolynomial = 10
};

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


static void initTemperatureSensor (Max6675_Port_t* temperatureSensor) {

	if (HAL_SPI_Init (temperatureSensor->hspi) != HAL_OK) {

		BSP_Error_Handler ();

	}

	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Enable the GPIO_LED Clock */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	HAL_GPIO_WritePin (temperatureSensor->spiSsPinPort, temperatureSensor->spiSsPin, GPIO_PIN_RESET);


	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = temperatureSensor->spiSsPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init (temperatureSensor->spiSsPinPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin (temperatureSensor->spiSsPinPort, temperatureSensor->spiSsPin, GPIO_PIN_SET);

}


void BSP_TM_InitTemperatureSensors (void) {

	for (int8_t i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {

		initTemperatureSensor (&TEMP_SENSOR_PORTS[i]);

	}

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
