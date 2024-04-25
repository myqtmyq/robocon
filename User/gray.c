/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2023 
 *  ==============================================================
 * 
 *  gray.c 
 *    灰度传感器功能的实现
 *
 *  --------------------------------------------------------------
 *  
 */

#include "gray.h"


void get_gray(unsigned char g[])
{
	g[0]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14);	
	g[1]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);		
	g[2]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);		
	g[3]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);		
	g[4]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3);	
	g[5]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2);	
	g[6]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2);	
	g[7]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);	
	g[8]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);	
	g[9]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);	
  g[10]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0);	
	g[11]=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);	
	//printf("x1=%d x2=%d x3=%d x4=%d x5=%d x6=%d x7=%d x8=%d x9=%d x10=%d x11=%d x12=%d\r\n",g[0],g[1],g[2],g[3],g[4],g[5],g[6],g[7],g[8],g[9],g[10],g[11]);   
}
