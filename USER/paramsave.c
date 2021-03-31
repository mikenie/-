/*******************************************************************************************
										    �� ��
    ����Ŀ�����������ѧϰʹ�ã�����������ֲ�޸ģ������뱣����������Ϣ����ֲ�����г�������
	
���ɹ�����BUG��������������κ����Ρ��������ã�

* ����汾��V1.01
* �������ڣ�2018-8-18
* �������ߣ���ŭ��С��
* ��Ȩ���У��������������Ϣ�������޹�˾
*******************************************************************************************/
#include "paramsave.h"
#include "flash.h"
#include "pid.h"
#include "usart.h"

#define INT160(dwTemp)       (*( int16_t *)(&dwTemp   	))
#define INT161(dwTemp)       (*((int16_t *)(&dwTemp) + 1))
#define INT162(dwTemp)       (*((int16_t *)(&dwTemp) + 2))
#define INT163(dwTemp)       (*((int16_t *)(&dwTemp) + 3))

PID_SAVE PIDflash;

/******************************************************************************************
* ��  ����void ParamsToTable(void)
* ��  �ܣ���Ҫ������ֵ��Flash�Ĵ洢�ṹ��
* ��  ������
* ����ֵ����
* ��  ע������Flash�Ĵ洢�Ľṹ��Ϊu16������PID����Ϊfloat������λ����
*         ���PID����������1000Ȼ��ǿ��ת��Ϊu16����
*******************************************************************************************/
void ParamsToTable(void)
{
	//��ƫ����
	PIDflash.ACC_OFFSET_X = ACC_OFFSET_RAW.X;
	PIDflash.ACC_OFFSET_Y = ACC_OFFSET_RAW.Y;
	PIDflash.ACC_OFFSET_Z = ACC_OFFSET_RAW.Z; 
	PIDflash.GYRO_OFFSET_X = GYRO_OFFSET_RAW.X;
	PIDflash.GYRO_OFFSET_Y = GYRO_OFFSET_RAW.Y;
	PIDflash.GYRO_OFFSET_Z = GYRO_OFFSET_RAW.Z;
	
	//�ǶȻ�����PID����
	PIDflash.ROL_Angle_P = (u16)(PID_ROL_Angle.P*1000);
	PIDflash.ROL_Angle_I = (u16)(PID_ROL_Angle.I*1000);
	PIDflash.ROL_Angle_D = (u16)(PID_ROL_Angle.D*1000);
	PIDflash.PIT_Angle_P = (u16)(PID_PIT_Angle.P*1000);
	PIDflash.PIT_Angle_I = (u16)(PID_PIT_Angle.I*1000);
	PIDflash.PIT_Angle_D = (u16)(PID_PIT_Angle.D*1000);
	PIDflash.YAW_Angle_P = (u16)(PID_YAW_Angle.P*1000);
	PIDflash.YAW_Angle_I = (u16)(PID_YAW_Angle.I*1000);
	PIDflash.YAW_Angle_D = (u16)(PID_YAW_Angle.D*1000);
	
	//���ٶȻ�PID����
	PIDflash.ROL_Rate_P  = (u16)(PID_ROL_Rate.P*1000);
	PIDflash.ROL_Rate_I  = (u16)(PID_ROL_Rate.I*1000);
	PIDflash.ROL_Rate_D  = (u16)(PID_ROL_Rate.D*1000);
	PIDflash.PIT_Rate_P  = (u16)(PID_PIT_Rate.P*1000);
	PIDflash.PIT_Rate_I  = (u16)(PID_PIT_Rate.I*1000);
	PIDflash.PIT_Rate_D  = (u16)(PID_PIT_Rate.D*1000);
	PIDflash.YAW_Rate_P  = (u16)(PID_YAW_Rate.P*1000);
	PIDflash.YAW_Rate_I  = (u16)(PID_YAW_Rate.I*1000);
	PIDflash.YAW_Rate_D  = (u16)(PID_YAW_Rate.D*1000);
	
	//�߶Ȼ�PID
	PIDflash.ALT_Rate_P = (u16)(PID_ALT_Rate.P*1000);
	PIDflash.ALT_Rate_I = (u16)(PID_ALT_Rate.I*1000);
	PIDflash.ALT_Rate_D = (u16)(PID_ALT_Rate.D*1000);
	PIDflash.ALT_P = (u16)(PID_ALT.P*1000);
	PIDflash.ALT_I = (u16)(PID_ALT.I*1000);
	PIDflash.ALT_D = (u16)(PID_ALT.D*1000);
	
	//�����ȡ��NRF��ַ����ֽ�
	PIDflash.SI24R1addr = SI24R1addr;	
}

