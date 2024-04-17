/*
 * m_bsp_stm32f4_buttons.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_BSP_STM32F4_BUTTONS_H__
#define __M_BSP_STM32F4_BUTTONS_H__

#include <stdint.h>

#include "stm32f4xx_hal.h"

#include "m_bsp_stm32_hardware_config.h"
#include "m_ddt_button_data_types.h"


typedef enum {

	E_BUTTON1 = 0,

	E_START_STOP_BUTTON = E_BUTTON1,

} Button_e;


typedef struct {

	uint32_t pin;
	GPIO_TypeDef* port;

} Button_t;


void BSP_PBM_InitButtons (void);
void BSP_PBM_DeInitButtons (void);
ButtonState_t BSP_PBM_ReadStartStopButton (void);

ButtonState_t BSP_PBM_ReadButton (Button_e button);

#endif /* __M_BSP_STM32F4_BUTTONS_H__ */
