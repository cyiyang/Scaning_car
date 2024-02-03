#ifndef __HC_SR04_H
#define __HC_SR04_H
#include "tim.h"
#include "stdio.h"
 
#define TRIG_H  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET)
#define TRIG_L  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET)
 
void delay_us(uint32_t us);
void SR04_GetData(void);
 

#endif


