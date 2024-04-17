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
 * @file m_app_temp_monitor_core.h
 * @brief Application core
 *
 * Module to execute the business logic of the application, calculates the
 * inputs for the main state machine, brings together the highest level
 * functions of the system
 *
 * @author Roberto Castro
 * @date April 14 2024
 *
 */

#ifndef __M_APP_TEMP_MONITOR_CORE_H__
#define __M_APP_TEMP_MONITOR_CORE_H__

#include "m_bsp_stm32f4.h"

#include "m_ddt_machine_state_inputs.h"



/**
 * Public functions of the application core
 */
void APP_TMC_runningIndicator (void);

ConfigResult_t APP_TMC_setup (void);

DataAcquisitionResult_t APP_TMC_dataAcquisition (void);

DataProcessingResult_t APP_TMC_dataProcessing (void);

DataShowResult_t APP_TMC_dataShow (void);


#endif /* __M_APP_TEMP_MONITOR_CORE_H__ */
