/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2022 
 *  ==============================================================
 * 
 *  motor.c 
 *    电机控制功能的实现
 *
 *  --------------------------------------------------------------
 *  
 */

#include "motor.h"

extern TIM_HandleTypeDef htim3;


/*-----------------------------  TB6612,电机方向和端电压(PWM占空比)值  -------------------------------------*/

static void MotorPwmSet1(int p)                                     //左前电机
{
  if (p >= 0)                                                         //控制电机顺时针旋转
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
  }
  else                                                                //控制电机逆时针旋转
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);              //BIN1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);            //BIN2
  }
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, abs(p));
}


static void MotorPwmSet2(int p)                                     //左后电机
{
  if (p >= 0)                                                         //控制电机顺时针旋转
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);               //AIN1
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);             //AIN2
  }
  else                                                                //控制电机逆时针旋转
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  }
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, abs(p));
}


static void MotorPwmSet3(int p)                                      //右后电机
{
  if (p >= 0)                                                          //控制电机顺时针旋转
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);                //BIN1
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);              //BIN2
  }
  else                                                                 //控制电机逆时针旋转
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
  }
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, abs(p));                 //注意电机3是通道4控制
}


static void MotorPwmSet4(int p)                                       //右前电机
{
  if (p >= 0)                                                           //控制电机顺时针旋转
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);                 //AIN1
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);               //AIN2
  }
  else                                                                  //控制电机逆时针旋转
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  }
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, abs(p));
}



/* 前进速度，差速值r>0右转 */
void MotorMove(int x, int r, int y)
{
	MotorPwmSet1(MotorLimit(x - r + y));
    MotorPwmSet2(MotorLimit(x - r - y));
	MotorPwmSet3(MotorLimit(x + r + y));
    MotorPwmSet4(MotorLimit(x + r - y));
}

int MotorLimit(int l)
{
	if(l>1000) return 1000;
	else if(l<-1000) return -1000;
	else return l;
}
