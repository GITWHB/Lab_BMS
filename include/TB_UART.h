/*
 * TB_UART.h
 *
 *  Created on: 2017Äê10ÔÂ15ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_UART_H_
#define TB_UART_H_

#include "project.h"

#define UART_DTFTFF             0x0002 /* Data transmit complete */
#define UART_DRFRFE             0x0004 /* Data reception complete */
#define MAXLENGTH 				30

void UART0_Init(unsigned int MegaHertz, unsigned int BaudRate);
void UART0_Send(uint8_t Data);
void UART0_SendStr(char *str);
unsigned char UART0_Rec();
void UART1_Init(unsigned int MegaHertz, unsigned int BaudRate);
void UART1_Send(uint8_t Data);
void UART1_SendStr(char *str);
unsigned char UART1_Rec();

#define RXD_485_Enable    SIUL2.GPDO[PA5].R  = 0;
#define TXD_485_Enable    SIUL2.GPDO[PA5].R  = 1;

#endif /* TB_UART_H_ */
