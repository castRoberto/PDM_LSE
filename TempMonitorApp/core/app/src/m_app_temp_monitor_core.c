/*
 * m_app_temp_monitor_core.c
 *
 *  Created on: Mar 22, 2024
 *      Author: recastrobeltran
 */

#include <stdbool.h>

#include "m_app_temp_monitor_core.h"
#include "m_bsp_stm32_hardware_config.h"
#include "m_lib_util_delay_processor.h"
#include "m_ddt_temperature_data_types.h"


static delay_t runnigIndicatorDelay;
static delay_t sampligRateDelay;
static TemperatureData_t tempData;


static void manageIndicators (void) {

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

	/**
	 * Manage sensor status
	 */
	if (tempData.sensorStatus == E_CONNECTED) {

		BSP_VIM_DeActivateTemperatureSensorStatusIndicator();

	} else {

		BSP_VIM_ActivateTemperatureSensorStatusIndicator();

	}


	/**
	 * ALARM TEMPERATURE
	 */
	if (tempData.temperature > TEMPERATURE_THRESHOLD_ALARM) {

		BSP_VIM_ActivateTemperatureAlarmIndicator();

	} else {

		BSP_VIM_DeActivateTemperatureAlarmIndicator();

	}

}

static void manageTemperature (void) {

	if (LIB_DP_delayRead (&sampligRateDelay)) {

		BSP_TM_GetTemperatureData(&tempData);

		BSP_NM_ShowTemperatureData(&tempData);

	}

}


void APP_TMC_setup (void) {

	/* MCU Configuration--------------------------------------------------------*/
	BSP_HardwareSetup ();

	LIB_DP_delayInit (&runnigIndicatorDelay, RINNING_INDICATOR_PERIOD_LOW_MS);

	LIB_DP_delayInit (&sampligRateDelay, SAMPLING_RATE_MS);

}

void APP_TMC_run (void) {

	manageTemperature();

	manageIndicators();

}
