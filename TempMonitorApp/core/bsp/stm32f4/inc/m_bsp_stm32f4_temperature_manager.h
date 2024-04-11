/*
 * m_bsp_stm32f4_temperature_manager.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__
#define __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__

#include <stdint.h>
#include <stddef.h>

#include "stm32f4xx_hal.h"

#include "m_bsp_stm32_hardware_config.h"
#include "m_ddt_temperature_data_types.h"
#include "m_bsp_stm32f4_setup.h"
#include "m_driver_max6675.h"
#include "m_driver_max6675_hal_port.h"

typedef enum {

	E_MOTOR_TEMP_SENSOR = 0,

} TempSensor_e;


void BSP_TM_InitTemperatureSensors (void);
void BSP_TM_GetTemperatureData (TemperatureData_t* tempData);


#endif /* __M_BSP_STM32F4_TEMPERATURE_MANAGER_H__ */
