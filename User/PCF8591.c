/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2024 
 *  ==============================================================
 * 
 *  PCF8591.c 
 *    灰度传感器数据读取
 *
 *  --------------------------------------------------------------
 *  
 */
#include "PCF8591.h"	

extern UART_HandleTypeDef huart3;


void delay_us(uint32_t nus)
{		
	uint16_t temp=0;	    	 
    while(nus--)
    {
		temp=20;
		while(temp--);
	}
}

void IIC_SDA_Mode_OUT(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}
/*****************************************
  SDA引脚转变为 输入模式(输入模式传输具体的数据) 
******************************************/
void IIC_SDA_Mode_IN(void)
{
    GPIO_InitStruct.Pin = SDA_GPIO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_Type, &GPIO_InitStruct);
}

/*****************************************
  IIC开始信号
******************************************/
void IIC_Start(void)//IIC开始信号
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();
	
	//空闲状态两个引脚是高电平
	SDA_OUT(1);
	SCL_OUT(1) ;
	delay_us(5);
	
	//拉低数据线
	SDA_OUT(0);
	delay_us(5);
	
	//再拉低时钟线
	SCL_OUT(0) ;
	delay_us(5);
}


//IIC停止信号
void IIC_Stop(void)
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();
 
	//拉低
	SDA_OUT(0);
	SCL_OUT(0);
	delay_us(5);
	
	//时钟线先拉高
	SCL_OUT(1);
	delay_us(5);
	
	//再把数据线拉高
	SDA_OUT(1);
	delay_us(5);
}


void IIC_Send_Byte(uint8_t d)//主机发送8位数据给从机MSB 高位先发
{
    uint8_t i = 0;
    //设置为输出模式
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	delay_us(5);
	for(i=0;i<8;i++)
	{
		if(d & (0x1<<(7-i)))//表示数据是1
			SDA_OUT(1)
		else
			SDA_OUT(0);
		
		delay_us(5);
		SCL_OUT(1);//拉高时钟线，告诉对方你可以读了
		
		delay_us(5);
		SCL_OUT(0);//拉低时钟线，告诉对方你暂时别读，我在准备数据
	}
 
}

uint8_t IIC_Wait_Ack(void)//等待从机给主机应答或者不应答
{
	uint8_t ack = 0;
	//设置为输入模式
	IIC_SDA_Mode_IN();
	
	//时钟线拉高,时钟线为高电平期间，不管是数据还是ack都是有效的
	SCL_OUT(1);
	delay_us(5);
	
	if( SDA_IN  == 1)
		ack = 1;//无效ACK，就是无效应答
	else
		ack = 0;//有效ACK，就是有效应答
	
	SCL_OUT(0);
    
	delay_us(5);
	return ack;
}

uint8_t  IIC_Read_Byte(void)//从机发送8位数据给主机
{
	uint8_t i =0;
	uint8_t data = 0;
	//设置为输入模式
	IIC_SDA_Mode_IN();
	//先拉低时钟线，准备数据
	SCL_OUT(0);
	delay_us(5);
	
	for(i=0;i<8;i++)
	{
		SCL_OUT(1);//时钟线为高电平期间数据才是有效的
		delay_us(5);
		if(SDA_IN == 1)
			data |= (0x1<<(7-i));//数据就是1
		else
			data &= ~(0x1<<(7-i));//数据就是0
		
		SCL_OUT (0);//告诉对方此时准备数据，先别读写
		delay_us(5);
	}
	return data;
}

void IIC_Ack(uint8_t ack)//主机发送应答或者不应答给从机
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	delay_us(5);
	
	SDA_OUT(ack) ;//发送高/低电平--->发送不应答/应答
	delay_us(5);
	
	SCL_OUT(1);//告诉从机我已经准备好数据，你可以读取了
	delay_us(5);
	
	SCL_OUT (0);//拉低时钟线，发送ack结束
	delay_us(5);
}


void PCF8591T_Read_AD(uint8_t addr,uint8_t *data)
{
	IIC_Start();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x40);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	data[3]=IIC_Read_Byte();
	IIC_Stop();
    delay_us(40);
	IIC_Start();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x41);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	data[0]=IIC_Read_Byte();
	IIC_Stop();
	delay_us(40);
	IIC_Start();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x42);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	data[1]=IIC_Read_Byte();
	IIC_Stop();
	delay_us(40);
	IIC_Start();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x43);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	data[2]=IIC_Read_Byte();
	IIC_Stop();
	delay_us(100);
}

void PCF8591_address_scan(void)
{
    uint8_t address;
    printf("Scanning PCF8591 IIC bus ...\r\n");
    for (address=0; address<128; ++address)
    {
        IIC_Start();
        if (IIC_Wait_Ack() == 0)
        {
            printf("Device found at address:0x%X\r\n", address);
        }
        IIC_Stop();
        delay_us(10);
    }
    printf("Scan fininshed\r\n");
}


void PCF8591T_DATE_NUM(uint8_t front[])
{
    uint8_t send[11]={0xA5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5A};
    uint8_t A_front[8];
    uint8_t sum=0x00;
	PCF8591T_Read_AD(0x92,&A_front[0]);
	PCF8591T_Read_AD(0x90,&A_front[4]);
    for(uint8_t i=0; i<8; i++)
    {
        if(A_front[i]<9) front[7-i] = 0;
        else front[7-i] = 1;
    }
	memcpy(&send[1],&A_front,8);
	for(int i=0;i<8;i++) sum+=A_front[i];
	send[9]=sum;
	//HAL_UART_Transmit(&huart3,send,11,5);      
	printf("%d %d %d %d %d %d %d %d\r\n",A_front[0],A_front[1],A_front[2],A_front[3],A_front[4],A_front[5],A_front[6],A_front[7]);
	//printf("x1=%d x2=%d x3=%d x4=%d x5=%d x6=%d x7=%d x8=%d \r\n",front[0],front[1],front[2],front[3],front[4],front[5],front[6],front[7]);   
}



