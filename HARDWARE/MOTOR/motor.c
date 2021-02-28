#include "motor.h"

void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	RCC->APB1ENR|=1<<2;       //TIM4ʱ��ʹ��    
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��   
  
	GPIOB->CRH&=0XFFFFFF00;   //PORTB8 9�������
	GPIOB->CRH|=0X000000BB;   
	GPIOB->CRL&=0X00FFFFFF;   //PORTB6 7�������
	GPIOB->CRL|=0XBB000000;  
	
	TIM4->ARR=arr;//�趨�������Զ���װֵ 
	TIM4->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM4->CCMR2|=6<<12;//CH4 PWM1ģʽ	
	TIM4->CCMR2|=6<<4; //CH3 PWM1ģʽ	
	TIM4->CCMR2|=1<<11;//CH4Ԥװ��ʹ��	 
	TIM4->CCMR2|=1<<3; //CH3Ԥװ��ʹ��		
	TIM4->CCMR1|=6<<12;//CH2 PWM1ģʽ	
	TIM4->CCMR1|=6<<4; //CH1 PWM1ģʽ	
	TIM4->CCMR1|=1<<11;//CH2Ԥװ��ʹ��	 
	TIM4->CCMR1|=1<<3; //CH1Ԥװ��ʹ��			
	
	TIM4->CCER|=1<<12; //CH4���ʹ��	   
	TIM4->CCER|=1<<8;  //CH3���ʹ��	
	TIM4->CCER|=1<<4;  //CH2���ʹ��	   
	TIM4->CCER|=1<<0;  //CH1���ʹ��	
	
	TIM4->CR1=0x8000;  //ARPEʹ�� 
	TIM4->CR1|=0x01;   //ʹ�ܶ�ʱ��4 										  
} 

