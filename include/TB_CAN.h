/*
 * TB_CAN.h
 *
 *  Created on: 2017年9月24日
 *      Author: WangHongBo
 */

#ifndef TB_CAN_H_
#define TB_CAN_H_

#include "project.h"

#define LOOPBACK      0     //为1是环回模式，为0是正常模式


#define CAN_MCR_MDIS        0x80000000
#define CAN_MCR_FRZ         0x40000000
#define CAN_MCR_FEN         0x20000000
#define CAN_MCR_HALT        0x10000000
#define CAN_MCR_NOTRDY      0x08000000
#define CAN_MCR_SOFTRST     0x02000000
#define CAN_MCR_FRZACK      0x01000000
#define CAN_MCR_WRNEN       0x00200000
#define CAN_MCR_LPMACK      0x00100000
#define CAN_MCR_SRXDIS      0x00020000
#define CAN_MCR_BCC         0x00010000
#define CAN_MCR_LPRIOEN     0x00002000
#define CAN_MCR_AEN         0x00001000




void initCAN_0();
void CAN_Trans(uint8_t Data_length,uint8_t TxData[]);
void CAN_Rec_LoopBack();
void CAN_Rec_Interrupt(uint32_t *RxCODE_T,uint32_t *RxID_T,uint32_t *Length,uint8_t *Buff);

void FlexCAN0_Init();


#endif /* TB_CAN_H_ */
