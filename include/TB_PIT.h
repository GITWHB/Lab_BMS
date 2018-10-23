/*
 * TB_PIT.h
 *
 *  Created on: 2017Äê9ÔÂ17ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_PIT_H_
#define TB_PIT_H_

#include "MPC5744P.h"

#define Start_Pit0_CH0 		PIT_0.TIMER[0].TCTRL.B.TEN = 1
#define Stop_Pit0_CH0 		PIT_0.TIMER[0].TCTRL.B.TEN = 0
#define Start_Pit0_CH1 		PIT_0.TIMER[1].TCTRL.B.TEN = 1
#define Stop_Pit0_CH1 		PIT_0.TIMER[1].TCTRL.B.TEN = 0

void PIT0_CH0_Init(uint32_t LDVAL);
void PIT0_CH1_Init(uint32_t LDVAL);

#endif /* TB_PIT_H_ */
