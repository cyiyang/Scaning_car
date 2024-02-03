#include<stdio.h>
#include<stm32f1xx.h>
#include<math.h>

static float foc_pwm;

//��Ƕ����
void _electricalAngle(float shaft_angle,int pole_pairs)
{	
	return (shaft_angle*pole_pairs);
}

void _normalizeAngle(float angle)
{
	float a = fmod(angle,2*PI);
	return a >= 0 ? a : (a + 2*PI);
	//fmod���Եõ���������ֵ�����������ͬ������ֵ���뵽[0,2*PI]��
}

void setPwm(float Ua,float Ub,float Uc)
{
	//��������
	Ua = _constance(Ua,0.0f,voltage_limit);
	Ua = _constance(Ua,0.0f,voltage_limit);
	Ua = _constance(Ua,0.0f,voltage_limit);

	//����ռ�ձ�
	//����ռ�ձȴ�0��1
	dc_a = _constance(Ua/voltage_power_supply,0.0f,1.0f);
	dc_b = _constance(Ub/voltage_power_supply,0.0f,1.0f);
	dc_c = _constance(Uc/voltage_power_supply,0.0f,1.0f);

	//����д�뵽PWM��ӳ��ͨ�� �Լ���	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,dc_a*255);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,dc_b*255);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,dc_c*255);
}

void setPhaseVoltage(float Uq,float Ud,float angle_el)
{
	angle_el = _normalizeAngle(angle_el + zero_electric_angle);
	Ualpha = -Uq*sin(angle_el);
	Ubeta = Uq*cos(angle_el);

	//�����˱任
	Ua = Ualpha + voltage_power_supply/2;
	Ub = (sqrt(3)*Ubeta-Ualpha)/2 + voltage_power_supply/2;
	Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;

	setPwm(Ua,Ub,Uc);
}

float velocityOpenloop(float target_velocity)
{
	unsigned long now_us = micros();

	//���㵱ǰÿ��Loop������ʱ����
	float Ts = (now_us - open_loop_timestamp)*1e-6f;

	//       
	
	
}






