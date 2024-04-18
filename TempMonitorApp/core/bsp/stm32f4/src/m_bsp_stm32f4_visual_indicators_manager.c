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
 * @file m_bsp_stm32f4_visual_indicators_manager.c
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


#include "m_bsp_stm32f4_visual_indicators_manager.h"

#include "stm32f4xx_hal.h"


/**
 * This structure models a private instance of a
 * visual indicator, containing its pin, port and
 * assigned state.
 */
typedef struct {

	uint32_t pin;
	GPIO_TypeDef* port;
	LedState_t state;

} VisualIndicator_t;



/**
 * Array with all the instances of visual indicators of the system,
 * adding a new LED implies adding it to this structure as well.
 */
static VisualIndicator_t VISUAL_INDICATORS [NUM_VISUAL_INDICATORS] = {

		(VisualIndicator_t) {
				.pin = RUNNING_INDICATOR,
				.port = RUNNING_INDICATOR_PORT,
				.state = E_LED_RESET,
		},

		(VisualIndicator_t) {
				.pin = TEMPERATURE_ALARM_INDICATOR,
				.port = TEMPERATURE_ALARM_INDICATOR_PORT,
				.state = E_LED_RESET,
		},

		(VisualIndicator_t) {
				.pin = TEMPERATURE_STATUS_SENSOR_INDICATOR,
				.port = TEMPERATURE_STATUS_SENSOR_INDICATOR_PORT,
				.state = E_LED_RESET,
		},

};


/**
 * @brief Initialization of visual indicator
 *
 * Function that configures a visual indicator or LED
 * at a low level.
 *
 *
 * @param visualIndicator: Visual indicator instance
 *
 * @return None
 */
static void initVisualIndicator (const VisualIndicator_t* const visualIndicator) {

	if (visualIndicator != NULL) {

		GPIO_InitTypeDef  GPIO_InitStruct;

		/* Enable the GPIO_LED Clock */
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/* Configure the GPIO_LED pin */
		GPIO_InitStruct.Pin = visualIndicator->pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

		HAL_GPIO_Init (visualIndicator->port, &GPIO_InitStruct);

		HAL_GPIO_WritePin
			(visualIndicator->port, visualIndicator->pin, GPIO_PIN_RESET);

	}

}


/**
 * @brief  DeInit LEDs.
 *
 * @param  Led: LED to be de-init.
 *
 * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
 */
static void deInitVisualIndicator (const VisualIndicator_t* const visualIndicator) {

	if (visualIndicator != NULL) {

		/* Turn off LED */
		HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_RESET);

		HAL_GPIO_DeInit (visualIndicator->port, visualIndicator->pin);

	}

}


