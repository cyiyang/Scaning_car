#include "bluetooth.h"
#include "stdio.h"

uint8_t USART2_RX_BUF;//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART2_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART2_NewData;//当前串口中断接收的1个字节数据的缓存
uint16_t Rx_statu = 0;


void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//串口中断回调函数
{
    if(huart->Instance == USART2)
    {
        
        Rx_statu = 1;
        
        run_prg();
        printf("OK,right!");
       
       //HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //因为每执行完一次中断回调函数会将接收中断功能关闭，所以最后需要再开启接收中断
        
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


