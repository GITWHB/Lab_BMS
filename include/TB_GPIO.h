/*
 * TB_GPIO.h
 *
 *  Created on: 2017年9月15日
 *      Author: WangHongBo
 */

#ifndef TB_GPIO_H_
#define TB_GPIO_H_

#include "project.h"
#include "TB_common.h"

#if (BOARD == 1)
	#define LED1_pin                PC10
	#define LED2_pin                PF13
	#define LED3_pin                PE13
	#define PowerHold_pin			PA11
	#define ONIN_state_pin			PA0
#elif (BOARD == 0)
	#define LED1_pin                PA8
	#define LED2_pin                PA9
	#define LED3_pin                PA13
	#define PowerHold_pin			PA11
	#define ONIN_state_pin			PA0
#elif (BOARD == 2)
	#define LED1_pin                PA6
	#define LED2_pin                PD1
	#define PowerHold_pin			PE15
	#define ONIN_state_pin			PD8
#endif

#define LED1_ON    			SIUL2.GPDO[LED1_pin].R   = 0
#define LED2_ON    			SIUL2.GPDO[LED2_pin].R   = 0

#if(BOARD != 2)
#define LED3_ON    			SIUL2.GPDO[LED3_pin].R  = 0
#endif

#define LED1_OFF   			SIUL2.GPDO[LED1_pin].R   = 1
#define LED2_OFF  			SIUL2.GPDO[LED2_pin].R   = 1

#if(BOARD != 2)
#define LED3_OFF  			SIUL2.GPDO[LED3_pin].R  = 1
#endif

#define PowerHold_high      SIUL2.GPDO[PowerHold_pin].R  = 1
#define PowerHold_low       SIUL2.GPDO[PowerHold_pin].R  = 0

#define DO1_CTL_high        SIUL2.GPDO[PC13].R  = 1
#define DO1_CTL_low         SIUL2.GPDO[PC13].R  = 0

#define ONIN_state 			SIUL2.GPDI[ONIN_state_pin].R


enum LED_Num
{
	LED1=1,
	LED2,
#if(BOARD != 2)
	LED3
#endif
};


void gpio_init();
void LED_turn(enum LED_Num num);

#endif /* TB_GPIO_H_ */
//测试代码
/*
    	if(Relay1_state == 0 || Relay2_state == 0 ||
    	   Extern1_state== 0)
    	{
    		LED2_ON;
    	}
    	else if(Relay1_state == 1)
    	{
    		LED1_OFF;
    		LED2_OFF;
    		LED3_OFF;
    	}
    	*/
