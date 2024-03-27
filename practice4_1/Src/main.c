 /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
 * States for the debounce state machine
 */
typedef enum {

	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING

} DebounceState_t;


/*
 * Rebound stabilization time
 */
#define DEBOUNCE_STABILIZATION_TIME_40MS 40


/* UART handler declaration */
UART_HandleTypeDef UartHandle;


static delay_t debounceDelay;
static DebounceState_t currentState;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config (void);
static void Error_Handler (void);

static void debounceFsmInit (void);
static void debounceFsmUpdate (void);

static void buttonPressed (void);
static void buttonReleased (void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main (void) {

	HAL_Init ();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config ();

	/* Initialize BSP Led for LED1 */
	BSP_LED_Init (LED1);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init (BUTTON_USER, BUTTON_MODE_GPIO);

	/* Initialize the state machine */
	debounceFsmInit ();

	/* Infinite loop */
	while (1) {

		/* Update the state machine */
		debounceFsmUpdate ();

	}
}


/**
 * @brief Initialize the state machine
 *
 * Sets the initial state of the state machine and its
 * non-blocking delay structure.
 *
 * @param void.
 *
 * @return void.
 */
static void debounceFsmInit (void) {

	currentState = BUTTON_UP;
	/* Initialize API delay */
	API_delayInit (&debounceDelay, DEBOUNCE_STABILIZATION_TIME_40MS);

}


/**
 * @brief Update the state machine
 *
 * Function to update the states and outputs of the
 * state machine
 *
 * @param None
 *
 * @return None
 */
static void debounceFsmUpdate (void) {

	GPIO_PinState buttonState = BSP_PB_GetState (BUTTON_USER);

	switch (currentState) {

		case BUTTON_UP: {

			if (buttonState) { currentState = BUTTON_FALLING; }
			break;

		}

		case BUTTON_FALLING: {

			if (API_delayRead (&debounceDelay)) {

				currentState = buttonState? BUTTON_DOWN : BUTTON_UP;

				if (currentState == BUTTON_DOWN) { buttonPressed (); }

			}

			break;

		}

		case BUTTON_DOWN: {

			if (!buttonState) {	currentState = BUTTON_RAISING;	}
			break;
		}

		case BUTTON_RAISING: {

			if (API_delayRead (&debounceDelay)) {

				currentState = (!buttonState)? BUTTON_UP : BUTTON_DOWN;

				if (currentState == BUTTON_UP) { buttonReleased (); }

			}

			break;

		}

		default: {

			debounceFsmInit ();
			break;

		}

	}

}


/**
 * @brief Activate output
 *
 * Activate the output of the state machine
 *
 * @param None
 *
 * @return None
 */
static void buttonPressed (void) {

    BSP_LED_On (LED1);

}


/**
 * @brief Disable output
 *
 * Disable the output of the state machine
 *
 * @param None
 *
 * @return None
 */
static void buttonReleased (void) {

    BSP_LED_Off (LED1);

}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void) {

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
