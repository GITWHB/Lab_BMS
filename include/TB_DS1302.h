/*
 * TB_DS1302.h
 *
 *  Created on: 2017Äê9ÔÂ27ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_DS1302_H_
#define TB_DS1302_H_

#include "project.h"

#define DS1302_RST_high     SIUL2.GPDO[PD1].R  = 1
#define DS1302_RST_low      SIUL2.GPDO[PD1].R  = 0

#define DS1302_DATA_high    SIUL2.GPDO[PD0].R  = 1
#define DS1302_DATA_low     SIUL2.GPDO[PD0].R  = 0

#define DS1302_SCK_high     SIUL2.GPDO[PB6].R  = 1
#define DS1302_SCK_low      SIUL2.GPDO[PB6].R  = 0

#define DS1302_DATA_Read    SIUL2.GPDI[PD0].R

void DS1302_Init();
void DS1302_Read();
void delay_10us();

#endif /* TB_DS1302_H_ */
