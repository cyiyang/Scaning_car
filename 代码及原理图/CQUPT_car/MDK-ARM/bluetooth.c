#include "bluetooth.h"
#include "stdio.h"

uint8_t USART2_RX_BUF;//���ջ���,���USART_REC_LEN���ֽ�.
uint16_t USART2_RX_STA=0;//����״̬���//bit15��������ɱ�־��bit14~0�����յ�����Ч�ֽ���Ŀ
uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���
uint16_t Rx_statu = 0;


void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//�����жϻص�����
{
    if(huart->Instance == USART2)
    {
        
        Rx_statu = 1;
        
        run_prg();
        printf("OK,right!");
       
       //HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //��Ϊÿִ����һ���жϻص������Ὣ�����жϹ��ܹرգ����������Ҫ�ٿ��������ж�
        
    }
}

void  run_prg(void)
{
    
    if(Rx_statu)
    {   
        
      Rx_statu = 0;
      if(USART2_NewData == 'U')
      {
         qianjin();
         printf("U");
             
      }
      else if(USART2_NewData == 'L')
      {
         zuozhuan();
      
      }
      else if(USART2_NewData == 'R')
      {
        youzhuan();
      }
      else if(USART2_NewData == 'S')
      {
        Motor_stop();
      
      }
      else if(USART2_NewData == 'D')
      {
        houtui();
      }     
    }

}


