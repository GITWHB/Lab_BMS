/*
 * TB_PIT.c
 *
 *  Created on: 2017��9��17��
 *      Author: WangHongBo
 */

#include "TB_PIT.h"

//example:    PIT_Init(50000);     //ʱ��Ϊ50MHz,�˴�����ʱ��Ϊ1ms
void PIT0_CH0_Init(uint32_t LDVAL)
{
	//TIMER[x]ָ����ģ���ͨ�����˴�Ϊͨ��0
	PIT_0.TIMER[0].LDVAL.R = LDVAL;    //װ�ؼ�����ֵ
	PIT_0.TIMER[0].TCTRL.B.TIE = 1;    //�ж�ʹ��
	INTC_0.PSR[226].R = 0x800A;        //�ж����ȼ�����
	PIT_0.TIMER[0].TCTRL.B.TEN = 0;    //ֹͣ��ʱ��ģ��
}
void PIT0_CH1_Init(uint32_t LDVAL)
{
	//TIMER[x]ָ����ģ���ͨ�����˴�Ϊͨ��0
	PIT_0.TIMER[1].LDVAL.R = LDVAL;    //װ�ؼ�����ֵ
	PIT_0.TIMER[1].TCTRL.B.TIE = 1;    //�ж�ʹ��
	INTC_0.PSR[227].R = 0x800B;        //�ж����ȼ�����
	PIT_0.TIMER[1].TCTRL.B.TEN = 0;    //ֹͣ��ʱ��ģ��
}
