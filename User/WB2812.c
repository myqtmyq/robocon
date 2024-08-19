#include "WB2812.h"
#include <stdio.h>
#include <stdlib.h>

void WB2812_Init(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = DA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DA_Port, &GPIO_InitStruct);
	
    HAL_GPIO_WritePin(DA_Port,DA_Pin,GPIO_PIN_RESET);
    Delay_us(500);

}

void WB2812_1(){
    HAL_GPIO_WritePin(DA_Port,DA_Pin,GPIO_PIN_SET);
    Delay_ns(7);
    HAL_GPIO_WritePin(DA_Port,DA_Pin,GPIO_PIN_RESET);
    Delay_ns(1);

}

void WB2812_0(){
    HAL_GPIO_WritePin(DA_Port,DA_Pin,GPIO_PIN_SET);
    Delay_ns(1);
    HAL_GPIO_WritePin(DA_Port,DA_Pin,GPIO_PIN_RESET);
    Delay_ns(7);

}

void WB2812_End(){
    Delay_us(500);

}

void WB2812_Write(RGB_Typedef *RGB_Data){
	int g=RGB_Data->g;
    for(int i=1;i<=8;i++){
        if((g&0x01)==1)
            WB2812_1();
        else    
            WB2812_0();
        g>>=1;
    }
	int r=RGB_Data->r;
    for(int i=1;i<=8;i++){
        if((r&0x01)==1)
            WB2812_1();
        else    
            WB2812_0();
       r>>=1;
    }
	int b=RGB_Data->b;
    for(int i=1;i<=8;i++){
        if((b&0x01)==1)
            WB2812_1();
        else    
            WB2812_0();
        b>>=1;
    }
	//WB2812_End();
}

void WB2812_Showtime(RGB_Typedef RGB_Data[],int num){
	for(int i=0;i<num;i++){
		WB2812_Write(&RGB_Data[i]);
	}
	WB2812_End();
}

void WB2812_Showtime_2(RGB_Queue_Typedef *RGB_Queue){
	RGB_Node_Typedef *RGB_Node;
	for(RGB_Node=RGB_Queue->_front;RGB_Node;RGB_Node=RGB_Node->_next)
		WB2812_Write(&RGB_Node->_data);
	WB2812_End();
}

void Update_RGB(RGB_Typedef *RGB_Data,int r,int g,int b){
	RGB_Data->r=r;
	RGB_Data->g=g;
	RGB_Data->b=b;
}

void RGB_Queue_Init(RGB_Queue_Typedef *RGB_Queue){
	RGB_Queue->_front=NULL;
	RGB_Queue->_rear=NULL;
}

void RGB_Queue_Push(RGB_Queue_Typedef *RGB_Queue,RGB_Typedef RGB_Data){
	RGB_Node_Typedef *RGB_Node=(RGB_Node_Typedef *)malloc(sizeof(RGB_Node_Typedef));
	if(RGB_Node==NULL)
		printf("Wrong\n");
	RGB_Node->_data=RGB_Data;
	RGB_Node->_next=NULL;
	if(RGB_Queue->_front==NULL){
		RGB_Queue->_front=RGB_Node;
		
        RGB_Queue->_rear = RGB_Node;
	}
	
	else{
		RGB_Queue->_rear->_next=RGB_Node;
		RGB_Queue->_rear=RGB_Node;
	}
	
    //printf("Pushed RGB: (%d, %d, %d)\n", RGB_Queue->_rear->_data.r, RGB_Queue->_rear->_data.g, RGB_Queue->_rear->_data.b);

}

void RGB_Queue_Pop(RGB_Queue_Typedef *RGB_Queue){
	if(RGB_Queue->_front==NULL)
		return;
	
	RGB_Node_Typedef *tmp=RGB_Queue->_front->_next;
	free(RGB_Queue->_front);
	RGB_Queue->_front=tmp;
	
    //printf("Popped RGB: (%d, %d, %d)\n", RGB_Queue->_front->_data.r, RGB_Queue->_front->_data.g, RGB_Queue->_front->_data.b);
}
