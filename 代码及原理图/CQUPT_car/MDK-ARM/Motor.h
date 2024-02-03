#ifndef __Motor_H__
#define __Motor_H__

#include "tim.h"
#include "gpio.h"

void  motor_init(void);
void  Set_motor(uint16_t speed0,uint16_t speed1,uint16_t speed2,uint16_t speed3);
void  Engine_Action(uint16_t angle);
void  qianjin(void);
void  zuozhuan(void);
void  youzhuan(void);
void Motor_stop(void);
void  houtui(void);

#endif


