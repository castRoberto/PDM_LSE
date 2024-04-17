/*
 * m_app_temp_monitor_core.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */


#include "m_app_temp_monitor_core.h"
#include "m_bsp_stm32_hardware_config.h"
#include "m_lib_util_delay_processor.h"
#include "m_lib_util_temp_converter.h"
#include "m_ddt_temperature_data_types.h"
#include "m_ddt_common_types.h"
#include "m_ddt_machine_state_inputs.h"


static delay_t runnigIndicatorDelay;
static delay_t sampligRateDelay;
static TemperatureData_t tempData;
static TemperatureData_t tempDataKelvin;
static TemperatureData_t tempDataFaren;


static void copyTempData (TemperatureData_t* source, TemperatureData_t* des) {

	if (source != NULL && des != NULL) {

		des->sensorStatus = source->sensorStatus;
		des->temperature = source->temperature;
		des->units = source->units;

	}

}


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


DataAcquisitionResult_t APP_TMC_dataAcquisition (void) {

	DataAcquisitionResult_t result = E_NO_DATA;

	if (LIB_DP_delayRead (&sampligRateDelay)) {

		BSP_TM_GetTemperatureData(&tempData);

		result = E_DATA_OK;

	}

	return result;

}


DataProcessingResult_t APP_TMC_dataProcessing (void) {

	DataProcessingResult_t result = E_ERROR_PROC;

	if (tempData.temperature >= MIN_TEMP && tempData.temperature <= MAX_TEMP) {

		copyTempData(&tempData, &tempDataKelvin);

		LIB_TC_celciusToKelvin(&tempDataKelvin);

		copyTempData(&tempData, &tempDataFaren);

		LIB_TC_celciusToFarenheit(&tempDataFaren);

		result = E_PROC_OK;

	}

	/**
	 * Manage sensor status
	 */
	if (tempData.sensorStatus == E_CONNECTED) {

		BSP_VIM_DeActivateTemperatureSensorStatusIndicator();
		BSP_NM_deActivateStateSensorIndicator();


	} else {

		BSP_VIM_ActivateTemperatureSensorStatusIndicator();
		BSP_NM_activateStateSensorIndicator();

	}

	/**
	 * ALARM TEMPERATURE
	 */
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


DataShowResult_t APP_TMC_dataShow (void) {

	DataShowResult_t result = E_SHOW_OK;

	BSP_NM_updateTempGraph(&tempData);

	BSP_NM_ShowTemperatureCelcius(&tempData);

	BSP_NM_ShowTemperatureKelvin(&tempDataKelvin);

	BSP_NM_ShowTemperatureFarenheit(&tempDataFaren);

	return result;

}
