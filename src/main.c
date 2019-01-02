/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "SysClk.h"
#include "TB_GPIO.h"
#include "TB_PIT.h"
#include "TB_ADC.h"
#include "TB_CAN.h"
#include "TB_DS1302.h"
#include "TB_25LC256.h"
#include "TB_AnSPI.h"
#include "TB_UART.h"
#include "TB_LTC6804.h"
#include "TB_Mul6804.h"
#include <string.h>

//���±�����CAN����ʱ�õ�
uint32_t   R0_CODE,R0_ID,R0_Length;
uint32_t   R1_CODE,R1_ID,R1_Length;
uint32_t   R2_CODE,R2_ID,R2_Length;

uint8_t    Rx0_Buff[8]   = {"123456"};
uint8_t    Rx1_Buff[8]   = {"123456"};
uint8_t    Rx2_Buff[8]   = {"123456"};

uint8_t    Tx_Buff[8]   = {"ABCDEF"};

char saveerr[30][32]=
{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 3,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 4,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 5,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 6,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 7,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 8,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 9,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 10,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 11,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 12,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 13,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 14,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 3,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 4,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 5,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 6,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 7,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 8,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 9,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 10,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 11,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 12,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 13,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 14,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 13,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
 14,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
};

uint8_t    Send_25LC256[10] ={0x03,0x00,0x00,0x00};

unsigned int    Read_25LC256 = 0;  //�����洢��25LC256�ж���������
char       Read_25LC256_buffer[1000] = {'S'};
char       Write_25LC256_buffer[100] = {'A'};
char       DataRec_485[15];   //�����洢��485���յ�������
char	   DataRec_232[MAXLENGTH];	  //�����洢��232���յ�������
unsigned char RecCompleteFlag = 0;    //232������ɱ�־λ��Ϊ1�������
int 	   CellVol[2][12] = {0};//�����洢LTC6804�ɼ��ĵ�ѹ
double     Data_ADC_I = 0;	  //�����洢����ת�����
//delay   ��ʱ����
void delay_test0(unsigned int t);
unsigned char ON_Check();
unsigned char ParseData(char rec, const char* header, unsigned char* index_header, char ValidData[], unsigned char* index_validdata, const char* ender, unsigned char* index_ender);
extern void xcptn_xmpl(void);
//������CAN0�Ľ����жϷ�����
//ע��:���ͻ������Ϻ󶼻�����ж�
void CAN0_Rec_ISR()
{
	//���պ�����ID�����ݳ��ȣ����յ������ݴ洢��Rx_Buff
	CAN0_Rec_Interrupt(&R0_CODE,&R0_ID,&R0_Length,Rx0_Buff);
	CAN_0.IFLAG1.R = 0x00000001;         //��MB0��������־λ
}
//������CAN1�Ľ����жϷ�����
//ע��:���ͻ������Ϻ󶼻�����ж�
void CAN1_Rec_ISR()
{
	//���պ�����ID�����ݳ��ȣ����յ������ݴ洢��Rx_Buff
	CAN1_Rec_Interrupt(&R1_CODE,&R1_ID,&R1_Length,Rx1_Buff);
	CAN_1.IFLAG1.R = 0x00000001;         //��MB0��������־λ
}
//������CAN2�Ľ����жϷ�����
//ע��:���ͻ������Ϻ󶼻�����ж�
void CAN2_Rec_ISR()
{
	//���պ�����ID�����ݳ��ȣ����յ������ݴ洢��Rx_Buff
	CAN2_Rec_Interrupt(&R2_CODE,&R2_ID,&R2_Length,Rx2_Buff);
	CAN_2.IFLAG1.R = 0x00000001;         //��MB0��������־λ
}
//������PIT0ͨ��0�Ķ�ʱ�жϷ�����
void PIT0_CH1_ISR()    //10ms
{
	static char flag = 0;

	if(flag == 0)
	{
		LED2_OFF;
		flag = 1;
	}
	else
	{
		LED2_ON;
		flag = 0;
	}
	LINFlexD_0.UARTSR.R &= UART_DTFTFF;
	PIT_0.TIMER[1].TFLG.B.TIF = 1;      //�������ɱ�־λ
}
//������PIT0ͨ��0�Ķ�ʱ�жϷ�����
void PIT0_CH0_ISR()    //0.1ms
{
	static char flag = 0;
	static short Count_PowerHold = 0;

	if(flag == 0)
	{
		LED1_ON;
		flag = 1;
		//vol_sample(0, CellVol); //����, ���ָ����������
	}
	else
	{
		LED1_OFF;
		flag = 0;
	}
	//vol_sample(0, CellVol); //����, ���ָ����������
	//vol_sample(1, CellVol); //����, ���ָ����������
	//vol_sample_Mul(CellVol); //˳�����

	//��ʱ�ϵ���
	if(ON_Check())
	{
		Count_PowerHold++;
		if(Count_PowerHold>=30000)
		{
			PowerHold_low;
			Count_PowerHold=0;
		}
	}

	PIT_0.TIMER[0].TFLG.B.TIF = 1;      //�������ɱ�־λ
}
//������LINFlex_0(UART) ���жϷ�����   232ͨ�Ż��õ�
void UART0_ISR()
{
	char temp;
	static unsigned char index = 0;
	static unsigned char index_header = 0;
	static unsigned char index_validdata = 0;
	static unsigned char index_ender = 0;
	temp = LINFlexD_0.BDRM.B.DATA4;		//��ȡ����


	if(ParseData(temp, "!$%", &index_header, DataRec_232, &index_validdata, "%*(", &index_ender) &&
	   RecCompleteFlag==0)
	{
		//strcpy(DataRec_232, DataRec);
		LINFlexD_0.BDRL.B.DATA0 = '$';
		RecCompleteFlag = 1;
	}
	//UART0_Send(temp);

	LINFlexD_0.UARTSR.B.DRFRFE = 1;   	//���־λ
}
//������LINFlex_1(UART) ���жϷ�����   485ͨ�Ż��õ�
void UART1_ISR()
{
	char temp;
	static char Index=0;
	temp = LINFlexD_1.BDRM.B.DATA4;		//��ȡ����
	DataRec_485[Index++]=temp;
	if(temp != 't')
	LINFlexD_1.UARTSR.B.DRFRFE = 1;   	//���־λ
	else
	{
		Index=0;
	}
}
//������SPI0 �Ľ����жϷ�����
void SPI_REC_ISR()
{
	unsigned char RecDataMaster;
	RecDataMaster = SPI_0.POPR.R;            //��ȡ�������յ�������
	SPI_0.SR.R = 0xFCFE0000;                 //�����־λ
}

