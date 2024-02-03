#include "PS2.h"

uint8_t cmd[3] = {0x01,0x42,0x00};  //�����������
uint8_t PS2data[9] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};   //�洢�ֱ���������
PS2_TypeDef PS2_Data = {0};
pid_wheel PS2_Motor[4];

/**
 * @brief 这个函数解决通信问题
 * 
 */
void PS2_Get(void)    //����ps2����
{
	uint8_t i = 0;
	
	CS_L;  //���ߣ���ʼͨѶ
		
	HAL_SPI_TransmitReceive(&hspi1,&cmd[0],&PS2data[0],1,0xffff); // ����0x01�������������
	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi1,&cmd[1],&PS2data[1],1,0xffff); // ����0x42������0x01��PS2��ʾ��ʼͨ�ţ�
	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi1,&cmd[2],&PS2data[2],1,0xffff); // ����0x00������ID�����̵�ģʽ��
	delay_us(10);
	for(i = 3;i <9;i++)
	{
		HAL_SPI_TransmitReceive(&hspi1,&cmd[2],&PS2data[i],1,0xffff); // ��������
		delay_us(10);		
	}	
	CS_H;  //���ͣ�׼���´�ͨѶ
}

void PS2_Decode(void)
{
   if (PS2data[2] == 0x5A)
    {
        PS2_Data.Key_Select = (~PS2data[3] >> 0) & 0x01; //ѡ���
        PS2_Data.Key_Start = (~PS2data[3] >> 3) & 0x01;  //��ʼ��

        //��ఴ��
        PS2_Data.Key_L_Up = (~PS2data[3] >> 4) & 0x01;
        PS2_Data.Key_L_Right = (~PS2data[3] >> 5) & 0x01;
        PS2_Data.Key_L_Down = (~PS2data[3] >> 6) & 0x01;
        PS2_Data.Key_L_Left = (~PS2data[3] >> 7) & 0x01;

        //��ఴ��
        PS2_Data.Key_L2 = (~PS2data[4] >> 0) & 0x01;
        PS2_Data.Key_R2 = (~PS2data[4] >> 1) & 0x01;
        PS2_Data.Key_L1 = (~PS2data[4] >> 2) & 0x01;
        PS2_Data.Key_R1 = (~PS2data[4] >> 3) & 0x01;

        //�Ҳఴ��
        PS2_Data.Key_R_Up = (~PS2data[4] >> 4) & 0x01;
        PS2_Data.Key_R_Right = (~PS2data[4] >> 5) & 0x01;
        PS2_Data.Key_R_Down = (~PS2data[4] >> 6) & 0x01;
        PS2_Data.Key_R_Left = (~PS2data[4] >> 7) & 0x01;

        if (PS2data[1] == 0x41)
        { //�޵�ģʽ(ҡ��ֵ����)
            PS2_Data.Rocker_LX = 127 * (PS2_Data.Key_L_Right - PS2_Data.Key_L_Left);
            PS2_Data.Rocker_LY = 127 * (PS2_Data.Key_L_Up - PS2_Data.Key_L_Down);

            PS2_Data.Rocker_RX = 127 * (PS2_Data.Key_R_Right - PS2_Data.Key_R_Left);
            PS2_Data.Rocker_RY = 127 * (PS2_Data.Key_R_Up - PS2_Data.Key_R_Down);
        }
        else if (PS2data[1] == 0x73)
        { //���ģʽ(ҡ��ֵģ��)

            //ҡ�˰���
            PS2_Data.Key_Rocker_Left = (~PS2data[3] >> 1) & 0x01;
            PS2_Data.Key_Rocker_Right = (~PS2data[3] >> 2) & 0x01;

            //ҡ��ֵ
            PS2_Data.Rocker_LX = PS2data[7] - 0x80;
            PS2_Data.Rocker_LY = -1 - (PS2data[8] - 0x80);
            PS2_Data.Rocker_RX = PS2data[5] - 0x80;
            PS2_Data.Rocker_RY = -1 - (PS2data[6] - 0x80);
        }
    }
}

/**
 * @brief PS的小车地盘代码，有问题
 * 
 */
void PS2_car(void)
{
    //PS2_Decode(); PS2_Motor �Ŀ��ƴ���
    
    if(PS2data[5] < 0xff && PS2data[6] < 0xff)
    {
        //������٣��Ҽ��ƶ�����
        uint16_t accelation =  (PS2data[7]-128)*35; //+ (PS2data[8]-128)*35;
        uint16_t right_site =  (PS2data[5]-128)*35;
        //uint16_t left_site = (PS2data[6]-128)*35; 
                       
        
        PS2_Motor[0].motor_speed = accelation + right_site;
        PS2_Motor[1].motor_speed = accelation;
        PS2_Motor[2].motor_speed = accelation;
        PS2_Motor[3].motor_speed = accelation + right_site;        
                
        Set_motor(PS2_Motor[0].motor_speed,PS2_Motor[1].motor_speed,PS2_Motor[2].motor_speed,PS2_Motor[3].motor_speed);        
    
    }        
            
}





