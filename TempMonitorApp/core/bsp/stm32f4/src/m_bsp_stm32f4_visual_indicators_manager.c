/*
 * m_bsp_stm32f4_leds.c
 *
 *  Created on: Mar 21, 2024
 *      Author: recastrobeltran
 */


#include <m_bsp_stm32f4_visual_indicators_manager.h>

//TODO: DOCUMENTA
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


//TODO: DOCUMENTA
static void initVisualIndicator (const VisualIndicator_t* const visualIndicator) {

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

//TODO: DOCUMENTA
/**
 * @brief  DeInit LEDs.
 * @param  Led: LED to be de-init.
 *   This parameter can be one of the following values:

 * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
 */
static void deInitVisualIndicator (const VisualIndicator_t* const visualIndicator) {

	/* Turn off LED */
	HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_RESET);

	HAL_GPIO_DeInit (visualIndicator->port, visualIndicator->pin);

}


//TODO: DOCUMENTA
void BSP_VIM_InitVisualIndicators (void) {

	for (int8_t i = E_FIRST_VISUAL_INDICATOR; i < E_LAST_VISUAL_INDICATOR; i++) {

		initVisualIndicator (&VISUAL_INDICATORS [i]);

	}

}


//TODO: DOCUMENTA
void BSP_VIM_DeInitVisualIndicators (void) {

	for (int8_t i = E_FIRST_VISUAL_INDICATOR; i < E_LAST_VISUAL_INDICATOR; i++) {

		deInitVisualIndicator (&VISUAL_INDICATORS[i]);

	}

}


//TODO: DOCUMENTA
void BSP_VIM_ActivateRunnigIndicator (void) {

	BSP_VIM_LedOn (E_RUNNING_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_DeActivateRuningIndicator (void) {

	BSP_VIM_LedOff (E_RUNNING_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_ActivateTemperatureAlarmIndicator (void) {

	BSP_VIM_LedOn (E_TEMPERATURE_ALARM_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_DeActivateTemperatureAlarmIndicator (void) {

	BSP_VIM_LedOff (E_TEMPERATURE_ALARM_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_ActivateTemperatureSensorStatusIndicator (void) {

	BSP_VIM_LedOn (E_TEMPERATURE_STATUS_SENSOR_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_DeActivateTemperatureSensorStatusIndicator (void) {

	BSP_VIM_LedOff (E_TEMPERATURE_STATUS_SENSOR_INDICATOR);

}


//TODO: DOCUMENTA
void BSP_VIM_LedOn (Led_e led) {

	VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

	HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_SET);

	visualIndicator->state = E_LED_SET;

}


//TODO: DOCUMENTA
void BSP_VIM_LedOff (Led_e led) {

	VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

	HAL_GPIO_WritePin (visualIndicator->port, visualIndicator->pin, GPIO_PIN_RESET);

	visualIndicator->state = E_LED_RESET;

}


//TODO: DOCUMENTA
void BSP_VIM_LedToggle (Led_e led) {

	VisualIndicator_t* visualIndicator = &VISUAL_INDICATORS[led];

	HAL_GPIO_TogglePin (visualIndicator->port, visualIndicator->pin);

	visualIndicator->state = !visualIndicator->state;

}


LedState_t BSP_VIM_GetLedState (Led_e led) {

	VisualIndicator_t visualIndicator = VISUAL_INDICATORS[led];

	return visualIndicator.state;

}
