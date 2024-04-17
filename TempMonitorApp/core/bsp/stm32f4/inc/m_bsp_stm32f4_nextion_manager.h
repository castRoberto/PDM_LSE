/*
 * m_bsp_stm32f4_nextion_manager.h
 *
 *  Created on: Mar 22, 2024
 *      Author: operador
 */

#ifndef __M_BSP_STM32F4_NEXTION_MANAGER_H__
#define __M_BSP_STM32F4_NEXTION_MANAGER_H__

#include <stdint.h>
#include <string.h>

#include "stm32f4xx_hal.h"

#include "m_bsp_stm32f4_setup.h"
#include "m_bsp_stm32_hardware_config.h"
#include "m_ddt_temperature_data_types.h"
#include "m_driver_nextion.h"
#include "m_driver_nextion_port.h"


#define NUM_NEXTION_OBJS 6


typedef enum {

	E_TEMP_GRAPH = 0,
	E_STATE_SENSOR_INDICATOR = 1,
	E_TEMP_ALART_IDICATOR = 2,
	E_CELCIUS_INDICATOR = 3,
	E_KELVIN_INDICATOR = 4,
	E_FARENHEIT_INDICATOR = 5,

} ObjectReference_e;


typedef enum {

	E_MAIN_DISPLAY = 0,

} DisplayReference_e;


/**
 *
 */
bool_t BSP_NM_ConfigureDisplay (void);
void BSP_NM_updateTempGraph (TemperatureData_t* tempData);


void BSP_NM_ShowTemperatureCelcius (TemperatureData_t* tempData);
void BSP_NM_ShowTemperatureKelvin (TemperatureData_t* tempData);
void BSP_NM_ShowTemperatureFarenheit (TemperatureData_t* tempData);

void BSP_NM_activateTempAlarmIndicator (void);
void BSP_NM_deActivateTempAlarmIndicator (void);

void BSP_NM_activateStateSensorIndicator (void);
void BSP_NM_deActivateStateSensorIndicator (void);


#endif /* __M_BSP_STM32F4_NEXTION_MANAGER_H__ */
