#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

void Systick_Config(void);
void MX_ADC1_Init(void);
void MX_ADC_DMA_Init(void);
void MX_ADC_GPIO_Init(void);

#endif
