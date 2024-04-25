/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2023 
 *  ==============================================================
 * 
 *  track.h 
 *    底盘循迹控制功能、转弯功能的外部接口
 *
 *  --------------------------------------------------------------
 *  
 */

#ifndef _TRACK_H
#define _TRACK_H

#include "main.h"


float detect_line(void);

float filter(float p ,float new_value, float* last_value);

#endif




