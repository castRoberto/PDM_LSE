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
 * @file m_bsp_stm32f4_buttons.c
 *
 * @brief Push button Manager Module
 *
 * This module acts as a facade for higher level layers that require
 * controlling hardware buttons, therefore exposing functions that
 * contain a business logic context as well as a hardware generalization.
 *
 * @author Roberto Castro
 * @date March 31 2024
 *
 */


#include "m_bsp_stm32f4_push_buttons_manager.h"

#include "stm32f4xx_hal.h"


/**
 * This structure models a private instance
 * of a button, containing its pin and port.
 */
typedef struct {

	uint32_t pin;
	GPIO_TypeDef* port;

} Button_t;



/**
 * Array with all the system button instances, adding
 * a new button implies also adding it to this structure.
 */
static const Button_t BUTTONS [NUM_VISUAL_INDICATORS] = {

		(Button_t) {
				.pin = START_BUTTON,
				.port = START_BUTTON_PORT
		}

};


/**
 * @brief Initialization of push button
 *
 * Function that configures a push button at a low
 * level.
 *
 *
 * @param button: push button instance
 *
 * @return None
 */
static void initButton (const Button_t* const button) {

	if (button != NULL) {

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

}


/**
 * @brief  DeInit BUTTONS.
 *
 * @param  button: BUTTON to be de-init.
 */
static void deInitButton (const Button_t* const button) {

	if (button != NULL) {

		HAL_GPIO_DeInit (button->port, button->pin);

	}

}


/**
 * @brief Initialization of push buttons
 *
 * Function that initializes all internal push button
 * instances contained in "BUTTONS".
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_PBM_InitButtons (void) {

	for (int8_t i = E_FIRST_BUTTON; i < E_LAST_BUTTON; i++) {

		initButton (&BUTTONS[i]);

	}

}


/**
 * @brief uninitializes of push button
 *
 * Function that uninitializes all internal push button
 * instances contained in "BUTTONS".
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_PBM_DeInitButtons (void) {

	for (int8_t i = E_FIRST_BUTTON; i < E_LAST_BUTTON; i++) {

		deInitButton (&BUTTONS[i]);

	}

}


/**
 * @brief Reading the system start and stop button
 *
 * This function queries HAL for the status of the button
 * used to denote the start and stop of the system.
 *
 *
 * @param None
 *
 * @return buttonState: Current state of the start and stop button
 */
ButtonState_t BSP_PBM_ReadStartStopButton (void) {

	return BSP_PBM_ReadButton (E_START_STOP_BUTTON);

}


/**
 * @brief Read a specific button denoted by the reference
 *
 * This function queries the hal for the state of a
 * certain button defined by the reference
 *
 *
 * @param None
 *
 * @return buttonState: Current state of the specified button
 */
ButtonState_t BSP_PBM_ReadButton (Button_e button) {

	ButtonState_t state = E_UNKNOWN_PB_STATE;

	if (button >= E_FIRST_BUTTON && button <= E_LAST_BUTTON) {

		Button_t m_button = BUTTONS[button];

		state = HAL_GPIO_ReadPin(m_button.port, m_button.pin);

	}

	return state;

}

