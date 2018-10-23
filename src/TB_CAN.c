/*
 * TB_CAN.c
 *
 *  Created on: 2017年9月24日
 *      Author: WangHongBo
 */

#include "TB_CAN.h"

uint32_t  RxCODE;              /* Received message buffer code */
uint32_t  RxID;                /* Received message ID */
uint32_t  RxLENGTH;            /* Recieved message number of data bytes */
uint8_t   RxDATA[8];           /* Received message data string*/
uint32_t  RxTIMESTAMP;         /* Received message time */

//CAN0初始化，LOOPBACK(can.h中定义的)决定了是环回模式(为1)还是正常模式(为0)
void initCAN_0(void)
{
  	 INTC_0.PSR[522].R = 0x8001;  //设置MB0的中断优先级为 1 (0位最低，31位最高)

  	 CAN_0.MCR.B.MDIS = 1;       /* Disable module before selecting clock source*/
  	 CAN_0.CTRL1.B.CLKSRC=0;     /* Clock Source = oscillator clock (40 MHz) */
  	 CAN_0.MCR.B.MDIS = 0;       /* Enable module for config. (Sets FRZ, HALT)*/
  	 while (!CAN_0.MCR.B.FRZACK) {} /* Wait for freeze acknowledge to set */

  	 CAN_0.CTRL1.R = 0x04DB0086;  //数据传输速率的设置
  	 	 	 	 	 	 	 	  /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
  	 	 	 	 	 	 	 	  /* PRESDIV+1 = Fclksrc/Ftq = 40 MHz/8MHz = 5 */
     	 	 	 	 	 	 	  /*    so PRESDIV = 4 */
  	 	 	 	 	 	 	 	  /* PSEG2 = Phase_Seg2 - 1 = 4 - 1 = 3 */
  	 	 	 	 	 	 	 	  /* PSEG1 = PSEG2 = 3 */
  	 	 	 	 	 	 	 	  /* PROPSEG= Prop_Seg - 1 = 7 - 1 = 6 */
  	 	 	 	 	 	 	 	  /* RJW = Resync Jump Width - 1 = 4 = 1 */
  	 	 	 	 	 	 	 	  /* SMP = 1: use 3 bits per CAN sample */

  	#if LOOPBACK   					  //为1 时，是环回模式
  	  CAN_0.CTRL1.B.LPB = 1;		  //使能环回模式
  	  CAN_0.MB[4].CS.B.CODE = 0;      //设置MB[4]位未激活状态
  	  CAN_0.MB[4].CS.B.IDE = 0;       //IDE为0，说明是标准帧;为1，说明是扩展帧
  	  CAN_0.MB[4].ID.B.ID_STD = 0x666;//结合RXMGMASK完成过滤作用
  	  CAN_0.MB[4].CS.B.CODE = 4;      //CODE写入4，将MB[4]的状态设置为Empty
  	  CAN_0.RXMGMASK.R = 0x00000000;  //全局接收过滤设置
  	#endif

  	  CAN_0.MB[0].CS.B.CODE = 0;	  //设置MB[0]位未激活状态
  	  CAN_0.MB[0].CS.B.IDE = 0;       //IDE为0，说明是标准帧;为1，说明是扩展帧
  	  CAN_0.MB[0].ID.B.ID_STD = 0x555;//该寄存器用于设置对应的ID
  	  CAN_0.MB[0].CS.B.CODE = 4;      //CODE写入4，将MB[0]的状态设置为Empty
  	  //全局过滤器，为0时不过滤对应位，为1时过滤，0x1FFFFFFF为全部过滤，即必须完全一样
  	  //标准帧时，RXMGMASK的高十一位，对应ID_STD的十一位，1过滤，0不过滤
  	  CAN_0.RXMGMASK.R = 0x00000000;   //当前状态为*全*不*过滤*

  	  //引脚配置，PB0为输出，CAN的TXD
  	  SIUL2.MSCR[PB0].B.SSS = 1; //PTB0 is for CAN0_TX. Select signal source select to CAN0_TX
  	  SIUL2.MSCR[PB0].B.OBE = 1; //Set pin to output. Enable output buffer
  	  SIUL2.MSCR[PB0].B.SRC = 3; //Maximum slew rate

      //引脚配置，PB1为输入，CAN的RXD
  	  SIUL2.MSCR[PB1].B.IBE = 1; //PB1 is CAN0_RX pin. Enable input buffer
  	  //0b是二进制的意思
  	  SIUL2.IMCR[32].B.SSS = 0b0010; //Set PB1 as CAN0_RX.



  	  CAN_0.MCR.R = 0x0000001;       /* Negate FlexCAN 0 halt state for 1 MB */
  	  while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY) {} /* Wait to clear */

  	  CAN_0.IMASK1.R = 0x00000001;    //中断使能  MB0
}
//发送数据函数;一次发送的数据最多不能超过8个字节
void CAN_Trans(uint8_t Data_length,uint8_t TxData[])
{
	uint8_t	i;
	CAN_0.MB[0].CS.B.IDE = 0;       	 //标准帧
	CAN_0.MB[0].ID.B.ID_STD = 0x666;	 //报文的ID
	CAN_0.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_0.MB[0].CS.B.DLC = Data_length ; //要发送的长度
 	for (i=0; i<Data_length; i++)
	{
 		//注意:DATA.B[i]该寄存器最多可以存8个字节的数据
 		CAN_0.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_0.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_0.MB[0].CS.B.CODE =0xC;   /* Activate msg. buf. to transmit data frame */
}
//环回模式下的接收函数
void CAN_Rec_LoopBack()
{
	 uint8_t j;
	 uint32_t dummy;

	 while (CAN_0.IFLAG1.B.BUF0I != 1) {};  /* Wait for CAN 0 MB 4 flag */
	  RxCODE   = CAN_0.MB[0].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
	  RxID     = CAN_0.MB[0].ID.B.ID_STD;
	  RxLENGTH = CAN_0.MB[0].CS.B.DLC;
	  for (j=0; j<RxLENGTH; j++) {
	    RxDATA[j] = CAN_0.MB[0].DATA.B[j];
	  }
	  RxTIMESTAMP = CAN_0.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_0.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
	  CAN_0.IFLAG1.R = 0x00000001;       /* Clear CAN 0 MB 4 flag */
}
//正常模式下的接收函数Buff存的是及收到的数据
void CAN_Rec_Interrupt(uint32_t *RxCODE_T,uint32_t *RxID_T,uint32_t *Length,uint8_t *Buff)
{
	uint32_t j,RxTIMER_T,dummy;

	  *RxCODE_T   = CAN_0.MB[0].CS.B.CODE;   //CODE寄存器有4位，用于只是对应MB的状态，未激活/空/满/被覆盖......
	  *RxID_T     = CAN_0.MB[0].ID.B.ID_STD; //报文ID
	  *Length     = CAN_0.MB[0].CS.B.DLC;    //数据长度
	  if(*RxID_T != 0x666 )
	  {
		  for (j=0; j<*Length; j++)
		  	  {
			  	  Buff[j] = CAN_0.MB[0].DATA.B[j];
		  	  }
	  }
	  RxTIMER_T = CAN_0.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_0.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
}

//发送报文函数;一次发送的数据最多不能超过8个字节
void CAN_Trans_Message(int ID_Message, uint8_t Data_length, uint8_t TxData[])
{
	uint8_t	i;
	CAN_0.MB[0].CS.B.IDE = 1;       	 //1:扩展帧    29位
	CAN_0.MB[0].ID.B.ID_STD = 0x666;	 //标准ID
	CAN_0.MB[0].ID.B.ID_EXT = 0;		 //扩展ID
	CAN_0.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_0.MB[0].CS.B.DLC = Data_length ; //要发送的长度
 	for (i=0; i<Data_length; i++)
	{
 		//注意:DATA.B[i]该寄存器最多可以存8个字节的数据
 		CAN_0.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_0.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_0.MB[0].CS.B.CODE =0xC;   //无条件发送一次数据


}
