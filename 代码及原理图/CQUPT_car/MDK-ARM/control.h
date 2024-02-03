#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "tim.h"
#include "Motor.h"
#include "PID.h"
#include "OLED.h"
#include "encoder.h"
#include "stdlib.h"
#include "Track.h"

//PID�ĳ�ʼ�����ı�kp��ki��kd
typedef struct
{
    int id;     //ÿ�����ID�Ŷ�Ӧ�ĵ��
    pid_t pid_motor;
    float motor_speed;
    float motor_angle;
    
}pid_wheel;

extern pid_wheel  motor_wheel[4];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim);
void pid_init(void);

#endif



