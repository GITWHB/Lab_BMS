/*
 * TB_GPIO.c
 *
 *  Created on: 2017��9��15��
 *      Author: WangHongBo
 */

#include "TB_GPIO.h"

void gpio_init()
{
	//���     ���������ʹ�� OBE
	SIUL2.MSCR[LED1_pin].B.OBE  = 1;    //LED1
	SIUL2.MSCR[LED2_pin].B.OBE  = 1;    //LED2
	SIUL2.MSCR[LED3_pin].B.OBE = 1;    //LED3
	SIUL2.MSCR[PA11].B.OBE = 1;    //PowerHold
	SIUL2.MSCR[PC13].B.OBE = 1;    //���̵�����������
    //LEDȫ��
	SIUL2.GPDO[LED1_pin].R  = 1;
	SIUL2.GPDO[LED2_pin].R  = 1;
	SIUL2.GPDO[LED3_pin].R = 1;
	//����     ���뻺����ʹ��IBE
 	SIUL2.MSCR[PA0].B.IBE = 1;    //ONIN�ź�
 	SIUL2.MSCR[PA1].B.IBE = 1;    //�ⲿ����Extern1
 	SIUL2.MSCR[PA6].B.IBE = 1;    //�̵���ͨ�ϼ��1
 	SIUL2.MSCR[PA7].B.IBE = 1;    //�̵���ͨ�ϼ��2
 	/*
 	SIUL2.MSCR[PB7].B.PUE = 1;    //����/����ʹ��
 	SIUL2.MSCR[PB7].B.PUS = 1;    //����Ϊ����
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
