#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "main.h" //HAL���ļ�����
#include "motor.h"

extern UART_HandleTypeDef huart2;//����USART2��HAL��ṹ��

#define USART2_REC_LEN  200//����USART2�������ֽ���

extern uint8_t  USART2_RX_BUF;//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�ΪУ���
extern uint16_t USART2_RX_STA;//����״̬���
extern uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���
extern uint16_t Rx_statu;

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart);//�����жϻص���������
void  run_prg(void);

#endif 


