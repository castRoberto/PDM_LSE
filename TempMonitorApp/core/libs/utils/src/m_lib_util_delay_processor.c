/******************************************************************************
 * Copyright (C) 2024 by Roberto Enrique Castro Beltran
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Roberto Castro are not liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file m_lib_util_delay.c
 * @brief Non-blocking delay manipulation
 *
 * This implementation file provides an abstraction for manipulating
 * non-blocking delays through function calls.
 *
 * @author Roberto Enrique Castro Beltran
 * @date March 09 2024
 *
 */

#include "m_lib_util_delay_processor.h"

#include "m_bsp_stm32f4.h"


/**
 * @brief Check elapsed time
 *
 * Function that checks if for a given time structure,
 * the timeout has been met
 *
 *
 * @param now: Current time
 * @param delay: Time structure
 *
 * @return timeOut.
 */
static bool_t isTimeOut (tick_t now, delay_t* delay) {

	return ((now - delay->startTime) >= delay->duration);

}


/**
 * @brief Time initializer
 *
 * Function that initializes a time structure with
 * default values
 *
 *
 * @param delay: Time structure
 * @param duration: Default wait
 *
 * @return void.
 */
void LIB_DP_delayInit( delay_t* delay, tick_t duration ) {

	if (delay != NULL) {

		*delay = (delay_t) {
			.startTime = 0,
			.duration = (duration > 0)? duration : DEFAULT_PERIOD_10MS,
			.running = false
		};

	}

}


/**
 * @brief Check elapsed time
 *
 * Function that checks if for a given time structure,
 * the timeout has been met
 *
 *
 * @param delay: Time structure
 *
 * @return timeOut.
 */
bool_t LIB_DP_delayRead( delay_t * delay ) {

	bool_t timeOut = false;

	if (delay != NULL) {

		tick_t currentTime = BSP_GetCurrentTime ();

		if (!(delay->running)) {

			delay->running = true;

			delay->startTime = currentTime;

		} else {

			if ( isTimeOut (currentTime, delay) ) {

				timeOut = true;

				delay->running = false;

			}

		}

	}

	return timeOut;

}


/**
 * @brief Delay updater
 *
 * This function updates the timeout duration
 *
 *
 * @param delay: Time structure
 * @param duration: New waiting time
 *
 * @return void.
 */
void LIB_DP_delayWrite( delay_t * delay, tick_t duration ) {

	if ((delay != NULL) && (duration > 0)) {

		delay->duration = duration;

	}

}
