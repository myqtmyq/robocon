/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2023 
 *  ==============================================================
 * 
 *  hostpc.c 
 *    上位机通信和指令处理
 *
 *  --------------------------------------------------------------
 *  
 */

#include "hostpc.h"

uint8_t receive_buff3[7];  
extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;


hostTypeDef host={0,0,0,0};

void USER_UART3_IRQHandler(UART_HandleTypeDef *huart)
{	// 判断是否是串口3
    if(USART3 == huart3.Instance)                                   
    {	// 判断是否是空闲中断
        if(RESET != __HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE))    
        {	 // 清除空闲中断标志（否则会一直不断进入中断）
            __HAL_UART_CLEAR_IDLEFLAG(&huart3);                     
            // 调用中断处理函数
            HAL_UART3_RxCpltCallback(huart);                          
        }
    }
		
}

//串口接收中断回调函数
void HAL_UART3_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_DMAStop(&huart3);  
                                                       
    // 计算接收到的数据长度
    uint8_t data_length  = 7 - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);   

    //HAL_UART_Transmit(&huart1,receive_buff3,data_length,1);          
		for(int i=0;i<data_length;i++)
			printf("%d,",receive_buff3[i]);   
    
    if(receive_buff3[0]==0xA5&&receive_buff3[6]==0x5A)
    { 	
		//printf("\n");
        memcpy(&host,&receive_buff3[1],4);
    }
	// 清零接收缓冲区
    memset(receive_buff3,0,data_length);                                            
    data_length = 0;
    
    // 重启开始DMA传输 每次255字节数据
    HAL_UART_Receive_DMA(&huart3, (uint8_t*)receive_buff3, 7);                    
}



int ByteToInt(char a)
{
    int data;
    if ((a & 0x7F) == a) return a;
    else
    {
        data = a - 0x01;//减去补码
        data = data ^ 0xFF;//反码得到负数的绝对值
        return data * -1;
    }
}

	/* 重定向 使用printf scanf调试 */
#pragma import(__use_no_semihosting)

struct __FILE
{
  int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
  x = x;
}

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t * ) & ch, 1, 1000);
  return (ch);
}

int fgetc(FILE *f)
{
  int ch;
  HAL_UART_Receive(&huart3, (uint8_t * ) & ch, 1, 1000);
  return (ch);
}
