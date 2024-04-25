/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2022 
 *  ==============================================================
 * 
 *  control.h
 *    受控运行功能的外部接口
 *
 *  --------------------------------------------------------------
 *  
 */

#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"

#define ANGLE_SPEED_PID_KP 80.0f
#define ANGLE_SPEED_PID_KI 0.05f
#define ANGLE_SPEED_PID_KD 0.0f
#define ANGLE_SPEED_PID_MAX_OUT 1000
#define ANGLE_SPEED_PID_MAX_IOUT 1000


/*用来存放运动状态的枚举*/
typedef enum
{
    DISARM = 0,
    ARM = 1,
    VEL_CONTROL_MODE = 2,
    GRAY_MODE = 3,
    TURN_LEFT_MODE = 4,
    TURN_RIGHT_MODE = 5
}mode_t;



/*用来存放锁定状态的枚举*/
typedef enum
{
    OK = 0,
    NOT_OK = 1
}lock_t;


void chassis_init(void);
	

#endif




