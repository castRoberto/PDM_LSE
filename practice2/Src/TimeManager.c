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
 * @file TimeManager.c
 * @brief Non-blocking delay manipulation
 *
 * This implementation file provides an abstraction for manipulating
 * non-blocking delays through function calls.
 *
 * @author Roberto Enrique Castro Beltran
 * @date March 09 2024
 *
 */
#include "TimeManager.h"

void TM_delayInit( delay_t * delay, tick_t duration ) {

	*delay = (delay_t) {
		.startTime = 0,
		.duration = duration,
		.running = false
	};

}

bool_t TM_delayRead( delay_t * delay ) {

	bool_t timeOut = false;

	tick_t currentTime = HAL_GetTick ();

	if (!(delay->running)) {

		delay->running = true;

		delay->startTime = currentTime;

	} else {

		if ((currentTime - delay->startTime) >= delay->duration) {

			timeOut = true;

			delay->running = false;

		}

	}

	return timeOut;

}

void TM_delayWrite( delay_t * delay, tick_t duration ) {

	if (delay->duration >= 0) {

		delay->duration = duration;

	}

}
