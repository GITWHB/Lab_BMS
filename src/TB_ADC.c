/*
 * TB_ADC.c
 *
 *  Created on: 2017年9月17日
 *      Author: WangHongBo
 */

#include "TB_ADC.h"
//注:
//测试板V1.0端口对应:
//ADC1_CH2	IDC1	电流
//ADC1_CH3	ADT1	温度
//换通道时，需要改的地方:
//void     ADC1_CH3_PinInit()   中的引脚号
//uint16_t ADC1_CH3_ReadData()  中的通道号
void ADC1_CH3_PinInit()
{
	SIUL2.MSCR[PC0].B.APC = 1;       //打开模拟输入开关
	ADC_1.NCMR0.B.CH3     = 1;       //使能普通采样
}
void ADC1_CH2_PinInit()
{
	SIUL2.MSCR[PB15].B.APC = 1;       //打开模拟输入开关
	ADC_1.NCMR0.B.CH2     = 1;        //使能普通采样
}
uint32_t ADC1_Calibration()
{
	uint32_t ADC1_calibration_Failed = 1;
	ADC_1.MCR.B.PWDN      = 1;       //在开始校验之前  Power Down
	ADC_1.MCR.B.ADCLKSEL = 0;       //ADC_Clock = Bus_Clock/2

	ADC_1.CALBISTREG.B.TEST_EN = 1;  //使能校验
	ADC_1.MCR.B.PWDN      = 0;       //Power Up 以   开始 校验
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
	ADC_1.MCR.B.WLSIDE	 = 0;	   //转换结果右对齐
	ADC_1.MCR.B.OWREN    = 1;      //转换数据可重写
	ADC_1.MCR.B.MODE     = 0;      //单次模式
	ADC_1.MCR.B.ADCLKSEL = 1;      //ADC_Clock = Bus Clock
	ADC_1.MCR.B.PWDN     = 0;      //Power Up
}
void ADC1_StartConvert()
{
	while(ADC_1.MSR.B.NSTART);  //等待正在进行的转换结束
	ADC_1.MCR.B.NSTART = 1;     //开始转换
}
double ADC1_CH3_ReadData()
{
	uint16_t temp;
	double t, result_mv = 0;
	while(!ADC_1.ISR.B.EOC);
	temp = ADC_1.CDR[3].B.CDATA;//读取转换结果      CDR[x],其中x对应的是通道号
	//转换为mV，因为是12位AD，所以最大为0xFFF
	t = ADC_VREF * temp;
	result_mv = (double)( t / (double)0xFFF);

	return result_mv;
}
double ADC1_CH2_ReadData()
{
	uint16_t temp;
	double t, result_mv = 0;
	while(!ADC_1.ISR.B.EOC);
	temp = ADC_1.CDR[2].B.CDATA;//读取转换结果      CDR[x],其中x对应的是通道号
	//转换为mV，因为是12位AD，所以最大为0xFFF
	t = ADC_VREF * temp;
	result_mv = (double)( t / (double)0xFFF);

	return result_mv;
}