/******************************************************************************************
* ��  ����void TableToParams(void)
* ��  �ܣ���Flash�ж����Ĳ�����ֵ����ȫ�ֱ���
* ��  ������
* ����ֵ����
* ��  ע������PID���������ʱ�򶼳���1000�����Զ�ȡ��ʱ�����Ҫ����1000
*******************************************************************************************/
void TableToParams(void)
{
	//��ƫ����
	ACC_OFFSET_RAW.X = PIDflash.ACC_OFFSET_X;
	ACC_OFFSET_RAW.Y = PIDflash.ACC_OFFSET_Y;
	ACC_OFFSET_RAW.Z = PIDflash.ACC_OFFSET_Z;
	GYRO_OFFSET_RAW.X = PIDflash.GYRO_OFFSET_X;
	GYRO_OFFSET_RAW.Y = PIDflash.GYRO_OFFSET_Y;
	GYRO_OFFSET_RAW.Z = PIDflash.GYRO_OFFSET_Z;
	
	//�ǶȻ�����PID����
	PID_ROL_Angle.P = PIDflash.ROL_Angle_P/1000.0f;
	PID_ROL_Angle.I = PIDflash.ROL_Angle_I/1000.0f;
	PID_ROL_Angle.D = PIDflash.ROL_Angle_D/1000.0f;
	PID_PIT_Angle.P = PIDflash.PIT_Angle_P/1000.0f;
	PID_PIT_Angle.I = PIDflash.PIT_Angle_I/1000.0f;
	PID_PIT_Angle.D = PIDflash.PIT_Angle_D/1000.0f;
	PID_YAW_Angle.P = PIDflash.YAW_Angle_P/1000.0f;
	PID_YAW_Angle.I = PIDflash.YAW_Angle_I/1000.0f;
	PID_YAW_Angle.D = PIDflash.YAW_Angle_D/1000.0f;
		
	//���ٶȻ�PID����	
	PID_ROL_Rate.P = PIDflash.ROL_Rate_P/1000.0f;
	PID_ROL_Rate.I = PIDflash.ROL_Rate_I/1000.0f;
	PID_ROL_Rate.D = PIDflash.ROL_Rate_D/1000.0f;
	PID_PIT_Rate.P = PIDflash.PIT_Rate_P/1000.0f;
	PID_PIT_Rate.I = PIDflash.PIT_Rate_I/1000.0f;
	PID_PIT_Rate.D = PIDflash.PIT_Rate_D/1000.0f;
	PID_YAW_Rate.P = PIDflash.YAW_Rate_P/1000.0f;
	PID_YAW_Rate.I = PIDflash.YAW_Rate_I/1000.0f;
	PID_YAW_Rate.D = PIDflash.YAW_Rate_D/1000.0f;
	
	//�߶Ȼ�PID
	PID_ALT_Rate.P = PIDflash.ALT_Rate_P/1000.0f;
	PID_ALT_Rate.I = PIDflash.ALT_Rate_I/1000.0f;
	PID_ALT_Rate.D = PIDflash.ALT_Rate_D/1000.0f;
	PID_ALT.P = PIDflash.ALT_P/1000.0f;
	PID_ALT.I = PIDflash.ALT_I/1000.0f;
	PID_ALT.D = PIDflash.ALT_D/1000.0f;
	
	//�����ȡ��NRF��ַ����ֽ�
	SI24R1addr = PIDflash.SI24R1addr;
}

