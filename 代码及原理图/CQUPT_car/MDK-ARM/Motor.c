#include "Motor.h"

void motor_init(void)
{
  Set_motor(0,0,0,0);  
}

/**
 * @brief 获取底层驱动
 * 
 * @param speed0 
 * @param speed1 
 * @param speed2 
 * @param speed3 
 */
//电机驱动
void Set_motor(uint16_t speed0,uint16_t speed1,uint16_t speed2,uint16_t speed3)
{
   //前进
  if(speed0 >= 0 && speed1 >= 0 && speed2 >= 0 && speed3 >= 0) 
  {  //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,speed0);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,speed1);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,speed2);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,speed3);
  }
  else if(speed0 > 0 && speed3 >0 && speed1 < 0 && speed2 <0)//左转
  {
            //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,speed0);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,-speed1);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,-speed2);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,speed3); 
  }
  else if(speed0 < 0 && speed3 < 0 && speed1 > 0 && speed2 > 0)//右转
  {
   //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,-speed0);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,speed1);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,speed2);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,-speed3);
  }
  else if(speed0 < 0 && speed3 < 0 && speed1 < 0 && speed2 < 0)
  {
        //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,-speed0);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,-speed1);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,-speed2);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,-speed3);
  }
    
}

//舵机输出------180°舵机位置控制
void  Engine_Action(uint16_t angle)  
{
    //PWM舵机输出
                                            
     __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,angle*100);//180°舵机
     __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,angle);          
     __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,angle);           
}


void  qianjin(void)
{
    Set_motor(3000,3000,3000,3000);
}

void  zuozhuan(void)
{
       //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,4000);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,4000);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,4000);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,4000); 

}

              
void youzhuan(void)
{    
      //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,4000);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,4000);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,4000);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,4000);  
}

void Motor_stop(void)
{
          //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,0);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,0);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,0);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,0);

}

void  houtui(void)
{
    //前右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_1,4000);  

    //前左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,4000);
   

    //后左电机
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,4000);

   
    //后右电机    
   HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
   __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,4000); 

}





