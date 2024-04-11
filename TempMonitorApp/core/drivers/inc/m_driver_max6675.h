/*
 * m_driver_max6675.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_DRIVER_MAX6675_H__
#define __M_DRIVER_MAX6675_H__

#include <stdint.h>

#include "m_driver_max6675_hal_port.h"
#include "m_bsp_stm32_hardware_config.h"


#define MAX6675_DATA_SIZE_BYTES 2
#define TEMP_BYTE_H 0
#define TEMP_BYTE_L 1
#define TEMP_OFFSET_BITS 3
#define TEMP_OFFSET_BITS_H 8

#define SENSOR_STATE_MASK 0x01
#define SENSOR_STATE_OFFSET_BITS 2


typedef enum {

	E_SELECTED = 0,
	E_NO_SELECTED = 1,

} SsState_e;


void MAX6675_updateDataRaw (Max6675_Port_t* port);
float MAX6675_getTemperature (void);
uint8_t MAX6675_getSensorStatus ();

#endif /* __M_DRIVER_MAX6675_H__ */
