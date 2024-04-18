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
 * @file m_lib_util_debounce_machine_state.c
 * @brief Finite state machine for bounce management
 *
 * This implementation file provides an abstraction for handling debounces
 * in physical pushbuttons on the board.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#include "m_lib_util_debounce_state_machine.h"

#include "m_ddt_button_data_types.h"


/*
 * Rebound stabilization time
 */
#define DEBOUNCE_STABILIZATION_TIME_40MS 40


/**
 * @brief Activate output
 *
 * Activate the output of the state machine
 *
 * @param debounce
 *
 * @return None
 */
static void buttonPressed (DebouncePinData_t* debounce) {

	if (debounce != NULL) {

		debounce->keyPressed = true;

	}

}


/**
 * @brief Disable output
 *
 * Disable the output of the state machine
 *
 * @param debounce
 *
 * @return None
 */
static void buttonReleased (DebouncePinData_t* debounce) {

	if (debounce != NULL) {

		debounce->keyPressed = false;

	}

}


/**
 * @brief Get method
 *
 * Get method to read the button state
 *
 * @param debounce.
 *
 * @return returnValue : bool_t; Button was pressed.
 */
bool_t LIB_DSM_debounceReadKey (DebouncePinData_t* debounce) {

	bool_t returnValue = false;

	if (debounce != NULL) {

		returnValue = debounce->keyPressed;

		if (debounce->keyPressed) { buttonReleased (debounce); }

	}

	return returnValue;

}


/**
 * @brief Initialize the state machine
 *
 * Sets the initial state of the state machine and its
 * non-blocking delay structure.
 *
 * @param void.
 *
 * @return void.
 */
void LIB_DSM_debounceFsmInit (DebouncePinData_t* debounce) {

	if (debounce != NULL) {

		debounce->currentState = BUTTON_UP;
		/* Initialize API delay */
		LIB_DP_delayInit(&debounce->debounceDelay, DEBOUNCE_STABILIZATION_TIME_40MS);

	}

}


/**
 * @brief Update the state machine
 *
 * Function to update the states and outputs of the
 * state machine
 *
 * @param None
 *
 * @return None
 */
void LIB_DSM_debounceFsmUpdate (DebouncePinData_t* debounce) {

	if (debounce != NULL) {

		ButtonState_t buttonState = BSP_PBM_ReadButton(debounce->pin);

		switch (debounce->currentState) {

			case BUTTON_UP: {

				if (buttonState) { debounce->currentState = BUTTON_FALLING; }
				break;

			}

			case BUTTON_FALLING: {

				if (LIB_DP_delayRead (&debounce->debounceDelay)) {

					debounce->currentState = buttonState? BUTTON_DOWN : BUTTON_UP;

					if (debounce->currentState == BUTTON_DOWN) {

						buttonPressed (debounce);

					}

				}

				break;

			}

			case BUTTON_DOWN: {

				if (!buttonState) {	debounce->currentState = BUTTON_RAISING;	}
				break;
			}

			case BUTTON_RAISING: {

				if (LIB_DP_delayRead (&debounce->debounceDelay)) {

					debounce->currentState = (!buttonState)? BUTTON_UP : BUTTON_DOWN;

					if (debounce->currentState == BUTTON_UP) {

						buttonReleased (debounce);

					}

				}

				break;

			}

			default: {

				LIB_DSM_debounceFsmInit (debounce);
				break;

			}

		}

	}

}


