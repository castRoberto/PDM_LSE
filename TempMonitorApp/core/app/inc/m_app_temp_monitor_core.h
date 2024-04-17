/*
 * m_app_temp_monitor_core.h
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#ifndef __M_APP_TEMP_MONITOR_CORE_H__
#define __M_APP_TEMP_MONITOR_CORE_H__

#include "m_bsp_stm32f4.h"

#include "m_ddt_machine_state_inputs.h"



void APP_TMC_runningIndicator (void);

ConfigResult_t APP_TMC_setup (void);

DataAcquisitionResult_t APP_TMC_dataAcquisition (void);

DataProcessingResult_t APP_TMC_dataProcessing (void);

DataShowResult_t APP_TMC_dataShow (void);


#endif /* __M_APP_TEMP_MONITOR_CORE_H__ */
