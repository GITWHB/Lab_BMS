/*
 * TB_PIT.c
 *
 *  Created on: 2017年9月17日
 *      Author: WangHongBo
 */

#include "TB_PIT.h"

//example:    PIT_Init(50000);     //时钟为50MHz,此处计数时间为1ms
void PIT0_CH0_Init(uint32_t LDVAL)
{
	//TIMER[x]指的是模块的通道，此处为通道0
	PIT_0.TIMER[0].LDVAL.R = LDVAL;    //装载计数初值
	PIT_0.TIMER[0].TCTRL.B.TIE = 1;    //中断使能
	INTC_0.PSR[226].R = 0x800A;        //中断优先级配置
	PIT_0.TIMER[0].TCTRL.B.TEN = 0;    //停止定时器模块
}
void PIT0_CH1_Init(uint32_t LDVAL)
{
	//TIMER[x]指的是模块的通道，此处为通道0
	PIT_0.TIMER[1].LDVAL.R = LDVAL;    //装载计数初值
	PIT_0.TIMER[1].TCTRL.B.TIE = 1;    //中断使能
	INTC_0.PSR[227].R = 0x800B;        //中断优先级配置
	PIT_0.TIMER[1].TCTRL.B.TEN = 0;    //停止定时器模块
}
