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
 * @file ConfigurationConsts.h
 * @brief Definition of constants
 *
 * Package where all the operating constants of the
 * system are defined
 *
 * @author Roberto Castro
 * @date March 09 2024
 *
 */
#ifndef __CONFIGURATION_CONSTS__
#define __CONFIGURATION_CONSTS__

//===========================================================================
//============================== Leds Settings ==============================
//===========================================================================

/**
 * Define the number of LEDs you want to control
 */
#define NUM_LEDS 3

/**
 * Constants to establish the oscillation period and
 * its duty cycle
 */
#define PERIOD_1000MS 500
#define PERIOD_200MS  100
#define PERIOD_100MS  50


#endif /* __CONFIGURATION_CONSTS__ */
