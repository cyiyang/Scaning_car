#include "HC_SR04.h"
 
float distant;      //��������
uint32_t measure_Buf[3] = {0};   //��Ŷ�ʱ������ֵ������
uint8_t  measure_Cnt = 0;    //״̬��־λ
uint32_t high_time;   //������ģ�鷵�صĸߵ�ƽʱ��
 
 
//========================��ȡ����
void SR04_GetData(void)
{
switch (measure_Cnt){
	case 0:
         TRIG_H;
         delay_us(30);
         TRIG_L;
    
		measure_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);	//�������벶��       ����: __HAL_TIM_ENABLE(&htim5);                                                                                    		
        break;
	case 3:
		high_time = measure_Buf[1]- measure_Buf[0];    //�ߵ�ƽʱ��
         printf("\r\n----�ߵ�ƽʱ��-%d-us----\r\n",high_time);							
		distant=(high_time*0.034)/2;  //��λcm
        printf("\r\n-������Ϊ-%.2f-cm-\r\n",distant);          
		measure_Cnt = 0;  //��ձ�־λ
        TIM1->CNT=0;     //��ռ�ʱ������
		break;
				
	}
}
  
//=========================us��ʱ����
    void delay_us(uint32_t us)//��Ƶ72M
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}
 
//===================�жϻص�����======================
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(TIM1 == htim->Instance)// �жϴ������жϵĶ�ʱ��ΪTIM1
	{
		switch(measure_Cnt)
      {
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;                          
		}	
	}
	
}

