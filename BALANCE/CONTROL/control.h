#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265

int TIM1_UP_IRQHandler(void);  

void Get_Angle(void);

int myabs(int a);

extern void set_duty(int width1,int width2,int width3,int width4);
extern unsigned int a_out,b_out,c_out,d_out;
void limit(void); //�޷�

extern int duty; //����

extern float w_x,w_y,w_z; //������ٶ�
extern float Roll_last,Pitch_last;

extern unsigned char jiesuo; //������־
extern unsigned char stop; //����ͣ�� 

extern float a_r_hat ;
extern float a_p_hat ;

extern float w_out_filterd;

#endif

