/*
 * TB_DS1302.h
 *
 *  Created on: 2017Äê9ÔÂ27ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_DS1302_H_
#define TB_DS1302_H_

#include "project.h"
#include "TB_common.h"

enum TransDirection
{
	to_module,
	to_user
};

enum Mode
{
	hour_24,
	hour_12
};

enum AMorPM
{
	NoUse,
	AM,
	PM
};

#define MODE hour_12

#if(BOARD == 0)
#define DS1302_RST_pin      PD1
#define DS1302_SCK_pin		PB6
#define DS1302_DATA_pin     PD0
#elif(BOARD == 2)
#define DS1302_RST_pin      PA5
#define DS1302_SCK_pin		PF8
#define DS1302_DATA_pin     PF7
#endif

#define DS1302_RST_high     SIUL2.GPDO[DS1302_RST_pin].R  = 1
#define DS1302_RST_low      SIUL2.GPDO[DS1302_RST_pin].R  = 0

#define DS1302_DATA_high    SIUL2.GPDO[DS1302_DATA_pin].R  = 1
#define DS1302_DATA_low     SIUL2.GPDO[DS1302_DATA_pin].R  = 0

#define DS1302_SCK_high     SIUL2.GPDO[DS1302_SCK_pin].R  = 1
#define DS1302_SCK_low      SIUL2.GPDO[DS1302_SCK_pin].R  = 0

#define DS1302_DATA_Read    SIUL2.GPDI[DS1302_DATA_pin].R

void DS1302_Init();
void DS1302_Read();

#endif /* TB_DS1302_H_ */