int main(void)
{
	int i=0;
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

    SysClk_Init();
    InitPeriClkGen();

    gpio_init();
    LED1_ON;
    LED2_ON;
//  LED3_OFF;

//  PowerHold_high;				//�ϵ籣��ǰ��
//  DS1302_Init();				//ʱ��ģ���ʼ��
//  UART0_Init(100,9600);			//232ͨ��ģ���ʼ��
/*
    SPI_Pin_Init();
    SPI_Init();					//LTC6804ͨ��SPI��ʼ��
*/
//  PIT0_CH0_Init(50000000);    	//ʱ��Ϊ50MHz,�˴�����ʱ��Ϊ0.1ms   5000
//  Start_Pit0_CH0;				//������ʱ��
/*
	PIT0_CH1_Init(500000);    	//ʱ��Ϊ50MHz,�˴�����ʱ��Ϊ10ms    500000
    Start_Pit0_CH1;				//������ʱ��
*/
    /*
    ADC1_CH2_PinInit();
    ADC1_Calibration();
    ADC1_Init();
     */

    initCAN_0();  //CAN0 ��ʼ��
    //initCAN_2();  //CAN2 ��ʼ��

    //��������while(1)��ѭ��
    while(1)
    {
    	delay_test0(500000);
    	/*
    	ADC1_StartConvert();
    	Data_ADC_I = ADC1_CH2_ReadData();
    	*/
    	//DS1302_Read();
    }

    return 0;
}
//�������ݰ�����
unsigned char ParseData(char rec, const char* header, unsigned char* index_header, char ValidData[], unsigned char* index_validdata, const char* ender, unsigned char* index_ender)
{
	unsigned char header_length = strlen(header);
	unsigned char ender_length = strlen(ender);
	static unsigned char ValidHeadFlag = 0;
	static unsigned char ValidDataFlag = 0;
	int i=0;
	if ((*index_validdata) == MAXLENGTH)
		*index_validdata = 0;
	if ((header == 0) && (ender == 0))
	{
		if ((*index_validdata) == MAXLENGTH)
		{
			*index_validdata = 0;
			return 0;
		}
		else
		{
			ValidData[*index_validdata] = rec;
			(*index_validdata)++;
		}
	}
	else if ((ender != 0) && (header!=0))
	{
		if ((header[*index_header] == rec) && (ValidHeadFlag == 0))
		{
			ValidDataFlag = 0;
			(*index_header)++;
			if ((*index_header) == header_length)
			{
				ValidHeadFlag = 1;
				(*index_header) = 0;
				//���ԭʼ����
				for(i=0; i<MAXLENGTH; ++i)
				{
					ValidData[i] = '\0';
				}
				return 0;
			}
		}
		if (ValidHeadFlag == 1)
		{
			if (rec != ender[*index_ender])
			{
				ValidData[*index_validdata] = rec;
				(*index_validdata)++;
			}
			else
			{
				(*index_ender)++;
				if ((*index_ender) == ender_length)
				{
					ValidData[*index_validdata] = '\0';
					ValidDataFlag = 1;
					(*index_ender) = 0;
					(*index_validdata) = 0;
					ValidHeadFlag = 0;
				}
			}
		}
	}

	return ValidDataFlag;
}
//��ʱ�ϵ纯��
unsigned char ON_Check()
{
	unsigned char StartTimer;
	if(ONIN_state == 1)   //����Կ�׹���
    {
    	StartTimer=1;
    }
    else if(ONIN_state == 0)
    {
    	PowerHold_high;
    	StartTimer=0;
    }

	return StartTimer;
}
void delay_test0(unsigned int t)
{
	int i,j;
	j=1000;     //1000  400us
	for(i=0;i<t;i++)
	{
		while(j > 0)
			j--;
	}
}

