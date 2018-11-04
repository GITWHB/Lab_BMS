/*
 * TB_ADC.c
 *
 *  Created on: 2017��9��17��
 *      Author: WangHongBo
 */

#include "TB_ADC.h"
//ע:
//���԰�V1.0�˿ڶ�Ӧ:
//ADC1_CH2	IDC1	����
//ADC1_CH3	ADT1	�¶�
//��ͨ��ʱ����Ҫ�ĵĵط�:
//void     ADC1_CH3_PinInit()   �е����ź�
//uint16_t ADC1_CH3_ReadData()  �е�ͨ����
void ADC1_CH3_PinInit()
{
	SIUL2.MSCR[PC0].B.APC = 1;       //��ģ�����뿪��
	ADC_1.NCMR0.B.CH3     = 1;       //ʹ����ͨ����
}
void ADC1_CH2_PinInit()
{
	SIUL2.MSCR[PB15].B.APC = 1;       //��ģ�����뿪��
	ADC_1.NCMR0.B.CH2     = 1;        //ʹ����ͨ����
}
uint32_t ADC1_Calibration()
{
	uint32_t ADC1_calibration_Failed = 1;
	ADC_1.MCR.B.PWDN      = 1;       //�ڿ�ʼУ��֮ǰ  Power Down
	ADC_1.MCR.B.ADCLKSEL = 0;       //ADC_Clock = Bus_Clock/2

	ADC_1.CALBISTREG.B.TEST_EN = 1;  //ʹ��У��
	ADC_1.MCR.B.PWDN      = 0;       //Power Up ��   ��ʼ У��
	while(ADC_1.CALBISTREG.B.C_T_BUSY);
	if(ADC_1.MSR.B.CALIBRTD)
	{
		ADC1_calibration_Failed = 0;
	}
	else
	{
		ADC1_calibration_Failed = 1;
	}
	return ADC1_calibration_Failed;
}
void ADC1_Init()
{
	ADC_1.MCR.B.PWDN     = 1;      //Power Down
	ADC_1.MCR.B.WLSIDE	 = 0;	   //ת������Ҷ���
	ADC_1.MCR.B.OWREN    = 1;      //ת�����ݿ���д
	ADC_1.MCR.B.MODE     = 0;      //����ģʽ
	ADC_1.MCR.B.ADCLKSEL = 1;      //ADC_Clock = Bus Clock
	ADC_1.MCR.B.PWDN     = 0;      //Power Up
}
void ADC1_StartConvert()
{
	while(ADC_1.MSR.B.NSTART);  //�ȴ����ڽ��е�ת������
	ADC_1.MCR.B.NSTART = 1;     //��ʼת��
}
double ADC1_CH3_ReadData()
{
	uint16_t temp;
	double t, result_mv = 0;
	while(!ADC_1.ISR.B.EOC);
	temp = ADC_1.CDR[3].B.CDATA;//��ȡת�����      CDR[x],����x��Ӧ����ͨ����
	//ת��ΪmV����Ϊ��12λAD���������Ϊ0xFFF
	t = ADC_VREF * temp;
	result_mv = (double)( t / (double)0xFFF);

	return result_mv;
}
double ADC1_CH2_ReadData()
{
	uint16_t temp;
	double t, result_mv = 0;
	while(!ADC_1.ISR.B.EOC);
	temp = ADC_1.CDR[2].B.CDATA;//��ȡת�����      CDR[x],����x��Ӧ����ͨ����
	//ת��ΪmV����Ϊ��12λAD���������Ϊ0xFFF
	t = ADC_VREF * temp;
	result_mv = (double)( t / (double)0xFFF);

	return result_mv;
}
