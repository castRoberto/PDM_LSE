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
 * @file m_bsp_stm32_hardware_config.h
 * @brief Defining hardware instances
 *
 * This header file is used to define all hardware device instances of
 * the application
 *
 * @author Roberto Castro
 * @date March 21 2024
 *
 */

#ifndef __M_BSP_STM32_HARDWARE_CONFIG_H__
#define __M_BSP_STM32_HARDWARE_CONFIG_H__

#define SYSTEM_NAME "Temperature monitor"

/**
 * LEDS
 */
#define NUM_VISUAL_INDICATORS 3

#define RUNNING_INDICATOR 										GPIO_PIN_0
#define RUNNING_INDICATOR_PORT 									GPIOB

#define TEMPERATURE_ALARM_INDICATOR								GPIO_PIN_14
#define TEMPERATURE_ALARM_INDICATOR_PORT 						GPIOB

#define TEMPERATURE_STATUS_SENSOR_INDICATOR 					GPIO_PIN_7
#define TEMPERATURE_STATUS_SENSOR_INDICATOR_PORT 				GPIOB


/**
 * BUTTONS
 */
#define NUM_BUTTONS 1

#define START_BUTTON 											GPIO_PIN_13
#define START_BUTTON_PORT 										GPIOC

#define RINNING_INDICATOR_PERIOD_LOW_MS							800
#define RINNING_INDICATOR_PERIOD_HIGH_MS						50
#define DEFAULT_PERIOD_10MS										10


/**
 * TEMPERATURE
 */
#define NUM_TEMPERATURE_SENSORS 1

#define MOTOR_TEMP_SENSOR_MAX6675_SPI_DEV						SPI1	//SPI_TypeDef
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_MODE						SPI_MODE_MASTER
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_SS						GPIO_PIN_14
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_SS_PORT					GPIOD
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_CPOL						SPI_POLARITY_LOW
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_CPHA						SPI_PHASE_1EDGE
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_DATA_SIZE					SPI_DATASIZE_8BIT
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_PRESCALER					SPI_BAUDRATEPRESCALER_256
#define MOTOR_TEMP_SENSOR_MAX6675_SPI_ENDIANNESS				SPI_FIRSTBIT_MSB
#define TEMP_SENSOR_MAX6675_SPI_TIMEOUT							100


/**
 * NEXTION DISPLAY
 */
#define NEXTION_UART_DEV										USART3
#define NEXTION_UART_BAUDRATE									9600
#define NEXTION_UART_TIMEOUT									100


/**
 * APPLICATION CONSTANTS
 */
#define SAMPLING_RATE_MS										150
#define TEMPERATURE_THRESHOLD_ALARM								60


#endif /* __M_BSP_STM32_HARDWARE_CONFIG_H__ */
