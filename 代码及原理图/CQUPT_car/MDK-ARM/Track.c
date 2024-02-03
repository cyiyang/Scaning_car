#include "Track.h"
#include "Motor.h"

static uint16_t pwm_add;
//加入PID控制算法实现平稳循迹
void Tracking(void)
{
	   //大幅度右转
		if ((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)==1)) 
		{
            while(1)//00001
		{
            pwm_add = 2000;
			Set_motor(1000,1000+pwm_add,1000+pwm_add,1000);
			if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)==0))
			break ;	
		}
        }		
		//右转
		else  if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12)==1)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)==0)) 
		{
            while(1)//00010
		 {
            pwm_add = 1000;
			Set_motor(1000,1000+pwm_add,1000+pwm_add,1000);
		 if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12)==0)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)==1))
			break ;	
		 }
        }
		
		//直行 //00100
		else if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12)==0)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==0))
		{
            Set_motor(1000,1000,1000,1000);      
        }
        
        //左转
        else if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10)==1)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==0))
        {
           while(1)//01000
		 {
            pwm_add = 1000;
			Set_motor(1000+pwm_add,1000,1000,1000+pwm_add);
		 if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12)==0)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)==1))
			break ;	
		 }  
        }
        //大幅度左转
        else if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10)==0)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)==1))
        {
           while(1)//10000
		 {
            pwm_add = 2000;
			Set_motor(1000+pwm_add,1000,1000,1000+pwm_add);
		 if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10)==1)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)==0))
			break ;	
		 }  
        }		 	
 }

    
 
