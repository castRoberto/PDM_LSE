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
 * @file LedManager.h
 * @brief LED manager
 *
 * Package for the initialization and management of LED states
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */

#ifndef __LED_MANAGER_H__
#define __LED_MANAGER_H__

#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h"
#include "ConfigurationConsts.h"

/**
 * Structure that contains all the information necessary
 * to control an LED
 */
typedef struct {

	Led_TypeDef led;
	delay_t delay;
	tick_t defoultWait;

} ledData_t;


/**
 * @brief LED data initializer
 *
 * Initializes the data of all the system LEDs
 *
 * @param ledsData: Time structure
 *
 * @return void.
 */
void LM_ledsDataInit (ledData_t* ledsData);


/**
 * @brief State validator
 *
 * Function to manage by survey if the LEDs can be switched
 * in value
 *
 * @param ledsData: Time structure
 *
 * @return void.
 */
void LM_manageLedStates (ledData_t* ledsData);

#endif /* __LED_MANAGER_H__ */
