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
 * @file m_ddt_machne_state_inputs.h
 * @brief Defining of SFM inputs
 *
 * Definition of the input values for the main finite state
 * machine of the application
 *
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DDT_MACHNE_STATE_INPUTS_H__
#define __M_DDT_MACHNE_STATE_INPUTS_H__



/**
 * Possible results when running the system
 * configuration routine
 */
typedef enum {

	E_ERROR = 0,
	E_NO_ERROR = 1,

} ConfigResult_t;


/**
 * Possible results when running the system
 * data acquisition routine
 */
typedef enum {

	E_DATA_OK = 0,
	E_NO_DATA = 1,

} DataAcquisitionResult_t;


/**
 * Possible results when running the system
 * data processing routine
 */
typedef enum {

	E_PROC_OK = 0,
	E_ERROR_PROC = 1,

} DataProcessingResult_t;


/**
 * Possible results when running the system
 * data display routine
 */
typedef enum {

	E_SHOW_OK = 0,
	E_ERROR_SHOW = 1,

} DataShowResult_t;



#endif /* __M_DDT_MACHNE_STATE_INPUTS_H__ */
