/**
 * @file encoder.c
 * @author cyyt (cyy543120@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "encoder.h"

float speed[4] = {0};

/**
 * @brief 获取速度
 * 
 * @param htim 
 */
void  Getspeed(TIM_HandleTypeDef *htim)
{
    uint16_t zhuansu[4];
    
    if (htim->Instance == TIM2) //������-------�������Ǻ�����
    {
        zhuansu[0] = (short)__HAL_TIM_GetCounter(&htim2);//��ȡ����ֵ
        speed[0] = (float)zhuansu[0] / (11 * 90) / 100;//����ת��
        __HAL_TIM_SetCounter(&htim2, 0);//��ռ���ֵ
//        printf("%d\r\n", speed[0]);//���ת��
         motor_wheel[0].motor_speed = speed[0];
    }
    else if(htim->Instance == TIM3) //����ת��10ms   ǰ�ҵ�� 
    {
        zhuansu[1] = (short)__HAL_TIM_GetCounter(&htim3);//��ȡ����ֵ
        speed[1] = (float)zhuansu[1] / (11 * 90) / 100;//����ת��
        __HAL_TIM_SetCounter(&htim3, 0);//��ռ���ֵ
//        printf("%d\r\n", speed[1]);//���ת��
        motor_wheel[1].motor_speed = speed[1];
    }
    else if(htim->Instance == TIM4)     //�Һ���
    {
        zhuansu[2] = (short)__HAL_TIM_GetCounter(&htim4);//��ȡ����ֵ
        speed[2] = (float)zhuansu[2] / (11 * 90) / 100;//����ת��
        __HAL_TIM_SetCounter(&htim4, 0);//��ռ���ֵ     
//        printf("%d\r\n", speed[2]);//���ת��
        motor_wheel[2].motor_speed = speed[2];
    }
    else if(htim->Instance == TIM8)        //ǰ��
    {
        zhuansu[3] = (short)__HAL_TIM_GetCounter(&htim8);//��ȡ����ֵ
        speed[3] = (float)zhuansu[3] / (11 * 90) / 100;//����ת��
        __HAL_TIM_SetCounter(&htim8, 0);//��ռ���ֵ
//        printf("%d\r\n", speed[3]);//���ת��
        motor_wheel[3].motor_speed = speed[3];
    }
}


