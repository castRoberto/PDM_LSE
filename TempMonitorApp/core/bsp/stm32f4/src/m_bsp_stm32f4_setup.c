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
 * @file m_bsp_stm32f4_setup.c
 * @brief Hardware configuration module
 *
 * This header file is used as an interface to expose functions that
 * configure the application hardware.
 *
 * @author Roberto Castro
 * @date March 21 2024
 *
 */


#include "m_bsp_stm32f4_setup.h"

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void BSP_Error_Handler (void) {

	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();

	while (1) { }
}


/**
 * @brief System Clock Configuration
 * @retval None
 */
static void SystemClock_Config (void) {

	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK) {

		BSP_Error_Handler ();

	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {

		BSP_Error_Handler ();

	}

}


/**
 * @brief Hardware configurator
 *
 * Function that Configure all instances of application
 * peripherals
 *
 * @param void
 *
 * @return result: Configuration result.
 */
bool_t BSP_HardwareSetup (void) {

	bool_t result = true;

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	result &= (HAL_Init () == HAL_OK);

	/* Configure the system clock */
	SystemClock_Config ();

	BSP_VIM_InitVisualIndicators ();

	BSP_PBM_InitButtons ();

	result &= BSP_TM_InitTemperatureSensors ();

	result &= BSP_NM_ConfigureDisplay ();

	return result;

}



