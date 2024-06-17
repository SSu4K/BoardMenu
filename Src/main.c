/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "lpuart.h"
#include "combuf.h"
#include "menu.h"
#include "diodes.h"

#define NVIC_ISER2			((uint32_t*)0xE000E108)
#define ISER2_LPUART_EN		(1<<6)

#define DIGIT				(1)
#define DELAY				(1000)

#define CR_KEY 					13

int is_command = 0;
combuf_t command_buffer;

void SystemClock_Config(void);
void nvic_init();
void LPUART1_IRQHandler(void);
void clear_command();

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	nvic_init();
	lpuart_init();
	combuf_init(&command_buffer);
	menu_init();

	transmit_string("\n\rWelcome to simple menu by Szymon Sudak!\n\rType 'help' to get available commands.\n\r");
	clear_command();

	while (1)
	{
		if(is_command){
			int error = handle_command(command_buffer.buffer);
			if(error == Invalid){
				transmit_string("\n\rInvalid command!");
			}
			else if(error == MissingArg){
				transmit_string("\n\rMissing argument!");
			}
			else if(error == InvalidArg){
				transmit_string("\n\rInvalid argument!");
			}
			else if(error == TooManyArg){
				transmit_string("\n\rToo many arguments!");
			}
			clear_command();
		}
		if(combuf_is_full(&command_buffer)){
			transmit_string("\n\rReached max command length!");
			clear_command();
		}

		controller_step();
	}
}

void nvic_init(){
	*NVIC_ISER2 |= ISER2_LPUART_EN;
}

void LPUART1_IRQHandler(void)
{
	if(is_command){
		return;
	}
	if(!(LPUART_REGISTER->ISR & ISR_RXNE)){
		return;
	}
	char c = LPUART_REGISTER->RDR;

	if(c==CR_KEY){
		is_command = 1;
	}
	else{
		if(combuf_put(&command_buffer, c)){
			transmit_char(c);
		}
	}
}

void clear_command(){
	combuf_flush(&command_buffer);
	transmit_string("\n\r");
	transmit_string(get_section_name());
	transmit_string("> ");
	is_command = 0;
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
