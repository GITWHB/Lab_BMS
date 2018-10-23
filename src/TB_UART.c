/*
 * TB_UART.c
 *
 *  Created on: 2017��10��15��
 *      Author: WangHongBo
 */


//ע��   ���԰���    232�õ���UART0   485�õ���UART1
//ʹ��485ʱ�ǵöԷ���/���յĿ������Ž��п���
//��������  485 Ĭ������Ϊ����ʹ��       ��UART1_Init()���������һ��
#include "TB_UART.h"
#include "string.h"

unsigned char UARTFirstTransmitFlag_0;
unsigned char UARTFirstTransmitFlag_1;
//example:	UART_Init(100,9600);
void UART0_Init(unsigned int MegaHertz, unsigned int BaudRate)
{
	  unsigned int Fraction;
	  unsigned int Integer;

	  INTC_0.PSR[376].R = 0x8001;  //����MB0���ж����ȼ�Ϊ 1 (0λ��ͣ�31λ���)
	  //��Щ�Ĵ���ֻ���ڳ�ʼ��ģʽ(Initialization Mode)���趨
	  LINFlexD_0.LINCR1.B.INIT = 1;     /* Enter Initialization Mode */
	  LINFlexD_0.LINCR1.B.SLEEP = 0;    /* Exit Sleep Mode */
	  LINFlexD_0.UARTCR.B.UART = 1;     /* UART Enable- Req'd before UART config.*/
	  LINFlexD_0.UARTCR.R = 0x0033;     /* UART Ena, 1 byte tx, no parity, 8 data*/
	  LINFlexD_0.UARTSR.B.SZF = 1;      /* CHANGE THIS LINE   Clear the Zero status bit */
	  LINFlexD_0.UARTSR.B.DRFRFE = 1;   /* CHANGE THIS LINE  Clear DRFRFE flag - W1C */
	  //�����ʵ����������
	  BaudRate  = (MegaHertz * 1000000) / BaudRate;
	  Integer   = BaudRate / 16;
	  Fraction  = BaudRate - (Integer * 16);

	  LINFlexD_0.LINIBRR.R = Integer;
	  LINFlexD_0.LINFBRR.R = Fraction;


	  LINFlexD_0.LINCR1.B.INIT = 0;     /* Exit Initialization Mode */

	  LINFlexD_0.LINIER.B.DRIE = 1;     //ʹ�����ݽ�������ж�

	  UARTFirstTransmitFlag_0 = 1;        /* Indicate no Tx has taken place yet */
      //���ų�ʼ��
	  /* Configure LINFlexD_0 TxD Pin. */
	  SIUL2.MSCR[PB2].B.SSS = 0b0001; //Pad PF14: Set to LINFlex_0 TxD. Must choose this option because F14 leads to LIN PHY of motherboard
	  SIUL2.MSCR[PB2].B.OBE = 1; //Enable output buffer
	  SIUL2.MSCR[PB2].B.SRC = 3; //Full drive-strength without slew rate control

	  /* Configure LINFlexD_0 RxD Pin. */
	  SIUL2.MSCR[PB3].B.IBE = 1; //Pad PF15: Enable input buffer
	  SIUL2.IMCR[165].B.SSS = 0b0001; //Connect LINFlexD_0 signal to PTB3
}

void UART0_Send(uint8_t Data)
{
	if( UARTFirstTransmitFlag_0 )   {         /* 1st byte transmit after init: */
	    UARTFirstTransmitFlag_0 = 0;            /* Clear variable */
	  }
	  else {                                  /* Normal tranmit (not 1st time): */
	    while (LINFlexD_0.UARTSR.B.DTFTFF == 0); /* Wait for data trans complete*/
	    LINFlexD_0.UARTSR.R &= UART_DTFTFF;      /* Clear DTFTFF flag - W1C */
	  }
	  LINFlexD_0.BDRL.B.DATA0 = Data;            /* Transmit 8 bits Data */
}
void UART0_SendStr(char *str)
{
	unsigned char i=0;
	for(i=0;i<strlen(str);i++)
	{
		UART0_Send(str[i]);
	}
}
unsigned char UART0_Rec()
{
	 while (LINFlexD_0.UARTSR.B.DRFRFE == 0); /* Wait for dta reception complete*/
	  LINFlexD_0.UARTSR.R &= UART_DRFRFE;      /* Clear data receptoin flag W1C */
	  return( LINFlexD_0.BDRM.B.DATA4 );       /* Read byte of Data */
}

