
#include "usart2.h"

 u8 mode_data[8];
 u8 six_data_stop[3]={0X59,0X59,0X59};  //ֹͣ��������
 u8 six_data_start[3]={0X58,0X58,0X58};  //������������

/**************************************************************************
�������ܣ�����2��ʼ��
��ڲ�����pclk2:PCLK2 ʱ��Ƶ��(Mhz)    bound:������
����  ֵ����
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO״̬����
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART2->CR1|=1<<8;    //PE�ж�ʹ��
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//��2��������ȼ� 
}

/**************************************************************************
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void)
{	
if(USART2->SR&(1<<5))//���յ�����
	{	  
	 
	 static	int uart_receive=0;//����������ر���
	 uart_receive=USART2->DR; 
		if(uart_receive==0x59)  Flag_sudu=2;  //���ٵ���Ĭ��ֵ��
		if(uart_receive==0x58)  Flag_sudu=1;  //���ٵ�
		
		if(uart_receive==0x00)	
			Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
		else if(uart_receive==0x01)
		{
			
			//while(1){PWMA=6000;PWMB=6000;}
			Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ǰ
		}
			else if(uart_receive==0x05)
			Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////��
		else if(uart_receive==0x02||uart_receive==0x03||uart_receive==0x04)	
			Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;  //��
		else if(uart_receive==0x06||uart_receive==0x07||uart_receive==0x08)	
			Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0; //��
		else 
			Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////ɲ��
	}  											 				 
} 

