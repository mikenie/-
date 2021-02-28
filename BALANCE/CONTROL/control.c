#include "control.h"	
#include "PID.h"
#include "led.h"
#include "RC.h"
#include "mpu6050.h"
#include "imu.h"
#include "filter.h"


/*
pwm1 1883 -> 3381   ����ͨ�� 
pwm2 1970 -> 3473 ����ֵ2719  ��� 
pwm3 1937 -> 3440 ����ֵ2689  ����
pwm4 1936 -> 3440 ����ֵ2693  ƫ��
*/

float junzhi(float w_in);
float Roll_last,Pitch_last;
float w_out_filterd;

unsigned char count;

#define pwm1_min 1975
#define pwm1_max 3475
#define pwm1_mid 2720

#define pwm2_min 1887
#define pwm2_max 3392
#define pwm2_mid 2637

#define pwm3_min 1883
#define pwm3_max 3388
#define pwm3_mid 2620

#define pwm4_min 1955
#define pwm4_max 3457
#define pwm4_mid 2715

int duty = 3600;
float w_x,w_y,w_z;
unsigned int a_out,b_out,c_out,d_out;

unsigned char jiesuo=1; //������־
unsigned char stop = 0; //����ͣ�� 
float a_r_hat = 0;
float a_p_hat = 0;
float a_y_hat = 0;
float c_a,c_b;

//�������ƹ���
int TIM1_UP_IRQHandler(void)  
{    
	if(TIM1->SR&0X0001)//5ms��ʱ�ж�
	{   
			TIM1->SR&=~(1<<0);                                       //===�����ʱ��1�жϱ�־λ	
		  
			Prepare_Data();
			IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle); //��Ԫ����̬����
				  
		  if(jiesuo == 1){			
			duty = 3500 +3600.0*(pwm3-pwm3_min)/(pwm3_max-pwm3_min);//���� 				
			a_r_hat = -60.0*(pwm1-pwm1_mid)/(pwm1_max-pwm1_min);//����roll
			a_p_hat = 60.0*(pwm2-pwm2_mid)/(pwm2_max-pwm2_min);//����pitch
		  a_y_hat = -10.0*(pwm4-pwm4_mid)/(pwm4_max-pwm4_min);//����yaw
							
      b_out = duty + rp_pid_i(a_p_hat,Att_Angle.rol,Gyr_rad.Y)+r_y_pid(a_y_hat,Gyr_rad.Z);//����������������������ٷ�����ø�С�����������Ǳ���΢�ֻ��ڣ���������ʱ�䣩��
      d_out = duty - rp_pid_i(a_p_hat,Att_Angle.rol,Gyr_rad.Y)+r_y_pid(a_y_hat,Gyr_rad.Z);			
			
			a_out = duty + rp_pid(a_r_hat,Att_Angle.pit,Gyr_rad.X)-r_y_pid(a_y_hat,Gyr_rad.Z);
			c_out = duty - rp_pid(a_r_hat,Att_Angle.pit,Gyr_rad.X)-r_y_pid(a_y_hat,Gyr_rad.Z);	
								
			limit();   //�޷�
						
			if(pwm3 < 1950) stop = 1; //�������������Ŵ򵽵ף����ӽǶȣ�����һ����˵
			else stop =0;           
			if( (myabs(Att_Angle.rol)>30) | (myabs(Att_Angle.pit)>30) ) stop = 1; //���ƽǶȣ�������
			
			if(stop == 0)        //����				
			set_duty(a_out,b_out,c_out,d_out);	
			
			if(stop == 1) 
			set_duty(3600,3600,3600,3600);//���� 
			
			Led_Flash(); //LED��˸������ץȡʵ��Ƶ�ʡ�
		}
		
	}       	
	 return 0;	  
} 




void limit(void){
	
	  if(a_out> 7100) a_out=7100 ;
	  if(b_out> 7100) b_out=7100 ;
		if(c_out> 7100) c_out=7100 ;
		if(d_out> 7100) d_out=7100 ;
	
}




/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

void set_duty(int width1,int width2,int width3,int width4){
				
   	TIM4->CCR1=width1;
		TIM4->CCR2=width2;
		TIM4->CCR3=width3;
		TIM4->CCR4=width4;
	
}

float junzhi(float w_in){
  static float w[3];
	unsigned char i ;
	float w_out;
	
	for(i=0;i<=2;i++)
	{
		w[i]=w[i+1];
	}
  w[2] = w_in;
  
	for(i=0;i<=2;i++)
	{
	w_out+=w[i];
	}
	w_out = w_out / 3.0;
	return w_out;
}
