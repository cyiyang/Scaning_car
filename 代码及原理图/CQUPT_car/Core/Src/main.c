/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "encoder.h"
#include "PID.h"
#include "Motor.h"
#include "Track.h"
#include "HC_SR04.h"
#include "bluetooth.h"
#include "OLED.h"
#include "PS2.h"
#include "control.h"
//#include "bsp_hal_wheel.h"

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
//printfÈáçÂÆöÂêë
int fputc(int ch, FILE *f) 
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);//huart1Œ™÷ÿ ‰≥ˆIOø⁄
	return ch;
}

int fgetc(FILE *f) 
{
uint8_t ch; 

HAL_UART_Receive(&huart2,(uint8_t*)&ch,1, HAL_MAX_DELAY ); 
return ch; 
} 
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
    //¥Æø⁄Ω” ‹≥ı ºªØ
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    
    HAL_UART_Init(&huart2);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_I2C1_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
    OLED_Init();
//  OLED_clear();
  
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);    
    
    HAL_TIM_Base_Start_IT(&htim1);    
    //±‡¬Î∆˜ƒ£ Ω    
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩƒ£ Ω
    HAL_TIM_Base_Start_IT(&htim2);                  //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ–∂ÔøΩ
        
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩƒ£ Ω
    HAL_TIM_Base_Start_IT(&htim3);                  //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ–∂ÔøΩ

    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩƒ£ Ω
    HAL_TIM_Base_Start_IT(&htim4);                  //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ–∂ÔøΩ
    
    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL); //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩƒ£ Ω
    HAL_TIM_Base_Start_IT(&htim8);                  //ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ–∂ÔøΩ 
    
    //∂® ±∆˜6µƒ÷–∂œ
//    __HAL_TIM_CLEAR_FLAG(&htim6,TIM_FLAG_UPDATE);//«Â≥˝÷–∂œ±Í÷æŒª    
//    HAL_TIM_Base_Start_IT(&htim6);

   //∂® ±∆˜7µƒ≥ı ºªØ
//    __HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);//«Â≥˝÷–∂œ±Í÷æŒª    
//    HAL_TIM_Base_Start_IT(&htim7);  

    //µÁª˙≥ı ºªØ
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);

    motor_init();
            
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   
  //PIDµƒ≥ı ºªØ
  pid_init();
  
  //HAL_UART_Receive_IT(&huart2,&USART2_NewData, 1);
  
  OLED_ShowStr(1,1,"bluetooth_mode",2);
  
  PS2_Get();
    
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      //OLED_ShowStr(1,1,"Motorspeed: ",2);
      
      //HAL_UART_Receive_IT(&huart2,&USART2_NewData, 1);
      
      //“£øÿ∆˜øÿ÷∆–°≥µ“∆∂Ø  PS2øÿ÷∆
      PS2_Get();      
      PS2_car();
      HAL_Delay(10);
   
      //printf("%s",&USART2_NewData);
            
      //Set_motor(2000,2000,2000,2000);     
      //HAL_Delay(10);
//    HAL_Delay(500);
//    OLED_ShowStr(20,1,"Motorspeed: ",2);
//           
//    HAL_Delay(50);
//    Engine_Action(2000);     
//    Set_motor(3000,3000,3000,3000);
//                                                      
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