void UART1_Init(unsigned int MegaHertz, unsigned int BaudRate)
{
	  unsigned int Fraction;
	  unsigned int Integer;

	  INTC_0.PSR[380].R = 0x8002;  //����MB0���ж����ȼ�Ϊ 1 (0λ��ͣ�31λ���)
	  //��Щ�Ĵ���ֻ���ڳ�ʼ��ģʽ(Initialization Mode)���趨
	  LINFlexD_1.LINCR1.B.INIT = 1;     /* Enter Initialization Mode */
	  LINFlexD_1.LINCR1.B.SLEEP = 0;    /* Exit Sleep Mode */
	  LINFlexD_1.UARTCR.B.UART = 1;     /* UART Enable- Req'd before UART config.*/
	  LINFlexD_1.UARTCR.R = 0x0033;     /* UART Ena, 1 byte tx, no parity, 8 data*/
	  LINFlexD_1.UARTSR.B.SZF = 1;      /* CHANGE THIS LINE   Clear the Zero status bit */
	  LINFlexD_1.UARTSR.B.DRFRFE = 1;   /* CHANGE THIS LINE  Clear DRFRFE flag - W1C */
	  //�����ʵ����������
	  BaudRate  = (MegaHertz * 1000000) / BaudRate;
	  Integer   = BaudRate / 16;
	  Fraction  = BaudRate - (Integer * 16);

	  LINFlexD_1.LINIBRR.R = Integer;
	  LINFlexD_1.LINFBRR.R = Fraction;


	  LINFlexD_1.LINCR1.B.INIT = 0;     /* Exit Initialization Mode */

	  LINFlexD_1.LINIER.B.DRIE = 1;     //ʹ�����ݽ�������ж�

	  UARTFirstTransmitFlag_1 = 1;        /* Indicate no Tx has taken place yet */
      //���ų�ʼ��
	  /* Configure LINFlexD_1 TxD Pin. */
	  SIUL2.MSCR[PD9].B.SSS = 0b0010; //Pad PF14: Set to LINFlex_1 TxD. Must choose this option because F14 leads to LIN PHY of motherboard
	  SIUL2.MSCR[PD9].B.OBE = 1; //Enable output buffer
	  SIUL2.MSCR[PD9].B.SRC = 3; //Full drive-strength without slew rate control

	  /* Configure LINFlexD_1 RxD Pin. */
	  SIUL2.MSCR[PD12].B.IBE = 1; //Pad PF15: Enable input buffer
	  SIUL2.IMCR[166].B.SSS = 0b0010; //Connect LINFlexD_1 signal to PTD12
	  //485����/���Ϳ�������
	  SIUL2.MSCR[PA5].B.OBE  = 1;
	  RXD_485_Enable;       //Ĭ������Ϊ����ʹ��
}

void UART1_Send(uint8_t Data)
{
	if( UARTFirstTransmitFlag_1 )   {         /* 1st byte transmit after init: */
	    UARTFirstTransmitFlag_1 = 0;            /* Clear variable */
	  }
	  else {                                  /* Normal tranmit (not 1st time): */
	    while (LINFlexD_1.UARTSR.B.DTFTFF == 0); /* Wait for data trans complete*/
	    LINFlexD_1.UARTSR.R &= UART_DTFTFF;      /* Clear DTFTFF flag - W1C */
	  }
	  LINFlexD_1.BDRL.B.DATA0 = Data;            /* Transmit 8 bits Data */
}
void UART1_SendStr(char *str)
{
	unsigned char i=0;
	for(i=0;i<strlen(str);i++)
	{
		UART1_Send(str[i]);
	}
}
unsigned char UART1_Rec()
{
	 while (LINFlexD_1.UARTSR.B.DRFRFE == 0); /* Wait for dta reception complete*/
	  LINFlexD_1.UARTSR.R &= UART_DRFRFE;      /* Clear data receptoin flag W1C */
	  return( LINFlexD_1.BDRM.B.DATA4 );       /* Read byte of Data */
}
