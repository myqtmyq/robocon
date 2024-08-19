#ifndef __WB2812_H__
#define __WB2812_H__

#include "stm32f1xx_hal.h"
#include "Delay.h"

#define DA_Port GPIOA
#define DA_Pin GPIO_PIN_0

typedef struct{
    int r;
    int g;
    int b;
}RGB_Typedef;

typedef struct RGB_Node_Type{
	RGB_Typedef _data;
	struct RGB_Node_Type *_next;
}RGB_Node_Typedef;

typedef struct{
	RGB_Node_Typedef *_front;
	RGB_Node_Typedef *_rear;
	
}RGB_Queue_Typedef;

void WB2812_Init(void);
void WB2812_1(void);
void WB2812_0(void);
void WB2812_End(void);
void WB2812_Write(RGB_Typedef *RGB_Data);
void WB2812_Showtime(RGB_Typedef RGB_Data[],int num);
void WB2812_Showtime_2(RGB_Queue_Typedef *RGB_Queue);
void Update_RGB(RGB_Typedef *RGB_Data,int r,int g,int b);
void RGB_Queue_Init(RGB_Queue_Typedef *RGB_Queue);
void RGB_Queue_Push(RGB_Queue_Typedef *RGB_Queue,RGB_Typedef RGB_Data);
void RGB_Queue_Pop(RGB_Queue_Typedef *RGB_Queue);

#endif
