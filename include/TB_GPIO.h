/*
 * TB_GPIO.h
 *
 *  Created on: 2017年9月15日
 *      Author: WangHongBo
 */

#ifndef TB_GPIO_H_
#define TB_GPIO_H_

#include "project.h"

#define BOARD   0   	//0  测试板
						//1 SPI单板

#if (BOARD == 1)
	#define LED1_pin                PC10
	#define LED2_pin                PF13
	#define LED3_pin                PE13
#else
	#define LED1_pin                PA8
	#define LED2_pin                PA9
	#define LED3_pin                PA13
#endif
#define LED1_ON    			SIUL2.GPDO[LED1_pin].R   = 0
#define LED2_ON    			SIUL2.GPDO[LED2_pin].R   = 0
#define LED3_ON    			SIUL2.GPDO[LED3_pin].R  = 0

#define LED1_OFF   			SIUL2.GPDO[PC10].R   = 1
#define LED2_OFF  			SIUL2.GPDO[PF13].R   = 1
#define LED3_OFF  			SIUL2.GPDO[PE13].R  = 1

#define PowerHold_high      SIUL2.GPDO[PA11].R  = 1
#define PowerHold_low       SIUL2.GPDO[PA11].R  = 0

#define DO1_CTL_high        SIUL2.GPDO[PC13].R  = 1
#define DO1_CTL_low         SIUL2.GPDO[PC13].R  = 0

#define ONIN_state 			SIUL2.GPDI[PA0].R
#define Extern1_state 		SIUL2.GPDI[PA1].R
#define Relay1_state 	    SIUL2.GPDI[PA6].R
#define Relay2_state 	    SIUL2.GPDI[PA7].R

void gpio_init();

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
