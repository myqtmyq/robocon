/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2024 
 *  ==============================================================
 * 
 *  control.c 
 *    受控运行功能的实现
 *
 *  --------------------------------------------------------------
 *  
 */

#include "control.h"

lock_t lock_tt;


mode_t control_mode;  

void RunVehicle(int speed);

PidTypeDef ANGLE_Z_PID;
extern TIM_HandleTypeDef 	htim7; 
extern TIM_HandleTypeDef 	htim3; 
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
extern  uint8_t receive_buff3[7];
extern hostTypeDef host;
extern unsigned char gray[12];
extern unsigned char sur,sul;
int d_time=0,z_time=0;
unsigned char mode=0,lock=1,detect=0;
unsigned char OverMess[4]="over";


extern uint8_t gray[12];
extern uint32_t adcValue[3];

#define Is_black(x) adcValue[x]>=1700

int16_t my_delay_time = 0;
uint8_t my_over = 0;
uint8_t turn_left_flag = 0;
uint8_t turn_right_flag = 0;
int16_t error,lasterror;


/*底盘初始化*/
void chassis_init()
{
	static float ANGLE_speed_pid[3] = {ANGLE_SPEED_PID_KP, ANGLE_SPEED_PID_KI, ANGLE_SPEED_PID_KD};	
	
    PID_Init(&ANGLE_Z_PID, PID_DELTA, ANGLE_speed_pid, ANGLE_SPEED_PID_MAX_OUT, ANGLE_SPEED_PID_MAX_IOUT);  
	
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);                            //开启定时器3PWM波输出
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);                            //开启定时器3PWM波输出
	
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart3, (uint8_t*)receive_buff3, 7); 
	HAL_TIM_Base_Start_IT(&htim7); //使能定时器7和定时器7更新中断：TIM_IT_UPDATE  
	
}



// 定时器中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim7))
    {
        //mode=host.mode;
		mode=TURN_LEFT_MODE;
        if(mode==DISARM)                 // 模式为0 ，停止模式，锁定
        {
            MotorMove(0, 0, 0);
            lock=OK;
        }
        else if(mode==ARM)lock=NOT_OK;     // 模式为1， 解锁
			
        if(lock==NOT_OK)                   // 如果解锁，执行
        {
            if(mode==ARM)
            {
                MotorMove(0, 0, 0);
            }             
            else if(mode==VEL_CONTROL_MODE)         // 如果模式为2， 为上位机速度控制模式，给x, y ,r 控制机器人移动
            {
                MotorMove(host.x*8, host.Raw*8, -host.y*8);
            }
            else if((mode==GRAY_MODE)||detect)   // 如果模式为3 或者detect==3 灰度巡线模式
            {
				/*
                if(d_time==0)d_time=1,detect=1;
                if ((sul>2||sur>2) && d_time>200)    // 判断循线停止条件
                {
                    my_over = 1;                     // 到尽头了
                }
                else if (my_over == 1)
                {
                    my_delay_time ++;
                    
                    if (my_delay_time >= 90)
                    {
                        MotorMove(0, 0, 0);
                                            //启动屏蔽检测到黑线
                        HAL_UART_Transmit(&huart3, OverMess, 4, 1);
                        host.mode = 10;
                        z_time=300;
                        mode=1;
                        detect=0;
                        my_over  =0;
                        my_delay_time = 0;
                    }
                    else
                    {
                        MotorMove(250, 0, 0);
                    }
                }
                else
                {
                    PID_Calc(&ANGLE_Z_PID);
                    MotorMove(250,ANGLE_Z_PID.out,0);
                    detect=1;
                    d_time++;
                    z_time--;
                }
				*/
				RunVehicle(800);
				//MotorMove(0, 0, 0);
            }
            else if (mode == TURN_LEFT_MODE || turn_left_flag)
            {
							/*
                my_delay_time++;
                if (my_delay_time >= 200)
                {
                    if (gray[3]|| gray[4])
                    {
                        MotorMove(0, 0, 0);
                        //启动屏蔽检测到黑线
                        HAL_UART_Transmit(&huart3, OverMess, 4, 1);
                        host.mode = 10;
                        my_delay_time = 0;
                        turn_left_flag = 0;
                    }
                }
                else
				*/
				//my_delay_time=0; 
//				while(my_delay_time<1000)
//                    MotorMove(0, 500, 0),my_delay_time++;
				my_delay_time=0;
				//printf("%d,%d,%d\n", adcValue[0], adcValue[1], adcValue[2]);
				if(Is_black(2)){
					//printf("Hello");
					my_delay_time++;
					//MotorMove(0, 50, 0);
									
//					if(my_delay_time>10)
//						printf("c"),detect=0,my_delay_time=0;
					printf("C"); 
					while(Is_black(1));	
				}
				else
                {
                    //turn_left_flag = 1;
                    MotorMove(0, 800, 0);
                }
            }
            else if (mode == TURN_RIGHT_MODE || turn_right_flag)
            {
                my_delay_time++;
                if (my_delay_time >= 150)
                {
                    if (gray[3]|| gray[4])
                    {
                        MotorMove(0, 0, 0);
                        //启动屏蔽检测到黑线
                        HAL_UART_Transmit(&huart3, OverMess, 4, 1);
                        host.mode = 10;
                        my_delay_time = 0;
                        turn_right_flag = 0;
                    }
                }
                else
                {
                    turn_right_flag = 1;
                    MotorMove(0, -300, 0);
                }
            }
            else
            {
				MotorMove(0, 0, 0);
            }
        }
        else
        {
			MotorMove(0, 0, 0);
			z_time=0;
			d_time=0;
			detect=0;	
        }
    }
}


//800 0.915 8.0
//300 0.35 4.5
void RunVehicle(int speed){
	//double p=(0.00127f)*speed-0.095f,d=(0.0017f)*speed;
	double p=0.9,d=2.375;
	int16_t kp=adcValue[0]-adcValue[1]-250;
	error=kp;
	int16_t kd=error-lasterror;
	int16_t pidvalue=p*kp+d*kd;
	MotorMove(speed,-pidvalue,0);
	lasterror=error;
	//printf("%d,%d,%d,%d\n", adcValue[0], adcValue[1], adcValue[2],pidvalue); // 打印结果
}




