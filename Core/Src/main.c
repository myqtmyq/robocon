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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

lock_t lock_tt;

mode_t control_mode;  


PidTypeDef ANGLE_Z_PID;
extern TIM_HandleTypeDef 	htim7; 
extern TIM_HandleTypeDef 	htim3;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart3;
extern  uint8_t receive_buff3[7];
extern hostTypeDef host;
extern unsigned char gray[12];
extern unsigned char sur,sul;
int d_time=0,z_time=0;
extern unsigned char mode=0,lock=1,detect=0;
unsigned char OverMess[4]="over";
int adc_data[4];

extern uint8_t gray[12];
extern uint32_t adcValue[3]; 

int16_t my_delay_time = 0;
uint8_t my_over = 0;
uint8_t turn_left_flag = 0;
uint8_t turn_right_flag = 0;
int16_t error,lasterror;

void RunVehicle(int speed);
void TurnVehicleLeft(int speed);
void TurnVehicleRight(int speed);

void SystemClock_Config(void);

/*底盘初始化*/
void chassis_init()
{
	
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);                            //开启定时器3PWM波输出
	
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart3, (uint8_t*)receive_buff3, 7); 
	//HAL_TIM_Base_Start_IT(&htim7); //使能定时器7和定时器7更新中断：TIM_IT_UPDATE  
	
}



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART1_UART_Init();
	MX_USART3_UART_Init();
	MX_TIM3_Init();
	MX_TIM7_Init();
	/* USER CODE BEGIN 2 */
	MX_ADC1_Init();
	MX_ADC_DMA_Init(); 
	MX_ADC_GPIO_Init();
	chassis_init();

	//while(1) printf("%d,%d,%d\n", adcValue[0], adcValue[1], adcValue[2]);
	//while(1) printf("%d,%d,%d,%d\n",host.mode,host.x,host.Raw,host.y);

	while(host.mode!=VEL_CONTROL_MODE)
		MotorMove(0,0,0);

	while(host.mode==VEL_CONTROL_MODE){
		MotorMove(host.x*8, host.Raw*8, -host.y*8);
	}

	TurnVehicleLeft(500);

	while(adcValue[2]<2000)
    RunVehicle(800);
		while(adcValue[2]>1500)
			MotorMove(800,0,0);
    
	for(int i=1;i<=12;i++){
	
	while(adcValue[2]<1700)
		RunVehicle(800);
	while(adcValue[2]>1500)
		MotorMove(800,0,0);
	int t=7200000;
	while(t--)
		RunVehicle(500);
	
	TurnVehicleLeft(500);
	TurnVehicleRight(500);
	}
  
  /* USER CODE END 2 */
//  static uint8_t gray[12];

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//     PCF8591T_DATE_NUM(gray);
    /* USER CODE END WHILE */
       // HAL_Delay(20);
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
//800 0.915 8.0
//300 0.35 4.5
void RunVehicle(int speed){
	//double p=(0.00127f)*speed-0.095f,d=(0.0017f)*speed;
	double p=0.9,d=2.4;
	int16_t kp=adcValue[0]-adcValue[1]-250;
	error=kp;
	int16_t kd=error-lasterror;
	int16_t pidvalue=p*kp+d*kd;
	MotorMove(speed,-pidvalue,0);
	lasterror=error;
	//printf("%d,%d,%d,%d\n", adcValue[0], adcValue[1], adcValue[2],pidvalue); // 打印结果
}


void TurnVehicleLeft(int speed){
	while(adcValue[1]>1000||adcValue[2]>1500)
		MotorMove(0,speed,0);
	while(adcValue[2]<1700)
		MotorMove(0,speed,0);
	while(adcValue[1]<1000)
		MotorMove(0,speed,0);

}

void TurnVehicleRight(int speed){
	while(adcValue[1]>1000||adcValue[0]>1500)
		MotorMove(0,-speed,0);
	while(adcValue[0]<1700)
		MotorMove(0,-speed,0);
	while(adcValue[1]<1000)
		MotorMove(0,-speed,0);

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
