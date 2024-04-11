/*
 * m_bsp_stm32f4.c
 *
 *  Created on: Mar 21, 2024
 *      Author: recastrobeltran
 */

#include "m_bsp_stm32f4.h"


/**
 * @brief Provides a tick value in millisecond.
 * @note This function is declared as _weak to be overwritten in case of other
 * 	     implementations in user file
 * @retval tick value
 */
uint32_t BSP_GetCurrentTime (void) {

	return HAL_GetTick ();

}
