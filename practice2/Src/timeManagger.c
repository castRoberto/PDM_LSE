/*
 * timeManagger.c
 *
 *  Created on: Mar 7, 2024
 *      Author: operador
 */


#include "timeManagger.h"

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
