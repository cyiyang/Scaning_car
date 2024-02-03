#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "tim.h"
#include "stdio.h"
#include "control.h"

//²âÁ¿×ªËÙ
void Getspeed(TIM_HandleTypeDef *htim);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);

#endif



