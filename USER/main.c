#include "sys.h"
#include "control.h"
#include "RC.h"
#include "led.h"
#include "iic.h"
#include "mpu6050.h"
#include "filter.h"
#include "SEND.H"
u8 Way_Angle=2;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� Ĭ�ϴ��ؿ������˲�
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=0,Flag_Show=1;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //��ʾ�¶�
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
unsigned char ig=1;

int main(void)
{ 
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init(); //���� pc13 led
	
	uart_init(72,115200);          
	//uart2_init(36,9600);          
	MiniBalance_PWM_Init(7199,19);   //=====��ʼ��PWM 500HZ,�������600������� 
	
	IIC_GPIO_Init();
	MPU6050_Init();
	
	
  Timer1_Init(99,7199);           //=====10MS��һ���жϷ�����
	
	TIM2_2PWMin_Init(7200*4-1,20*2-1);  //���ڲ����ʱ�䡣����
	
	while(1)
		{		
			send_data();
			delay_ms(1);
		} 
}
