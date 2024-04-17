/*
 * m_ddt_machne_state_inputs.h
 *
 *  Created on: Apr 14, 2024
 *      Author: rober
 */

#ifndef __M_DDT_MACHNE_STATE_INPUTS_H__
#define __M_DDT_MACHNE_STATE_INPUTS_H__


typedef enum {

	E_ERROR = 0,
	E_NO_ERROR = 1,

} ConfigResult_t;


typedef enum {

	E_DATA_OK = 0,
	E_NO_DATA = 1,

} DataAcquisitionResult_t;


typedef enum {

	E_PROC_OK = 0,
	E_ERROR_PROC = 1,

} DataProcessingResult_t;


typedef enum {

	E_SHOW_OK = 0,
	E_ERROR_SHOW = 1,

} DataShowResult_t;



#endif /* __M_DDT_MACHNE_STATE_INPUTS_H__ */
