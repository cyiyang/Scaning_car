#include "control.h"

//控制电机转速
float target_speed[4] = {6,6,6,6};

pid_wheel  motor_wheel[4];

void pid_init(void)
{
    //四个电机的ID对应结构体
    motor_wheel[0].id = 1;
    motor_wheel[1].id = 2;
    motor_wheel[2].id = 3;
    motor_wheel[3].id = 4;
        
    PID_struct_init(&motor_wheel[0].pid_motor,POSITION_PID,4000.0f,300.0f,
    500.0f,0,0);//后三个参数是PID的值
    PID_struct_init(&motor_wheel[1].pid_motor,POSITION_PID,4000.0f,300.0f,
    500.0f,0,0);
    PID_struct_init(&motor_wheel[2].pid_motor,POSITION_PID,4000.0f,300.0f,
    500.0f,0,0);
    PID_struct_init(&motor_wheel[3].pid_motor,POSITION_PID,4000.0f,300.0f,
    500.0f,0,0);    
    
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)
{   
  //float f_leftspeed,f_rightspeed,b_leftspeed,b_rightspeed;
  uint16_t pwm_pos[4];
  if(htim->Instance == TIM6)
  {
    Getspeed(&htim2);
    Getspeed(&htim3);
    Getspeed(&htim4);
    Getspeed(&htim8);

    pwm_pos[0] = pid_calc(&motor_wheel[0].pid_motor,motor_wheel[0].motor_speed,target_speed[0]);
    pwm_pos[1] = pid_calc(&motor_wheel[1].pid_motor,motor_wheel[1].motor_speed,target_speed[1]);
    pwm_pos[2] = pid_calc(&motor_wheel[2].pid_motor,motor_wheel[2].motor_speed,target_speed[2]);
    pwm_pos[3] = pid_calc(&motor_wheel[3].pid_motor,motor_wheel[3].motor_speed,target_speed[3]);

    Set_motor(pwm_pos[1],pwm_pos[2],pwm_pos[0],pwm_pos[3]);
    
    OLED_ShowStr1(1,5,(int*)(pwm_pos[0]),9,2);
      
  }
  else if(htim->Instance == TIM7)
  {
     Tracking();  
  }
  
}









