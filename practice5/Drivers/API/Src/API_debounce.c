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
 * @file API_debounce.c
 * @brief Finite state machine for bounce management
 *
 * This implementation file provides an abstraction for handling debounces
 * in physical pushbuttons on the board.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#include "API_debounce.h"

/**
 * States for the debounce state machine
 */
typedef enum {

	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING

} DebounceState_t;


/**
 * Internal state machine variables
 */
static delay_t debounceDelay = {};
static DebounceState_t currentState;
static bool_t keyPressed = false;

/**
 * State change messages
 */
static const uint8_t FALLING_MSG[] = "[API_DEBOUNCE.UPDATE]: Falling edge\r\n";
static const uint8_t RISING_MSG[] = "[API_DEBOUNCE.UPDATE]: Rising edge\r\n";


/**
 * @brief Activate output
 *
 * Activate the output of the state machine
 *
 * @param None
 *
 * @return None
 */
static void buttonPressed (void) {

    keyPressed = true;

}


/**
 * @brief Disable output
 *
 * Disable the output of the state machine
 *
 * @param None
 *
 * @return None
 */
static void buttonReleased (void) {

    keyPressed = false;

}


/**
 * @brief Get method
 *
 * Get method to read the button state
 *
 * @param None.
 *
 * @return returnValue : bool_t; Button was pressed.
 */
bool_t API_debounceReadKey (void) {

	bool_t returnValue = keyPressed;

	if (keyPressed) { buttonReleased (); }

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
void API_debounceFsmInit (void) {

	currentState = BUTTON_UP;
	/* Initialize API delay */
	API_delayInit (&debounceDelay, DEBOUNCE_STABILIZATION_TIME_40MS);

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
void API_debounceFsmUpdate (void) {

	uint8_t buttonState = BSP_PB_GetState (BUTTON_USER);

	switch (currentState) {

		case BUTTON_UP: {

			if (buttonState) { currentState = BUTTON_FALLING; }
			break;

		}

		case BUTTON_FALLING: {

			if (API_delayRead (&debounceDelay)) {

				currentState = buttonState? BUTTON_DOWN : BUTTON_UP;

				if (currentState == BUTTON_DOWN) {

					buttonPressed ();
					API_uartSendString ((uint8_t*)FALLING_MSG);

				}

			}

			break;

		}

		case BUTTON_DOWN: {

			if (!buttonState) {	currentState = BUTTON_RAISING;	}
			break;
		}

		case BUTTON_RAISING: {

			if (API_delayRead (&debounceDelay)) {

				currentState = (!buttonState)? BUTTON_UP : BUTTON_DOWN;

				if (currentState == BUTTON_UP) {

					buttonReleased ();
					API_uartSendString ((uint8_t*)RISING_MSG);

				}

			}

			break;

		}

		default: {

			API_debounceFsmInit ();
			break;

		}

	}

}


