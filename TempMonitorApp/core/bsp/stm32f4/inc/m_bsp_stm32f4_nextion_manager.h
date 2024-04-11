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

#define NEXTION_SENSOR_CONNECT_MSG_LEN 22
#define NEXTION_SENSOR_CONNECT_COLOR_MSG_LEN 18
#define NEXTION_SENSOR_DISCONNECT_MSG_LEN 25
#define NEXTION_WAVEFORM_MSG_LEN 14

#define NEXTION_WAVEFORM_ID '1'
#define NEXTION_WAVEFORM_CHANNEL '0'
#define NEXTION_WAVEFORM_SEPARATOR ','
#define NEXTION_END_MSG 0XFF



/**
 *
 */
void BSP_NM_ConfigureDisplay (void);
void BSP_NM_ShowTemperatureData (TemperatureData_t* tempData);


#endif /* __M_BSP_STM32F4_NEXTION_MANAGER_H__ */
