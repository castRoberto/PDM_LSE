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
 * @file LedManager.c
 * @brief Non-blocking delay manipulation
 *
 * This implementation file provides an abstraction for manipulating
 * leds through function calls.
 *
 * @author Roberto Enrique Castro Beltran
 * @date March 09 2024
 *
 */

#include <stddef.h>

#include "LedManager.h"


void LM_ledsDataInit (ledData_t* ledsData) {

	if (ledsData != NULL) {

		for (int8_t i = 0; i < NUM_LEDS; i++) {

			BSP_LED_Init (ledsData[i].led);

			TM_delayInit (&(ledsData[i].delay), ledsData[i].defoultWait);

		}

	}

}


void LM_manageLedStates (ledData_t* ledsData) {

	if (ledsData != NULL) {

		for (int8_t i = 0; i < NUM_LEDS; i++) {

			if (TM_delayRead (&(ledsData[i].delay))) {

				BSP_LED_Toggle (ledsData[i].led);

			}

		}

	}

}
