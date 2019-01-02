/*
 * TB_CAN.c
 *
 *  Created on: 2017��9��24��
 *      Author: WangHongBo
 */

#include "TB_CAN.h"

uint32_t  RxCODE;              /* Received message buffer code */
uint32_t  RxID;                /* Received message ID */
uint32_t  RxLENGTH;            /* Recieved message number of data bytes */
uint8_t   RxDATA[8];           /* Received message data string*/
uint32_t  RxTIMESTAMP;         /* Received message time */

//CAN0��ʼ����LOOPBACK(can.h�ж����)�������ǻ���ģʽ(Ϊ1)��������ģʽ(Ϊ0)
void initCAN_0(void)
{
  	 INTC_0.PSR[522].R = 0x8002;  //����MB0���ж����ȼ�Ϊ 2 (0λ��ͣ�31λ���)

  	 CAN_0.MCR.B.MDIS = 1;       /* Disable module before selecting clock source*/
  	 CAN_0.CTRL1.B.CLKSRC=0;     /* Clock Source = oscillator clock (40 MHz) */
  	 CAN_0.MCR.B.MDIS = 0;       /* Enable module for config. (Sets FRZ, HALT)*/
  	 while (!CAN_0.MCR.B.FRZACK) {} /* Wait for freeze acknowledge to set */

  	 CAN_0.CTRL1.R = 0x04DB0086;  //���ݴ������ʵ�����
  	 	 	 	 	 	 	 	  /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
  	 	 	 	 	 	 	 	  /* PRESDIV+1 = Fclksrc/Ftq = 40 MHz/8MHz = 5 */
     	 	 	 	 	 	 	  /*    so PRESDIV = 4 */
  	 	 	 	 	 	 	 	  /* PSEG2 = Phase_Seg2 - 1 = 4 - 1 = 3 */
  	 	 	 	 	 	 	 	  /* PSEG1 = PSEG2 = 3 */
  	 	 	 	 	 	 	 	  /* PROPSEG= Prop_Seg - 1 = 7 - 1 = 6 */
  	 	 	 	 	 	 	 	  /* RJW = Resync Jump Width - 1 = 4 = 1 */
  	 	 	 	 	 	 	 	  /* SMP = 1: use 3 bits per CAN sample */

  	#if LOOPBACK   					  //Ϊ1 ʱ���ǻ���ģʽ
  	  CAN_0.CTRL1.B.LPB = 1;		  //ʹ�ܻ���ģʽ
  	  CAN_0.MB[4].CS.B.CODE = 0;      //����MB[4]λδ����״̬
  	  CAN_0.MB[4].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_0.MB[4].ID.B.ID_STD = 0x666;//���RXMGMASK��ɹ�������
  	  CAN_0.MB[4].CS.B.CODE = 4;      //CODEд��4����MB[4]��״̬����ΪEmpty
  	  CAN_0.RXMGMASK.R = 0x00000000;  //ȫ�ֽ��չ�������
  	#endif

  	  CAN_0.MB[0].CS.B.CODE = 0;	  //����MB[0]λδ����״̬
  	  CAN_0.MB[0].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_0.MB[0].ID.B.ID_STD = 0x555;//�üĴ����������ö�Ӧ��ID
  	  CAN_0.MB[0].CS.B.CODE = 4;      //CODEд��4����MB[0]��״̬����ΪEmpty
  	  //ȫ�ֹ�������Ϊ0ʱ�����˶�Ӧλ��Ϊ1ʱ���ˣ�0x1FFFFFFFΪȫ�����ˣ���������ȫһ��
  	  //��׼֡ʱ��RXMGMASK�ĸ�ʮһλ����ӦID_STD��ʮһλ��1���ˣ�0������
  	  CAN_0.RXMGMASK.R = 0x00000000;   //��ǰ״̬Ϊ*ȫ*��*����*

  	  //�������ã�PB0Ϊ�����CAN��TXD
  	  SIUL2.MSCR[PB0].B.SSS = 1; //PTB0 is for CAN0_TX. Select signal source select to CAN0_TX
  	  SIUL2.MSCR[PB0].B.OBE = 1; //Set pin to output. Enable output buffer
  	  SIUL2.MSCR[PB0].B.SRC = 3; //Maximum slew rate

      //�������ã�PB1Ϊ���룬CAN��RXD
  	  SIUL2.MSCR[PB1].B.IBE = 1; //PB1 is CAN0_RX pin. Enable input buffer
  	  //0b�Ƕ����Ƶ���˼
  	  SIUL2.IMCR[32].B.SSS = 0b0010; //Set PB1 as CAN0_RX.



  	  CAN_0.MCR.R = 0x0000001;       /* Negate FlexCAN 0 halt state for 1 MB */
  	  while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY) {} /* Wait to clear */

  	  CAN_0.IMASK1.R = 0x00000001;    //�ж�ʹ��  MB0
}
void initCAN_1(void)
{
  	 INTC_0.PSR[535].R = 0x8001;  //����MB0���ж����ȼ�Ϊ 1 (0λ��ͣ�31λ���)

  	 CAN_1.MCR.B.MDIS = 1;       /* Disable module before selecting clock source*/
  	 CAN_1.CTRL1.B.CLKSRC=0;     /* Clock Source = oscillator clock (40 MHz) */
  	 CAN_1.MCR.B.MDIS = 0;       /* Enable module for config. (Sets FRZ, HALT)*/
  	 while (!CAN_1.MCR.B.FRZACK) {} /* Wait for freeze acknowledge to set */

  	 CAN_1.CTRL1.R = 0x04DB0086;  //���ݴ������ʵ�����
  	 	 	 	 	 	 	 	  /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
  	 	 	 	 	 	 	 	  /* PRESDIV+1 = Fclksrc/Ftq = 40 MHz/8MHz = 5 */
     	 	 	 	 	 	 	  /*    so PRESDIV = 4 */
  	 	 	 	 	 	 	 	  /* PSEG2 = Phase_Seg2 - 1 = 4 - 1 = 3 */
  	 	 	 	 	 	 	 	  /* PSEG1 = PSEG2 = 3 */
  	 	 	 	 	 	 	 	  /* PROPSEG= Prop_Seg - 1 = 7 - 1 = 6 */
  	 	 	 	 	 	 	 	  /* RJW = Resync Jump Width - 1 = 4 = 1 */
  	 	 	 	 	 	 	 	  /* SMP = 1: use 3 bits per CAN sample */

  	#if LOOPBACK   					  //Ϊ1 ʱ���ǻ���ģʽ
  	  CAN_1.CTRL1.B.LPB = 1;		  //ʹ�ܻ���ģʽ
  	  CAN_1.MB[4].CS.B.CODE = 0;      //����MB[4]λδ����״̬
  	  CAN_1.MB[4].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_1.MB[4].ID.B.ID_STD = 0x666;//���RXMGMASK��ɹ�������
  	  CAN_1.MB[4].CS.B.CODE = 4;      //CODEд��4����MB[4]��״̬����ΪEmpty
  	  CAN_1.RXMGMASK.R = 0x00000000;  //ȫ�ֽ��չ�������
  	#endif

  	  CAN_1.MB[0].CS.B.CODE = 0;	  //����MB[0]λδ����״̬
  	  CAN_1.MB[0].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_1.MB[0].ID.B.ID_STD = 0x555;//�üĴ����������ö�Ӧ��ID
  	  CAN_1.MB[0].CS.B.CODE = 4;      //CODEд��4����MB[0]��״̬����ΪEmpty
  	  //ȫ�ֹ�������Ϊ0ʱ�����˶�Ӧλ��Ϊ1ʱ���ˣ�0x1FFFFFFFΪȫ�����ˣ���������ȫһ��
  	  //��׼֡ʱ��RXMGMASK�ĸ�ʮһλ����ӦID_STD��ʮһλ��1���ˣ�0������
  	  CAN_1.RXMGMASK.R = 0x00000000;   //��ǰ״̬Ϊ*ȫ*��*����*

  	  //�������ã�PB0Ϊ�����CAN��TXD
  	  SIUL2.MSCR[PA14].B.SSS = 1; //PTB0 is for CAN0_TX. Select signal source select to CAN0_TX
  	  SIUL2.MSCR[PA14].B.OBE = 1; //Set pin to output. Enable output buffer
  	  SIUL2.MSCR[PA14].B.SRC = 3; //Maximum slew rate

      //�������ã�PB1Ϊ���룬CAN��RXD
  	  SIUL2.MSCR[PA15].B.IBE = 1; //PB1 is CAN0_RX pin. Enable input buffer
  	  //0b�Ƕ����Ƶ���˼
  	  SIUL2.IMCR[33].B.SSS = 0b0001; //Set PB1 as CAN0_RX.



  	  CAN_1.MCR.R = 0x0000001;       /* Negate FlexCAN 0 halt state for 1 MB */
  	  while (CAN_1.MCR.B.FRZACK & CAN_1.MCR.B.NOTRDY) {} /* Wait to clear */

  	  CAN_1.IMASK1.R = 0x00000001;    //�ж�ʹ��  MB0
}
void initCAN_2(void)
{
  	 INTC_0.PSR[548].R = 0x8002;  //����MB0���ж����ȼ�Ϊ 2 (0λ��ͣ�31λ���)

  	 CAN_2.MCR.B.MDIS = 1;       /* Disable module before selecting clock source*/
  	 CAN_2.CTRL1.B.CLKSRC=0;     /* Clock Source = oscillator clock (40 MHz) */
  	 CAN_2.MCR.B.MDIS = 0;       /* Enable module for config. (Sets FRZ, HALT)*/
  	 while (!CAN_2.MCR.B.FRZACK) {} /* Wait for freeze acknowledge to set */

  	 CAN_2.CTRL1.R = 0x04DB0086;  //���ݴ������ʵ�����
  	 	 	 	 	 	 	 	  /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
  	 	 	 	 	 	 	 	  /* PRESDIV+1 = Fclksrc/Ftq = 40 MHz/8MHz = 5 */
     	 	 	 	 	 	 	  /*    so PRESDIV = 4 */
  	 	 	 	 	 	 	 	  /* PSEG2 = Phase_Seg2 - 1 = 4 - 1 = 3 */
  	 	 	 	 	 	 	 	  /* PSEG1 = PSEG2 = 3 */
  	 	 	 	 	 	 	 	  /* PROPSEG= Prop_Seg - 1 = 7 - 1 = 6 */
  	 	 	 	 	 	 	 	  /* RJW = Resync Jump Width - 1 = 4 = 1 */
  	 	 	 	 	 	 	 	  /* SMP = 1: use 3 bits per CAN sample */

  	#if LOOPBACK   					  //Ϊ1 ʱ���ǻ���ģʽ
  	  CAN_2.CTRL1.B.LPB = 1;		  //ʹ�ܻ���ģʽ
  	  CAN_2.MB[4].CS.B.CODE = 0;      //����MB[4]λδ����״̬
  	  CAN_2.MB[4].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_2.MB[4].ID.B.ID_STD = 0x666;//���RXMGMASK��ɹ�������
  	  CAN_2.MB[4].CS.B.CODE = 4;      //CODEд��4����MB[4]��״̬����ΪEmpty
  	  CAN_2.RXMGMASK.R = 0x00000000;  //ȫ�ֽ��չ�������
  	#endif

  	  CAN_2.MB[0].CS.B.CODE = 0;	  //����MB[0]λδ����״̬
  	  CAN_2.MB[0].CS.B.IDE = 0;       //IDEΪ0��˵���Ǳ�׼֡;Ϊ1��˵������չ֡
  	  CAN_2.MB[0].ID.B.ID_STD = 0x555;//�üĴ����������ö�Ӧ��ID
  	  CAN_2.MB[0].CS.B.CODE = 4;      //CODEд��4����MB[0]��״̬����ΪEmpty
  	  //ȫ�ֹ�������Ϊ0ʱ�����˶�Ӧλ��Ϊ1ʱ���ˣ�0x1FFFFFFFΪȫ�����ˣ���������ȫһ��
  	  //��׼֡ʱ��RXMGMASK�ĸ�ʮһλ����ӦID_STD��ʮһλ��1���ˣ�0������
  	  CAN_2.RXMGMASK.R = 0x00000000;   //��ǰ״̬Ϊ*ȫ*��*����*

  	  //�������ã�PF14Ϊ�����CAN2��TXD
  	  SIUL2.MSCR[PF14].B.SSS = 2; //PTF14 is for CAN2_TX. Select signal source select to CAN0_TX
  	  SIUL2.MSCR[PF14].B.OBE = 1; //Set pin to output. Enable output buffer
  	  SIUL2.MSCR[PF14].B.SRC = 3; //Maximum slew rate

      //�������ã�PF15Ϊ���룬CAN��RXD
  	  SIUL2.MSCR[PF15].B.IBE = 1; //PF15 is CAN2_RX pin. Enable input buffer
  	  //0b�Ƕ����Ƶ���˼
  	  SIUL2.IMCR[34].B.SSS = 0b0001; //Set PF15 as CAN2_RX.



  	  CAN_2.MCR.R = 0x0000001;       /* Negate FlexCAN 0 halt state for 1 MB */
  	  while (CAN_2.MCR.B.FRZACK & CAN_2.MCR.B.NOTRDY) {} /* Wait to clear */

  	  CAN_2.IMASK1.R = 0x00000001;    //�ж�ʹ��  MB0
}

