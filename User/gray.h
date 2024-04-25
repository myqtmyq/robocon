/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2022 
 *  ==============================================================
 * 
 *  gray.h 
 *    灰度传感器功能的外部接口
 *
 *  --------------------------------------------------------------
 *  
 */

#ifndef _GRAY_H
#define _GRAY_H

#include "main.h"

#define GRAY_F_0   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)    //读取左侧前部灰度传感器状态
#define GRAY_F_1   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)   //读取左侧中部灰度传感器状态
#define GRAY_F_2   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)   //读取左侧后部灰度传感器状态
#define GRAY_F_3   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)    //读取前侧左部灰度传感器状态
#define GRAY_F_4   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)    //读取前侧中部灰度传感器状态
#define GRAY_F_5   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)    //读取前侧右部灰度传感器状态
#define GRAY_F_6   HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)    //读取右侧前部灰度传感器状态
#define GRAY_F_7   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)    //读取右侧中部灰度传感器状态
#define GRAY_F_8   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)    //读取右侧后部灰度传感器状态

#define GRAY_B_L   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)   //读取后侧左部灰度传感器状态
#define GRAY_B_M   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)    //读取后侧中部灰度传感器状态
#define GRAY_B_R   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)    //读取后侧右部灰度传感器状态

void get_gray(unsigned char front[]);

#endif
