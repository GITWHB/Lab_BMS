/*
 * TB_GPIO.c
 *
 *  Created on: 2017年9月15日
 *      Author: WangHongBo
 */

#include "TB_GPIO.h"

void gpio_init()
{
	//输出     输出缓冲区使能 OBE
	SIUL2.MSCR[LED1_pin].B.OBE  = 1;    //LED1
	SIUL2.MSCR[LED2_pin].B.OBE  = 1;    //LED2
	SIUL2.MSCR[LED3_pin].B.OBE = 1;    //LED3
	SIUL2.MSCR[PA11].B.OBE = 1;    //PowerHold
	SIUL2.MSCR[PC13].B.OBE = 1;    //主继电器控制引脚
    //LED全灭
	SIUL2.GPDO[LED1_pin].R  = 1;
	SIUL2.GPDO[LED2_pin].R  = 1;
	SIUL2.GPDO[LED3_pin].R = 1;
	//输入     输入缓冲区使能IBE
 	SIUL2.MSCR[PA0].B.IBE = 1;    //ONIN信号
 	SIUL2.MSCR[PA1].B.IBE = 1;    //外部输入Extern1
 	SIUL2.MSCR[PA6].B.IBE = 1;    //继电器通断检测1
 	SIUL2.MSCR[PA7].B.IBE = 1;    //继电器通断检测2
 	/*
 	SIUL2.MSCR[PB7].B.PUE = 1;    //上拉/下拉使能
 	SIUL2.MSCR[PB7].B.PUS = 1;    //配置为上拉
 	*/
}
void gpio_turn(void)
{
	SIUL2.GPDO[PB2].R = ~SIUL2.GPDO[PB2].R;
}
vuint32_t gpio_get()
{
	return SIUL2.GPDI[PB7].R;
}
