/*
 * m_bsp_stm32f4_leds.h
 *
 *  Created on: Mar 21, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_BSP_STM32F4_LEDS_H__
#define __M_BSP_STM32F4_LEDS_H__

#include <stdint.h>

#include "stm32f4xx_hal.h"

#include "m_bsp_stm32_hardware_config.h"
#include "m_ddt_led_data_types.h"


typedef enum {

	E_LED1 = 0,
	E_LED2 = 1,
	E_LED3 = 2,

	E_RUNNING_INDICATOR = E_LED1,
	E_TEMPERATURE_ALARM_INDICATOR = E_LED2,
	E_TEMPERATURE_STATUS_SENSOR_INDICATOR = E_LED3

} Led_e;


typedef struct {

	uint32_t pin;
	GPIO_TypeDef* port;
	LedState_t state;

} VisualIndicator_t;


void BSP_VIM_InitVisualIndicators (void);
void BSP_VIM_DeInitVisualIndicators (void);
void BSP_VIM_ActivateRunnigIndicator (void);
void BSP_VIM_DeActivateRuningIndicator (void);
void BSP_VIM_ActivateTemperatureAlarmIndicator (void);
void BSP_VIM_DeActivateTemperatureAlarmIndicator (void);
void BSP_VIM_ActivateTemperatureSensorStatusIndicator (void);
void BSP_VIM_DeActivateTemperatureSensorStatusIndicator (void);

void BSP_VIM_LedOn (Led_e led);
void BSP_VIM_LedOff (Led_e led);
void BSP_VIM_LedToggle (Led_e led);
LedState_t BSP_VIM_GetLedState (Led_e led);

#endif /* __M_BSP_STM32F4_LEDS_H__ */
