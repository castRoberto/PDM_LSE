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
 * @file m_driver_max6675.h
 * @brief Driver for the MAX6675 module
 *
 * This driver allows you to manage low-level communications with the
 * MAX6675 temperature measurement module. It has complete management
 * of the byte frame format, which allows you to know the real temperature
 * value and the connection status of the transducer.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DRIVER_MAX6675_H__
#define __M_DRIVER_MAX6675_H__

#include <stdint.h>
#include <stddef.h>

#include "m_driver_max6675_hal_port.h"


/**
 * K-type transducer connection states
 */
typedef enum {

	E_SELECTED = 0,
	E_NO_SELECTED = 1,

} SsState_e;



/**
 * Public driver functions for updating and requesting
 * temperature data
 */
void MAX6675_updateDataRaw (Max6675_Port_t* port);
float MAX6675_getTemperature (void);
uint8_t MAX6675_getSensorStatus (void);

#endif /* __M_DRIVER_MAX6675_H__ */