//�������ݺ���;һ�η��͵�������಻�ܳ���8���ֽ�
void CAN0_Trans(uint8_t Data_length,uint8_t TxData[])
{
	uint8_t	i;
	CAN_0.MB[0].CS.B.IDE = 0;       	 //��׼֡
	CAN_0.MB[0].ID.B.ID_STD = 0x666;	 //���ĵ�ID
	CAN_0.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_0.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_0.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_0.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_0.MB[0].CS.B.CODE =0xC;   /* Activate msg. buf. to transmit data frame */
}
//�������ݺ���;һ�η��͵�������಻�ܳ���8���ֽ�
void CAN1_Trans(uint8_t Data_length,uint8_t TxData[])
{
	uint8_t	i;
	CAN_1.MB[0].CS.B.IDE = 0;       	 //��׼֡
	CAN_1.MB[0].ID.B.ID_STD = 0x666;	 //���ĵ�ID
	CAN_1.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_1.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_1.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_1.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_1.MB[0].CS.B.CODE =0xC;   /* Activate msg. buf. to transmit data frame */
}
void CAN2_Trans(uint8_t Data_length,uint8_t TxData[])
{
	uint8_t	i;
	CAN_2.MB[0].CS.B.IDE = 0;       	 //��׼֡
	CAN_2.MB[0].ID.B.ID_STD = 0x666;	 //���ĵ�ID
	CAN_2.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_2.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_2.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_2.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_2.MB[0].CS.B.CODE =0xC;   /* Activate msg. buf. to transmit data frame */
}