/**
 * @brief Initialization of visual indicators
 *
 * Function that initializes all internal visual indicator
 * instances contained in "VISUAL_INDICATORS".
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_InitVisualIndicators (void) {

	for (int8_t i = E_FIRST_VISUAL_INDICATOR; i < E_LAST_VISUAL_INDICATOR; i++) {

		initVisualIndicator (&VISUAL_INDICATORS [i]);

	}

}


/**
 * @brief uninitializes of visual indicators
 *
 * Function that uninitializes all internal visual indicator
 * instances contained in "VISUAL_INDICATORS".
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_DeInitVisualIndicators (void) {

	for (int8_t i = E_FIRST_VISUAL_INDICATOR; i < E_LAST_VISUAL_INDICATOR; i++) {

		deInitVisualIndicator (&VISUAL_INDICATORS[i]);

	}

}


/**
 * @brief Activate running visual indicator
 *
 * Function that activates the internal instance of the
 * visual indicator for running status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_ActivateRunnigIndicator (void) {

	BSP_VIM_LedOn (E_RUNNING_INDICATOR);

}


/**
 * @brief dectivate running visual indicator
 *
 * Function that deactivates the internal instance of the
 * visual indicator for running status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_DeActivateRuningIndicator (void) {

	BSP_VIM_LedOff (E_RUNNING_INDICATOR);

}


/**
 * @brief Activate temperature alert visual indicator
 *
 * Function that activates the internal instance of the
 * visual indicator for temperature alert status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_ActivateTemperatureAlarmIndicator (void) {

	BSP_VIM_LedOn (E_TEMPERATURE_ALARM_INDICATOR);

}


/**
 * @brief deactivate temperature alert visual indicator
 *
 * Function that deactivates the internal instance of the
 * visual indicator for temperature alert status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_DeActivateTemperatureAlarmIndicator (void) {

	BSP_VIM_LedOff (E_TEMPERATURE_ALARM_INDICATOR);

}


/**
 * @brief Activate temperature sensor status visual indicator
 *
 * Function that activates the internal instance of the
 * visual indicator for temperature sensor status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_ActivateTemperatureSensorStatusIndicator (void) {

	BSP_VIM_LedOn (E_TEMPERATURE_STATUS_SENSOR_INDICATOR);

}


/**
 * @brief deactivate temperature sensor status visual indicator
 *
 * Function that deactivates the internal instance of the
 * visual indicator for temperature sensor status.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_DeActivateTemperatureSensorStatusIndicator (void) {

	BSP_VIM_LedOff (E_TEMPERATURE_STATUS_SENSOR_INDICATOR);

}


/**
 * @brief Activate all visual indicators
 *
 * Function that activates the internal instances of the
 * all visual indicator.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_ActivateAllVisualIndicators (void) {

	BSP_VIM_ActivateRunnigIndicator();
	BSP_VIM_ActivateTemperatureAlarmIndicator();
	BSP_VIM_ActivateTemperatureSensorStatusIndicator();

}


/**
 * @brief deactivate all visual indicators
 *
 * Function that deactivates the internal instances of the
 * all visual indicator.
 *
 *
 * @param None
 *
 * @return None
 */
void BSP_VIM_DeActivateAllVisualIndicators (void) {

	BSP_VIM_DeActivateRuningIndicator ();
	BSP_VIM_DeActivateTemperatureAlarmIndicator ();
	BSP_VIM_DeActivateTemperatureSensorStatusIndicator ();

}


/**
 * @brief Activate a specific instance
 *
 * This function activates an indicated visual
 * indicator specified by the input argument.
 *
 *
 * @param led: Reference to visual indicator
 *
 * @return None
 */
void BSP_VIM_LedOn (Led_e led) {

	if (led >= E_FIRST_VISUAL_INDICATOR && led <= E_LAST_VISUAL_INDICATOR) {

		VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

		HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_SET);

		visualIndicator->state = E_LED_SET;

	}

}


/**
 * @brief deactivate a specific instance
 *
 * This function deactivates an indicated visual
 * indicator specified by the input argument.
 *
 *
 * @param led: Reference to visual indicator
 *
 * @return None
 */
void BSP_VIM_LedOff (Led_e led) {

	if (led >= E_FIRST_VISUAL_INDICATOR && led <= E_LAST_VISUAL_INDICATOR) {

		VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

		HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_RESET);

		visualIndicator->state = E_LED_RESET;

	}

}


/**
 * @brief Toggle state of a specific instance
 *
 * This function Toggle state an indicated visual
 * indicator specified by the input argument.
 *
 *
 * @param led: Reference to visual indicator
 *
 * @return None
 */
void BSP_VIM_LedToggle (Led_e led) {

	if (led >= E_FIRST_VISUAL_INDICATOR && led <= E_LAST_VISUAL_INDICATOR) {

		VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

		HAL_GPIO_TogglePin (visualIndicator->port, visualIndicator->pin);

		visualIndicator->state = !visualIndicator->state;

	}

}


/**
 * @brief Returns the state of a visual indicator
 *
 * This function returns the current state of a visual
 * indicator indicated by the input argument.
 *
 *
 * @param led: Reference to visual indicator
 *
 * @return state: Current status of a visual indicator
 */
LedState_t BSP_VIM_GetLedState (Led_e led) {

	LedState_t state = E_UNKNOWN_VI_STATE;

	if (led >= E_FIRST_VISUAL_INDICATOR && led <= E_LAST_VISUAL_INDICATOR) {

		VisualIndicator_t visualIndicator = VISUAL_INDICATORS[led];

		state = visualIndicator.state;

	}

	return state;

}
