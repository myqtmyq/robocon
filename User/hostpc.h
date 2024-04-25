/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2023 
 *  ==============================================================
 * 
 *  hostpc.h 
 *    上位机通信和指令处理
 *
 *  --------------------------------------------------------------
 *  
 */

#ifndef __HOSTPC_H
#define __HOSTPC_H

#include "main.h"


/* 向上位机发送信息 */
typedef struct
{
    int8_t mode;
    int8_t x;
    int8_t y;
    int8_t Raw; 
}hostTypeDef;

void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart);
void USER_UART3_IRQHandler(UART_HandleTypeDef *huart);
int ByteToInt(char a);
#endif



