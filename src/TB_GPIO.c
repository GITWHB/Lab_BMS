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
#if(BOARD != 2)
	SIUL2.MSCR[LED3_pin].B.OBE = 1;    //LED3
#endif
	SIUL2.MSCR[PowerHold_pin].B.OBE = 1;    //PowerHold
    //LEDȫ��
	SIUL2.GPDO[LED1_pin].R  = 1;
	SIUL2.GPDO[LED2_pin].R  = 1;
#if(BOARD != 2)
	SIUL2.GPDO[LED3_pin].R = 1;
#endif
	//����     ���뻺����ʹ��IBE
 	SIUL2.MSCR[ONIN_state_pin].B.IBE = 1;    //ONIN�ź�
 	//SIUL2.MSCR[PA1].B.IBE = 1;    //�ⲿ����Extern1
 	//SIUL2.MSCR[PA6].B.IBE = 1;    //�̵���ͨ�ϼ��1
 	//SIUL2.MSCR[PA7].B.IBE = 1;    //�̵���ͨ�ϼ��2
 	/*
 	SIUL2.MSCR[PB7].B.PUE = 1;    //����/����ʹ��
 	SIUL2.MSCR[PB7].B.PUS = 1;    //����Ϊ����
 	*/
}
void LED_turn(enum LED_Num num)
{
	switch(num)
	{
		case 1:
			SIUL2.GPDO[LED1_pin].R = ~SIUL2.GPDO[LED1_pin].R;
			break;
		case 2:
			SIUL2.GPDO[LED2_pin].R = ~SIUL2.GPDO[LED2_pin].R;
			break;
#if(BOARD != 2)
		case 3:
			SIUL2.GPDO[LED3_pin].R = ~SIUL2.GPDO[LED3_pin].R;
			break;
#endif
		default:
			break;

	}

}
vuint32_t gpio_get()
{
	return SIUL2.GPDI[PB7].R;
}