/******************************************************************************************
* ��  ����void DefaultParams(void)
* ��  �ܣ�Ĭ�ϲ���
* ��  ������
* ����ֵ����
* ��  ע����������������Flash�е����ݶ������˿ɵ��ô˺������³�ʼ������д��Flash
*******************************************************************************************/
void DefaultParams(void)
{          
	//��ƫ����
	PIDflash.ACC_OFFSET_X  = 0;
	PIDflash.ACC_OFFSET_Y  = 0;
	PIDflash.ACC_OFFSET_Z  = 0;
	PIDflash.GYRO_OFFSET_X = 0;
	PIDflash.GYRO_OFFSET_Y = 0;
	PIDflash.GYRO_OFFSET_Z = 0;
	
	//�ǶȻ�����PID����
	PIDflash.ROL_Angle_P = 1800;
	PIDflash.ROL_Angle_I = 8;
	PIDflash.ROL_Angle_D = 50;
	PIDflash.PIT_Angle_P = 1800;
	PIDflash.PIT_Angle_I = 8;
	PIDflash.PIT_Angle_D = 50;
	PIDflash.YAW_Angle_P = 3500;
	PIDflash.YAW_Angle_I = 0;
	PIDflash.YAW_Angle_D = 1000;
	
	//���ٶȻ�PID����
	PIDflash.ROL_Rate_P  = 930;
	PIDflash.ROL_Rate_I  = 5;
	PIDflash.ROL_Rate_D  = 860;
	PIDflash.PIT_Rate_P  = 930;
	PIDflash.PIT_Rate_I  = 5;
	PIDflash.PIT_Rate_D  = 860;
	PIDflash.YAW_Rate_P  = 2000;
	PIDflash.YAW_Rate_I  = 50;
	PIDflash.YAW_Rate_D  = 1000;
	
	//�߶Ȼ�PID
	PIDflash.ALT_Rate_P = 0;
	PIDflash.ALT_Rate_I = 0;
	PIDflash.ALT_Rate_D = 0;
	PIDflash.ALT_P = 0;
	PIDflash.ALT_I = 0;
	PIDflash.ALT_D = 0;            	
}

/************************************************************************
* ��  ����void ParamsClearAll(void)
* ��  �ܣ���Flash�洢�ṹ�����ݶ�����
* ��  ������
* ����ֵ����
* ��  ע����
*************************************************************************/
void ParamsClearAll(void)
{
	//��ƫ����
	PIDflash.ACC_OFFSET_X = 0;
	PIDflash.ACC_OFFSET_Y = 0;
	PIDflash.ACC_OFFSET_Z = 0;
	PIDflash.GYRO_OFFSET_X = 0;
	PIDflash.GYRO_OFFSET_Y = 0;
	PIDflash.GYRO_OFFSET_Z = 0;
	
	//�ǶȻ�����PID����
	PIDflash.ROL_Angle_P = 0;
	PIDflash.ROL_Angle_I = 0;
	PIDflash.ROL_Angle_D = 0;
	PIDflash.PIT_Angle_P = 0;
	PIDflash.PIT_Angle_I = 0;
	PIDflash.PIT_Angle_D = 0;
	PIDflash.YAW_Angle_P = 0;
	PIDflash.YAW_Angle_I = 0;
	PIDflash.YAW_Angle_D = 0;

	//���ٶȻ�PID����	
	PIDflash.ROL_Rate_P = 0;
	PIDflash.ROL_Rate_I = 0; 
	PIDflash.ROL_Rate_D = 0;
	PIDflash.PIT_Rate_P = 0; 
	PIDflash.PIT_Rate_I = 0;
	PIDflash.PIT_Rate_D = 0; 
	PIDflash.YAW_Rate_P = 0;
	PIDflash.YAW_Rate_I = 0; 
	PIDflash.YAW_Rate_D = 0; 

  //�߶Ȼ�PID
	PIDflash.ALT_Rate_P = 0;
	PIDflash.ALT_Rate_I = 0;
	PIDflash.ALT_Rate_D = 0;
	PIDflash.ALT_P = 0;
	PIDflash.ALT_I = 0;
	PIDflash.ALT_D = 0;
	
	//�����ȡ��NRF��ַ����ֽ�
	PIDflash.SI24R1addr = 0;
}

/******************************************************************************************
* ��  ����void PID_ClearFlash(void)
* ��  �ܣ���Flash�еĴ洢������Ԫ���ݶ�����
* ��  ������
* ����ֵ����
* ��  ע����
*******************************************************************************************/
void PID_ClearFlash(void)
{
	u8 size,len;
	ParamsClearAll();//�������
	len =  sizeof(PIDflash);
	size = len/(4+(len%4)?1:0); //��������ݳ���
	STMFLASH_Write(FLASH_SAVE_ADDR,(uint32_t*)(&PIDflash),size);
}

/******************************************************************************************
* ��  ����void PID_WriteFlash(void)
* ��  �ܣ�����Ҫ����д��Flash
* ��  ������
* ����ֵ����
* ��  ע����
*******************************************************************************************/
void PID_WriteFlash(void)
{
	u8 size,len;
	ParamsToTable();//������ת��������
	len =  sizeof(PIDflash);
	size = len/(4+(len%4)?1:0); //��������ݳ���
	STMFLASH_Write(FLASH_SAVE_ADDR,(uint32_t*)(&PIDflash),size);
}