//����ģʽ�µĽ��պ���
void CAN0_Rec_LoopBack()
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
void CAN1_Rec_LoopBack()
{
	 uint8_t j;
	 uint32_t dummy;

	 while (CAN_1.IFLAG1.B.BUF0I != 1) {};  /* Wait for CAN 0 MB 4 flag */
	  RxCODE   = CAN_1.MB[0].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
	  RxID     = CAN_1.MB[0].ID.B.ID_STD;
	  RxLENGTH = CAN_1.MB[0].CS.B.DLC;
	  for (j=0; j<RxLENGTH; j++) {
	    RxDATA[j] = CAN_1.MB[0].DATA.B[j];
	  }
	  RxTIMESTAMP = CAN_1.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_1.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
	  CAN_1.IFLAG1.R = 0x00000001;       /* Clear CAN 0 MB 4 flag */
}
void CAN2_Rec_LoopBack()
{
	 uint8_t j;
	 uint32_t dummy;

	 while (CAN_2.IFLAG1.B.BUF0I != 1) {};  /* Wait for CAN 2 MB 0 flag */
	  RxCODE   = CAN_2.MB[0].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
	  RxID     = CAN_2.MB[0].ID.B.ID_STD;
	  RxLENGTH = CAN_2.MB[0].CS.B.DLC;
	  for (j=0; j<RxLENGTH; j++) {
	    RxDATA[j] = CAN_2.MB[0].DATA.B[j];
	  }
	  RxTIMESTAMP = CAN_2.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_2.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
	  CAN_2.IFLAG1.R = 0x00000001;       /* Clear CAN 0 MB 4 flag */
}

