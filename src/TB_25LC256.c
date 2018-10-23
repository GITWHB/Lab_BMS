/*
 * TB_25LC256.c
 *
 *  Created on: 2017��10��13��
 *      Author: WangHongBo
 */
#include "TB_25LC256.h"
#include "string.h"

static void delay_100ns(unsigned char N)
{
	unsigned char t=2;
	while(N--)
	{
		while(t--);
	}
}
//SPI_0  ���ų�ʼ��
void SPI_25LC256_Pin_Init()
{
	//PC4 CS0
	SIUL2.MSCR[PC4].B.SSS = 0b0001;
	SIUL2.MSCR[PC4].B.OBE = 1;
	SIUL2.MSCR[PC4].B.SRC = 3;

	//��Ϊ�ӻ�ʱ���õ�
	/*SIUL2.MSCR[PC4].B.SSS = 0b0001;
	  SIUL2.MSCR[PC4].B.IBE = 1;*/

	//PC5 SCK
	SIUL2.MSCR[PC5].B.SSS = 1;
	SIUL2.MSCR[PC5].B.OBE = 1;
	SIUL2.MSCR[PC5].B.SRC = 3;
	//��Ϊ�ӻ�ʱ�õ�
	/*SIUL2.MSCR[PC5].B.SSS = 1;
	  SIUL2.MSCR[PC5].B.IBE = 1;*/

	//PC6 SOUT
	SIUL2.MSCR[PC6].B.SSS = 1;
	SIUL2.MSCR[PC6].B.OBE = 1;
	SIUL2.MSCR[PC6].B.SRC = 3;

	//PC7 SIN
	SIUL2.IMCR[41].B.SSS  = 0b0001;
	SIUL2.MSCR[PC7].B.IBE = 1;
	SIUL2.MSCR[PC7].B.PUE = 1;    //����/����ʹ��
	SIUL2.MSCR[PC7].B.PUS = 1;    //����Ϊ����

	//PD2 HOLD
	SIUL2.MSCR[PD2].B.OBE = 1;
	SIUL2.GPDO[PD2].R     = 1;
}
//SPI_0  ���ܼĴ�����ʼ��
void SPI_25LC256_Init()
{
	SPI_0.MCR.R = 0x80010001;                //����Ϊ����,��������CLK�źţ���ֹ���ݵ�λ���ִ���
	SPI_0.MODE.CTAR[0].R = 0x3E02100D;//0x3E661884; //ÿ֡8λ����λ�ȷ���������ΪFp/80
	//SPI_0.RSER.B.RFDF_RE = 1;                //�ж���������
	//SPI_0.RSER.B.RFDF_DIRS = 0;              //ѡ��ΪFIFO�ж�����
	//INTC_0.PSR[263].R = 0x800B;              //�ж����ȼ�����

	SPI_0.MCR.B.HALT = 0x0;                  //��ʼ����

}
//SPI_0  ���ݽ��պ���
unsigned char SPI_25LC256_DataRec()
{
	unsigned char RecDataMaster;
 	while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	RecDataMaster = SPI_0.POPR.R;            //��ȡ�������յ�������
	SPI_0.SR.R = 0xFCFE0000;
	return RecDataMaster;
}
//SPI_0  ���͵�������
void SPI_25LC256_DataSend(uint8_t Data_Tx)
{
	unsigned int R_temp = 0;

	SPI_0.PUSHR.PUSHR.R  =  0x08010000 | (Data_Tx&0x0000FFFF);     /* Transmit data from master to slave SPI with EOQ */
	while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	R_temp = SPI_0.POPR.R;
	SPI_0.SR.B.RFDF = 1;
}
//SPI_0  �������Ͷ������
void SPI_25LC256_Send_Continuous(uint8_t *Data_Tx, uint8_t length)
{
	uint8_t i=0;
	unsigned int R_temp;
	//����(length-1)������
	for(i=0; i<(length-1);i++)
	{
		//SPI_0.SR.B.TCF = 1;
		SPI_0.PUSHR.PUSHR.R  = 0x80010000 | (Data_Tx[i] & 0x0000FFFF);
		while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	    R_temp = SPI_0.POPR.R;
		SPI_0.SR.B.RFDF = 1;
	}

	//�������1������

	SPI_0.PUSHR.PUSHR.R  = 0x08010000|(Data_Tx[length-1] & 0x0000FFFF);
	while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
    R_temp = SPI_0.POPR.R;
	SPI_0.SR.B.RFDF = 1;

}
void SPI_25LC256_WriteMul(short addr, unsigned int num, char* src)
{
	 int i,temp=0;
	 unsigned int R_temp = 0;

	 SPI_0.PUSHR.PUSHR.R  =  0x08010000 | (0x06&0x0000FFFF);     /* Transmit data from master to slave SPI with EOQ */
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (0x02&0x0000FFFF);/* Transmit data from master to slave SPI with EOQ */
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 temp = ((addr&0xFF00)>>8);

	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);/* Transmit data from master to slave SPI with EOQ */
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 temp = (addr&0x00FF);

	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);/* Transmit data from master to slave SPI with EOQ */
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 for(i=0;i<(num-1);i++)
	 {
		 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (src[i]&0x0000FFFF);/* Transmit data from master to slave SPI with EOQ */
		 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
		 R_temp = SPI_0.POPR.R;
		 SPI_0.SR.B.RFDF = 1;
	 }
	 SPI_0.PUSHR.PUSHR.R  =  0x08010000 | (src[i]&0x0000FFFF);/* Transmit data from master to slave SPI with EOQ */
	 //while(SPI_0.SR.B.TCF!=1); //Wait for transfer complete
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

}
void SPI_25LC256_ReadMul(short addr,int num,char* des)
{
	 unsigned int temp=0,Data_Rec,i,R_temp;

	 //SPI_0.SR.B.TCF = 1;    //���������λ����
	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (0x03&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ */
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 temp = ((addr&0xFF00)>>8);

	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 temp = (addr&0x00FF);
	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 for(i=0;i<(num-1);i++)
	 {
		 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (0x00&0x0000FFFF);// Transmit data from master to slave SPI with EOQ

		 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
		 Data_Rec = SPI_0.POPR.R;                 //��ȡ�������յ�������
		 SPI_0.SR.B.RFDF = 1;
		 des[i] = Data_Rec;
	 }
	 SPI_0.PUSHR.PUSHR.R  =  0x08010000 | (0x00&0x0000FFFF);
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 Data_Rec = SPI_0.POPR.R;                 //��ȡ�������յ�������
	 SPI_0.SR.B.RFDF = 1;
	 des[i] = Data_Rec;
}
unsigned int SPI_25LC256_ReadSingle(short addr)
{
	 int temp=0;
	 unsigned int R_temp = 0;
	 unsigned int Data_Rec = 0;

	 //SPI_0.SR.B.TCF = 1;    //���������λ����
	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (0x03&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ */
	 //while(SPI_0.SR.B.TCF!=1); //Wait for transfer complete
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	 temp = ((addr&0xFF00)>>8);
	// SPI_0.SR.B.TCF = 1;    //���������λ����
	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ
	// while(SPI_0.SR.B.TCF!=1); //Wait for transfer complete
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;


	 temp = (addr&0x00FF);
	// SPI_0.SR.B.TCF = 1;    //���������λ����
	 SPI_0.PUSHR.PUSHR.R  =  0x80010000 | (temp&0x0000FFFF);   // Transmit data from master to slave SPI with EOQ
	// while(SPI_0.SR.B.TCF!=1); //Wait for transfer complete
	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 R_temp = SPI_0.POPR.R;
	 SPI_0.SR.B.RFDF = 1;

	// SPI_0.SR.B.TCF = 1;    //���������λ����
	 SPI_0.PUSHR.PUSHR.R  =  0x08010000 ;// Transmit data from master to slave SPI with EOQ
	// while(SPI_0.SR.B.TCF!=1); //Wait for transfer complete

	 while (SPI_0.SR.B.RFDF != 1){}           //�ȴ�����FIFO���磬��������������
	 Data_Rec = SPI_0.POPR.R;                 //��ȡ�������յ�������
	 SPI_0.SR.B.RFDF = 1;

	 return Data_Rec;
}