/******************************************************************************************
* ��  ����void ParamsClearAll(void)
* ��  �ܣ���Flash��ȡ����
* ��  ������
* ����ֵ����
* ��  ע����
*******************************************************************************************/
void PID_ReadFlash(void)
{
	u8 size,len;
	len =  sizeof(PIDflash);
	size = len/(4+(len%4)?1:0);//��������ݳ���
	STMFLASH_Read(FLASH_SAVE_ADDR,(uint32_t*)(&PIDflash),size);
	TableToParams();//������ת���ɸ�����
	//��ȡ����ʧ��
	if(PIDflash.PIT_Angle_P ==0xFFFF && PIDflash.ROL_Angle_P==0xFFFF && PIDflash.YAW_Angle_P==0xFFFF)
	{
		
		DefaultParams_WriteFlash();
		printf("Flash Read Error!!!\r\n");
	}
	else
	{
		printf("Flash Read OK!!!\r\n");
	}
	/*
	printf("\r***************PID Angle loop parameter****************\r\n");
	printf("\rPID_ROL_Angle.P = %0.2f\r\n",PID_ROL_Angle.P);
	printf("\rPID_ROL_Angle.I = %0.2f\r\n",PID_ROL_Angle.I);
	printf("\rPID_ROL_Angle.D = %0.2f\r\n",PID_ROL_Angle.D);
	printf("\rPID_PIT_Angle.P = %0.2f\r\n",PID_PIT_Angle.P);
	printf("\rPID_PIT_Angle.I = %0.2f\r\n",PID_PIT_Angle.I);
	printf("\rPID_PIT_Angle.D = %0.2f\r\n",PID_PIT_Angle.D);
	printf("\rPID_YAW_Angle.P = %0.2f\r\n",PID_YAW_Angle.P);
	printf("\rPID_YAW_Angle.I = %0.2f\r\n",PID_YAW_Angle.I);
	printf("\rPID_YAW_Angle.D = %0.2f\r\n",PID_YAW_Angle.D);
	printf("\r***************PID AngleRate loop parameter**************\r\n");
	printf("\rPID_ROL_Rate.P = %0.2f\r\n",PID_ROL_Rate.P );
	printf("\rPID_ROL_Rate.I = %0.2f\r\n",PID_ROL_Rate.I );
	printf("\rPID_ROL_Rate.D = %0.2f\r\n",PID_ROL_Rate.D );
	printf("\rPID_PIT_Rate.P = %0.2f\r\n",PID_PIT_Rate.P );
	printf("\rPID_PIT_Rate.I = %0.2f\r\n",PID_PIT_Rate.I );
	printf("\rPID_PIT_Rate.D = %0.2f\r\n",PID_PIT_Rate.D );
	printf("\rPID_YAW_Rate.P = %0.2f\r\n",PID_YAW_Rate.P );
	printf("\rPID_YAW_Rate.I = %0.2f\r\n",PID_YAW_Rate.I );
	printf("\rPID_YAW_Rate.D = %0.2f\r\n",PID_YAW_Rate.D );
	printf("\r*****************PID ALTRate loop parameter**************\r\n");
	printf("\rPID_ALT_Rate.P = %0.2f\r\n",PID_ALT_Rate.P );
	printf("\rPID_ALT_Rate.I = %0.2f\r\n",PID_ALT_Rate.I );
	printf("\rPID_ALT_Rate.D = %0.2f\r\n",PID_ALT_Rate.D );
	printf("\r********************PID ALT loop parameter****************\r\n");
	printf("\rPID_ALT.P = %0.2f\r\n",PID_ALT.P );
	printf("\rPID_ALT.I = %0.2f\r\n",PID_ALT.I );
	printf("\rPID_ALT.D = %0.2f\r\n",PID_ALT.D );
	printf("\rSI24R1addr = 0x%x\r\n",SI24R1addr);
	*/
}

/******************************************************************************************
* ��  ����void DefaultParams_WriteFlash(void)
* ��  �ܣ���Ĭ��PID����д��Flash
* ��  ������
* ����ֵ����
* ��  ע����
*******************************************************************************************/
void DefaultParams_WriteFlash(void)
{
	u8 size,len;
	DefaultParams();//��ʼ��Ĭ�ϲ���
	len =  sizeof(PIDflash);
	size = len/(4+(len%4)?1:0); //��������ݳ���
	STMFLASH_Write(FLASH_SAVE_ADDR,(uint32_t*)(&PIDflash),size);
}


