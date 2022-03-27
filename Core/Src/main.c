/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * PMIK 2021Z Projekt
  * Maksym Khachapuridze
  *
  * Opis projektu:
  *
  * Projekt magnetometru
  * Układ sluzy do wykonywania i rejestracji pola magnetycznego.
  * Zostanie zrealizowany w przenosnej formie przy pomocy mikrokontrolera stm32L476RG.
  * Uklad wykonuje pomiar pola magnetycznego metodą pomiarową różnicową i wyswietla wyniki na zywo na ekranie.
  * Posiada rowniez mozliwosc przeslania zebranych pomiarow do komputera za pomocą interfejsu UART
  * pomiar można zatrzymać opcją pauzy oraz wyczyścić zapisane dane.
  * Sterowanie ukłądem jest oparte na 2 przyciskach
  *
  *
  *
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "../Inc/Pomiar.h"
#include "../Inc/ADC_Pomiary.h"
#include "GFX.h"
#include "displayManager.h"
#include  "ZapisLog.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define LINE_MAX_LENGTH	80

/* przeciazenie funkcji printf
 * pozwala na latwe wyswietlenie wyniku za pomoca interfejsu UART na komputerze
*/

/**
 * @brief inicjalizacja obiektu przechowywujacego pola z wynikami pomiarow
 * 
 */
	ADC_pomiary czujnik;
    ADC_pomiary *cptr=&czujnik;
/**
 * @brief flagi pomocnicze
 * 
 */
    bool isRunning=0;
    bool isPushed=0;




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
/**
 * @brief Construct a new hal adcex calibration start object
 * roznicowa kalibracja przetwornika
 */
HAL_ADCEx_Calibration_Start(&hadc1,ADC_DIFFERENTIAL_ENDED);
HAL_TIM_Base_Start_IT(&htim6);

displayWelcome();
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
 * @brief function HAL_TIM_PeriodElapsedCallback
 * Obsluga przerwania licznika
 * licznik ten steruje czestotliwoscia wykonania pomiaru
 * 
 * @param htim wskaznik na strukture timera
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim6) {
	  if(isRunning!=0){
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); //debug Led
	  WykonajPomiar(cptr);
	  }
  }
}

/*
 * function HAL_GPIO_EXTI_Callback
 * Obsluga przerwan przycisku
 * (wlacza pomiar albo go pauzuje)
 *
 */

/**
 * @brief function HAL_GPIO_EXTI_Callback
 * Obsluga przerwan przycisku
 * (wlacza pomiar albo go pauzuje)
 * 
 * @param GPIO_Pin 
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	//Blue button- Start/Pause
	if(GPIO_Pin==B1_Pin){

		if(isRunning==0){ isRunning=1;
		removePause();
		}
		else{ 	isRunning = 0;
		displayPause();
		}
	}
//przycisk do wyzwalania przesylu bufora z wynikami
	if(GPIO_Pin==B2_Pin){
		if(isRunning==1){// przeslanie bufora
			isPushed=1;
			SaveLog(czujnik.Bufor);
		}
		else if(isRunning==0){// klikniecie jesli pomiar w stanie pauzy- czysci bufor
			ClearBufor(czujnik.Bufor);

		}



	}


}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
