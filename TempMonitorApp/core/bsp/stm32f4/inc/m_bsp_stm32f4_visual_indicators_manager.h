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
 * @file m_bsp_stm32f4_visual_indicators_manager.h
 *
 * @brief Visual Indicators Manager Module
 *
 * This module acts as a facade for the higher level layers that
 * require controlling visual indicators of the hardware, therefore
 * it exposes functions that contain a context of the business logic
 * as well as a generalization of the hardware.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */

#ifndef __M_BSP_STM32F4_LEDS_H__
#define __M_BSP_STM32F4_LEDS_H__

/* Includes */
#include "m_bsp_stm32_system_config.h"
#include "m_ddt_led_data_types.h"


/**
 * This enumeration defines a set of references to instances
 * of the system's visual indicators.
 */
typedef enum {

	E_LED1 = 0,
	E_LED2 = 1,
	E_LED3 = 2,

	E_RUNNING_INDICATOR = E_LED1,
	E_TEMPERATURE_ALARM_INDICATOR = E_LED2,
	E_TEMPERATURE_STATUS_SENSOR_INDICATOR = E_LED3,

	E_FIRST_VISUAL_INDICATOR = E_LED1,
	E_LAST_VISUAL_INDICATOR = NUM_VISUAL_INDICATORS

} Led_e;



/**
 * Prototypes of public functions for the control of visual
 * indicators of the system. Related to the business logic.
 */
void BSP_VIM_InitVisualIndicators (void);
void BSP_VIM_DeInitVisualIndicators (void);
void BSP_VIM_ActivateRunnigIndicator (void);
void BSP_VIM_DeActivateRuningIndicator (void);
void BSP_VIM_ActivateTemperatureAlarmIndicator (void);
void BSP_VIM_DeActivateTemperatureAlarmIndicator (void);
void BSP_VIM_ActivateTemperatureSensorStatusIndicator (void);
void BSP_VIM_DeActivateTemperatureSensorStatusIndicator (void);
void BSP_VIM_ActivateAllVisualIndicators (void);
void BSP_VIM_DeActivateAllVisualIndicators (void);

/**
 * Prototypes of public functions for the control of visual
 * indicators of the system, They use references to the instances
 * in a generic way
 */
void BSP_VIM_LedOn (Led_e led);
void BSP_VIM_LedOff (Led_e led);
void BSP_VIM_LedToggle (Led_e led);
LedState_t BSP_VIM_GetLedState (Led_e led);

#endif /* __M_BSP_STM32F4_LEDS_H__ */
