/*  
 *  Nanjing JIYU Technology Co.,Ltd All rights reserved.
 *  Copyright (C) 2022 
 *  ==============================================================
 * 
 *  track.c 
 *    底盘循迹控制功能、转弯功能的实现
 *
 *  --------------------------------------------------------------
 *  
 */

#include "track.h"


unsigned char gray[12];
float line_err=0;
unsigned char su=0,sur=0,sul=0;
float es_value=0;


float detect_line(){
    
	 PCF8591T_DATE_NUM(gray);
	 su=gray[0]+gray[1]+gray[2]+gray[3]+gray[4]+gray[5]+gray[6]+gray[7]+gray[8];
     sur=gray[4]+gray[5]+gray[6]+gray[7];
	 sul=gray[0]+gray[1]+gray[2]+gray[3];

	 if(su==2){
		 if(gray[3]==1&&gray[4]==1)line_err=1;
		 else if(gray[4]==1&&gray[5]==1)line_err=-1;
		 else if(gray[2]==1&&gray[3]==1)line_err=3;
		 else if(gray[5]==1&&gray[6]==1)line_err=-3;
		 else if(gray[1]==1&&gray[2]==1)line_err=5;
		 else if(gray[6]==1&&gray[7]==1)line_err=-5;
		 else if(gray[0]==1&&gray[1]==1)line_err=7;
		 else if(gray[7]==1&&gray[8]==1)line_err=-7;
		 else line_err=0;
	 }
	 else if(su==1){
		 if(gray[4]==1)line_err=0;
	 	 else if(gray[3]==1)line_err=2;
		 else if(gray[5]==1)line_err=-2;
		 else if(gray[2]==1)line_err=4;
		 else if(gray[6]==1)line_err=-4;
		 else if(gray[1]==1)line_err=6;
		 else if(gray[7]==1)line_err=-6;
		 else if(gray[0]==1)line_err=8;
		 else if(gray[8]==1)line_err=-8;
	 }
	 else if(su==0){
	 	 if(line_err>6)line_err=9;
		 else if(line_err<-6)line_err=-9;
	 }
	 else if(su>2) line_err=0;
	 line_err=filter(0.5,line_err,&es_value);
	 //printf("E=%f,SU=%d\r\n",line_err,su);   
	 return line_err;
}

float filter(float p ,float new_value, float* last_value) 
{ 
    *last_value = p *new_value +(1-p)**last_value;
    return *last_value;
}
