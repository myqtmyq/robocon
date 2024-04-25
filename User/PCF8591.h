#ifndef __PCF8591_H
#define __PCF8591_H 

#include "main.h"

static GPIO_InitTypeDef GPIO_InitStruct;

#define SCL_Type     GPIOB
#define SDA_Type     GPIOB
 
#define SCL_GPIO    GPIO_PIN_4
#define SDA_GPIO    GPIO_PIN_3
//设置输出高低电平模式
#define SDA_OUT(X)   if(X) \
					 HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_SET); \
				     else  \
					 HAL_GPIO_WritePin(SDA_Type, SDA_GPIO, GPIO_PIN_RESET);
 
#define SCL_OUT(X)   if(X) \
					 HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_SET); \
				     else  \
					 HAL_GPIO_WritePin(SCL_Type, SCL_GPIO, GPIO_PIN_RESET);    
                                     
#define SDA_IN		 HAL_GPIO_ReadPin(SDA_Type,SDA_GPIO)//只有输入模式才能读取电平状态

#define front_gl_1     PCF8591T_Read_AD(0x92)


//void PCF8591_WR_BP(u8 x,u8 y);
void PCF8591T_Read_AD(uint8_t addr,uint8_t *data);
void PCF8591_Init(void);
void PCF8591T_DATE_NUM(uint8_t front[]);
                     
void PCF8591_address_scan(void);
#endif

