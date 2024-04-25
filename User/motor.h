/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2023 
 *  ==============================================================
 * 
 *  motor.h
 *    电机控制功能的外部接口
 *
 *  --------------------------------------------------------------
 *  
 */

#ifndef _MOTOR_H
#define _MOTOR_H

#include "main.h"

void MotorInit(void);

void MotorMove(int x, int r, int y);

int MotorLimit(int l);

#endif