//����ģʽ�µĽ��պ���Buff����Ǽ��յ�������
void CAN0_Rec_Interrupt(uint32_t *RxCODE_T,uint32_t *RxID_T,uint32_t *Length,uint8_t *Buff)
{
	uint32_t j,RxTIMER_T,dummy;

	  *RxCODE_T   = CAN_0.MB[0].CS.B.CODE;   //CODE�Ĵ�����4λ������ֻ�Ƕ�ӦMB��״̬��δ����/��/��/������......
	  *RxID_T     = CAN_0.MB[0].ID.B.ID_STD; //����ID
	  *Length     = CAN_0.MB[0].CS.B.DLC;    //���ݳ���
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
void CAN1_Rec_Interrupt(uint32_t *RxCODE_T,uint32_t *RxID_T,uint32_t *Length,uint8_t *Buff)
{
	uint32_t j,RxTIMER_T,dummy;

	  *RxCODE_T   = CAN_1.MB[0].CS.B.CODE;   //CODE�Ĵ�����4λ������ֻ�Ƕ�ӦMB��״̬��δ����/��/��/������......
	  *RxID_T     = CAN_1.MB[0].ID.B.ID_STD; //����ID
	  *Length     = CAN_1.MB[0].CS.B.DLC;    //���ݳ���
	  if(*RxID_T != 0x666 )
	  {
		  for (j=0; j<*Length; j++)
		  	  {
			  	  Buff[j] = CAN_1.MB[0].DATA.B[j];
		  	  }
	  }
	  RxTIMER_T = CAN_1.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_1.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
}
void CAN2_Rec_Interrupt(uint32_t *RxCODE_T,uint32_t *RxID_T,uint32_t *Length,uint8_t *Buff)
{
	uint32_t j,RxTIMER_T,dummy;

	  *RxCODE_T   = CAN_2.MB[0].CS.B.CODE;   //CODE�Ĵ�����4λ������ֻ�Ƕ�ӦMB��״̬��δ����/��/��/������......
	  *RxID_T     = CAN_2.MB[0].ID.B.ID_STD; //����ID
	  *Length     = CAN_2.MB[0].CS.B.DLC;    //���ݳ���
	  if(*RxID_T != 0x666 )
	  {
		  for (j=0; j<*Length; j++)
		  	  {
			  	  Buff[j] = CAN_2.MB[0].DATA.B[j];
		  	  }
	  }
	  RxTIMER_T = CAN_2.MB[0].CS.B.TIMESTAMP;
	  dummy = CAN_2.TIMER.R;             /* Read TIMER to unlock message buffers */
	  if(dummy){}
}

//���ͱ��ĺ���;һ�η��͵�������಻�ܳ���8���ֽ�
void CAN0_Trans_Message(int ID_Message, uint8_t Data_length, uint8_t TxData[])
{
	uint8_t	i;
	CAN_0.MB[0].CS.B.IDE = 1;       	 //1:��չ֡    29λ
	CAN_0.MB[0].ID.B.ID_STD = 0x666;	 //��׼ID
	CAN_0.MB[0].ID.B.ID_EXT = 0;		 //��չID
	CAN_0.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_0.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_0.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_0.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_0.MB[0].CS.B.CODE =0xC;   //����������һ������
}
void CAN1_Trans_Message(int ID_Message, uint8_t Data_length, uint8_t TxData[])
{
	uint8_t	i;
	CAN_1.MB[0].CS.B.IDE = 1;       	 //1:��չ֡    29λ
	CAN_1.MB[0].ID.B.ID_STD = 0x666;	 //��׼ID
	CAN_1.MB[0].ID.B.ID_EXT = 0;		 //��չID
	CAN_1.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_1.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_1.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_1.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_1.MB[0].CS.B.CODE =0xC;   //����������һ������
}
void CAN2_Trans_Message(int ID_Message, uint8_t Data_length, uint8_t TxData[])
{
	uint8_t	i;
	CAN_2.MB[0].CS.B.IDE = 1;       	 //1:��չ֡    29λ
	CAN_2.MB[0].ID.B.ID_STD = 0x666;	 //��׼ID
	CAN_2.MB[0].ID.B.ID_EXT = 0;		 //��չID
	CAN_2.MB[0].CS.B.RTR = 0;            /* Data frame, not remote Tx request frame */
 	CAN_2.MB[0].CS.B.DLC = Data_length ; //Ҫ���͵ĳ���
 	for (i=0; i<Data_length; i++)
	{
 		//ע��:DATA.B[i]�üĴ��������Դ�8���ֽڵ�����
 		CAN_2.MB[0].DATA.B[i] = TxData[i];      /* Data to be transmitted */
	}
	CAN_2.MB[0].CS.B.SRR = 1;     /* Tx frame (not req'd for standard frame)*/
	CAN_2.MB[0].CS.B.CODE =0xC;   //����������һ������
}
