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
 *
 * @author Roberto Castro
 * @date April 14 2024
 *
 */


#include "m_app_temp_monitor_core.h"

#include "m_bsp_stm32_system_config.h"

#include "m_lib_util_delay_processor.h"
#include "m_lib_util_temp_converter.h"

#include "m_ddt_temperature_data_types.h"
#include "m_ddt_machine_state_inputs.h"



/**
 * Internal variables of the application core
 */
static delay_t runnigIndicatorDelay 	= { NULL_VALUE };
static delay_t sampligRateDelay 		= { NULL_VALUE };

static TemperatureData_t tempData 		= { NULL_VALUE };
static TemperatureData_t tempDataKelvin = { NULL_VALUE };
static TemperatureData_t tempDataFaren	= { NULL_VALUE };



/**
 * @brief Copy temperature data from one location to another
 *
 * Given two pointers to temperature data structures,
 * copy the source fields to des.
 *
 *
 * @param source Pointer to original temp data.
 * @param des Pointer to destinity of temp data.
 *
 * @return None.
 */
static void copyTempData (TemperatureData_t* source, TemperatureData_t* des) {

	if (source != NULL && des != NULL) {

		des->sensorStatus = source->sensorStatus;
		des->temperature = source->temperature;
		des->units = source->units;

	}

}


/**
 * @brief Manages power indicator oscillation
 *
 * Ensures that the period of the power LED changes with
 * each switching of its state, to guarantee a flashing effect.
 *
 *
 * @param None.
 *
 * @return None.
 */
void APP_TMC_runningIndicator (void) {

	/**
	 * Manage running indicator
	 */
	if (LIB_DP_delayRead (&runnigIndicatorDelay)) {

		uint32_t newPeriod = DEFAULT_PERIOD_10MS;

		BSP_VIM_LedToggle (E_RUNNING_INDICATOR);

		newPeriod = BSP_VIM_GetLedState (E_RUNNING_INDICATOR) ?
				RINNING_INDICATOR_PERIOD_HIGH_MS :
				RINNING_INDICATOR_PERIOD_LOW_MS;

		LIB_DP_delayInit(&runnigIndicatorDelay, newPeriod);

	}

}


/**
 * @brief System configuration
 *
 * Function to configure the software and hardware necessary for
 * the correct operation of the system. It invokes high- and
 * low-level routines to get the system ready.
 *
 *
 * @param None
 *
 * @return None.
 */
ConfigResult_t APP_TMC_setup (void) {

	/* MCU Configuration--------------------------------------------------------*/
	ConfigResult_t result = E_ERROR;

	LIB_DP_delayInit (&runnigIndicatorDelay, RINNING_INDICATOR_PERIOD_LOW_MS);

	LIB_DP_delayInit (&sampligRateDelay, SAMPLING_RATE_MS);

	if (BSP_HardwareSetup ()) {

		result = E_NO_ERROR;

	}

	return result;

}


/**
 * @brief Temperature data acquisition
 *
 * Function that invokes low-level routines to take temperature
 * samples at an interval of 200 milliseconds
 *
 *
 * @param None
 *
 * @return result Acquisition process report.
 */
DataAcquisitionResult_t APP_TMC_dataAcquisition (void) {

	DataAcquisitionResult_t result = E_NO_DATA;

	if (LIB_DP_delayRead (&sampligRateDelay)) {

		BSP_TM_GetTemperatureData(&tempData);

		result = E_DATA_OK;

	}

	return result;

}


/**
 * @brief Temperature data processing
 *
 * Function that verifies temperature limits and converts the acquired
 * temperature data into different units, also calculates temperature
 * alerts and sensor connection status.
 *
 *
 * @param None
 *
 * @return result processing routine report.
 */
DataProcessingResult_t APP_TMC_dataProcessing (void) {

	DataProcessingResult_t result = E_ERROR_PROC;

	// Verification of operating ranges
	if (tempData.temperature >= MIN_TEMP && tempData.temperature <= MAX_TEMP) {

		copyTempData(&tempData, &tempDataKelvin);

		LIB_TC_celciusToKelvin(&tempDataKelvin);

		copyTempData(&tempData, &tempDataFaren);

		LIB_TC_celciusToFarenheit(&tempDataFaren);

		result = E_PROC_OK;

	}


	// Manage sensor status
	if (tempData.sensorStatus == E_CONNECTED) {

		BSP_VIM_DeActivateTemperatureSensorStatusIndicator();
		BSP_NM_deActivateStateSensorIndicator();


	} else {

		BSP_VIM_ActivateTemperatureSensorStatusIndicator();
		BSP_NM_activateStateSensorIndicator();

		result = E_ERROR_PROC;

	}

	// ALARM TEMPERATURE
	if (tempData.temperature > TEMPERATURE_THRESHOLD_ALARM &&
		tempData.sensorStatus == E_CONNECTED) {

		BSP_VIM_ActivateTemperatureAlarmIndicator();
		BSP_NM_activateTempAlarmIndicator();

	} else {

		BSP_VIM_DeActivateTemperatureAlarmIndicator();
		BSP_NM_deActivateTempAlarmIndicator();

	}

	return result;

}


/**
 * @brief Procedure to display the captured information
 *
 * Function that sends the captured information to the screen for display
 *
 *
 * @param None
 *
 * @return result display rutine report.
 */
DataShowResult_t APP_TMC_dataShow (void) {

	BSP_NM_updateTempGraph(&tempData);

	BSP_NM_ShowTemperatureCelcius(&tempData);

	BSP_NM_ShowTemperatureKelvin(&tempDataKelvin);

	BSP_NM_ShowTemperatureFarenheit(&tempDataFaren);

	return E_SHOW_OK;

}
