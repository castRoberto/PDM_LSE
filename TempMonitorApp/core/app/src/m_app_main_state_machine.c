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
 * @file m_app_main_state_machine.c
 * @brief Finite state machine to manage the application
 *
 * This implementation file provides an abstraction to handle the internal
 * states of the electric motor temperature monitoring application.
 *
 * @author Roberto Castro
 * @date April 14 2024
 *
 */

#include "m_app_main_state_machine.h"

#include "m_app_temp_monitor_core.h"
#include "m_lib_util_debounce_state_machine.h"



/**
 * States for the main state machine
 */
typedef enum {

	E_CONFIG_STATE 		= 1,
	E_FAILURE_STATE 	= 2,
	E_IDLE_STATE 		= 3,
	E_ACTIVE_STATE 		= 4,
	E_DATA_ACQ_STATE 	= 5,
	E_DATA_PROC_STATE 	= 6,
	E_DATA_SHOW_STATE 	= 7,

} MainFSM_States_t;


/**
 * Internal state machine variables
 */
static MainFSM_States_t currentState;
static DebouncePinData_t startStopDebounce = { 0 };


/**
 * @brief Initialize the state machine
 *
 * Sets the initial state of the main fsm, defines the system
 * start and stop pin, and initializes the state machine to
 * handle start and stop pin debounces.
 *
 * @param None.
 *
 * @return None.
 */
void APP_MSM_init (void) {

	currentState = E_CONFIG_STATE;

	startStopDebounce.pin = E_START_STOP_BUTTON;

	LIB_DSM_debounceFsmInit(&startStopDebounce);

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
void APP_MSM_update (void) {

	LIB_DSM_debounceFsmUpdate(&startStopDebounce);

	switch (currentState) {

		//-----------------------------------------------------------//
		case E_CONFIG_STATE: {

			if (APP_TMC_setup() == E_NO_ERROR) {

				currentState = E_IDLE_STATE;

			} else {

				currentState = E_FAILURE_STATE;

			}

			break;

		}

		//-----------------------------------------------------------//
		case E_FAILURE_STATE: {

			if (RECONFIGURE_SYSTEM) {

				currentState = E_CONFIG_STATE;

			} else {

				BSP_VIM_ActivateAllVisualIndicators ();

			}

			break;

		}

		//-----------------------------------------------------------//
		case E_IDLE_STATE: {

			if (LIB_DSM_debounceReadKey(&startStopDebounce)) {

				currentState = E_ACTIVE_STATE;

			}

			break;

		}

		//-----------------------------------------------------------//
		case E_ACTIVE_STATE: {

			if (LIB_DSM_debounceReadKey(&startStopDebounce)) {

				currentState = E_IDLE_STATE;

			} else {

				currentState = E_DATA_ACQ_STATE;

			}

			APP_TMC_runningIndicator ();

			break;

		}

		//-----------------------------------------------------------//
		case E_DATA_ACQ_STATE: {

			if (APP_TMC_dataAcquisition() == E_DATA_OK) {

				currentState = E_DATA_PROC_STATE;

			} else {

				currentState = E_ACTIVE_STATE;

			}

			break;

		}

		//-----------------------------------------------------------//
		case E_DATA_PROC_STATE: {

			if (APP_TMC_dataProcessing() == E_PROC_OK) {

				currentState = E_DATA_SHOW_STATE;

			} else {

				currentState = E_DATA_ACQ_STATE;

			}

			break;

		}

		//-----------------------------------------------------------//
		case E_DATA_SHOW_STATE: {

			APP_TMC_dataShow();

			currentState = E_ACTIVE_STATE;

			break;

		}

		//-----------------------------------------------------------//
		default: {

			APP_MSM_init ();
			break;

		}

	}

}
