/*
 * m_BSP_PBM_stm32f4_buttons.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */


#include "m_bsp_stm32f4_push_buttons_manager.h"

//TODO: DOCUMENTA
static const Button_t BUTTONS [NUM_VISUAL_INDICATORS] = {

		(Button_t) {
				.pin = START_BUTTON,
				.port = START_BUTTON_PORT
		}

};


static void initButton (const Button_t* const button) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable the BUTTON Clock */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* Configure Button pin as input */
	GPIO_InitStruct.Pin = button->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(button->port, &GPIO_InitStruct);

}


static void deInitButton (const Button_t* const button) {

	HAL_GPIO_DeInit (button->port, button->pin);

}


void BSP_PBM_InitButtons (void) {

	for (int8_t i = 0; i < NUM_BUTTONS; i++) {

		initButton (&BUTTONS[i]);

	}

}


void BSP_PBM_DeInitButtons (void) {

	for (int8_t i = 0; i < NUM_BUTTONS; i++) {

		deInitButton (&BUTTONS[i]);

	}

}


ButtonState_t BSP_PBM_ReadStartStopButton (void) {

	return BSP_PBM_ReadButton (E_START_STOP_BUTTON);

}


ButtonState_t BSP_PBM_ReadButton (Button_e button) {

	Button_t m_button = BUTTONS[button];

	return HAL_GPIO_ReadPin(m_button.port, m_button.pin);

}

