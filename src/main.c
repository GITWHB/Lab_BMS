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

unsigned char StartTimer=0;               //定时器开始定时的标志位
//static unsigned int Count_PowerHold=0;    //定时辅助变量
//以下变量，CAN调试时用到
uint32_t   R_CODE,R_ID,R_Length;
uint8_t    Rx_Buff[8]   = {"123456"};
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

unsigned int    Read_25LC256 = 0;  //用来存储从25LC256中读出的数据
char  FFF = 0;
char       Read_25LC256_buffer[1000] = {'S'};
char       Write_25LC256_buffer[100] = {'A'};
char       DataRec_485[15];   //用来存储从485接收到的数据
int 	   CellVol[2][12] = {0};
//delay   延时函数
void delay_test0(unsigned int t);
extern void xcptn_xmpl(void);
//以下是CAN0的接收中断服务函数
void CAN0_Rec_ISR()
{
	//接收函数，ID，数据长度，接收到的数据存储在Rx_Buff
	CAN_Rec_Interrupt(&R_CODE,&R_ID,&R_Length,Rx_Buff);
	CAN_0.IFLAG1.R = 0x00000001;         //清MB0缓冲区标志位
}
//以下是PIT0通道0的定时中断服务函数
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
	PIT_0.TIMER[1].TFLG.B.TIF = 1;      //清计数完成标志位
}
//以下是PIT0通道0的定时中断服务函数
void PIT0_CH0_ISR()    //100us
{
	static char flag = 0;

	if(flag == 0)
	{
		LED1_ON;
		flag = 1;
	}
	else
	{
		LED1_OFF;
		flag = 0;

	}
	vol_sample(0, CellVol); //采样, 入参指定采样板编号
	vol_sample(1, CellVol); //采样, 入参指定采样板编号
	/*static int times = 0;
	static int count = 0;
	++times;
	if((count < 30))
	{
		times = 0;
		static int addr = 0;
		for(count=0; count<30; ++count)
		{
			SPI_25LC256_WriteMul(addr, 32, Write_25LC256_buffer);
			addr += 32;
			++count;
		}
	}*/
	/*if(StartTimer==1)
	{
		Count_PowerHold++;
		if(Count_PowerHold>=3000)
		{
			PowerHold_low;
			Count_PowerHold=0;
			StartTimer=0;
		}
	}*/
	/*if(count == 30)
		FFF = 1;*/
	PIT_0.TIMER[0].TFLG.B.TIF = 1;      //清计数完成标志位
}
//以下是LINFlex_0(UART) 的中断服务函数   232通信会用到
void UART0_ISR()
{
	char temp;
	temp = LINFlexD_0.BDRM.B.DATA4;		//读取数据
	LINFlexD_0.UARTSR.B.DRFRFE = 1;   	//清标志位
}
//以下是LINFlex_1(UART) 的中断服务函数   485通信会用到
void UART1_ISR()
{
	char temp;
	static char Index=0;
	temp = LINFlexD_1.BDRM.B.DATA4;		//读取数据
	DataRec_485[Index++]=temp;
	if(temp != 't')
	LINFlexD_1.UARTSR.B.DRFRFE = 1;   	//清标志位
	else
	{
		Index=0;
	}
}
//以下是SPI0 的接收中断服务函数
void SPI_REC_ISR()
{
	unsigned char RecDataMaster;
	RecDataMaster = SPI_0.POPR.R;            //读取主机接收到的数据
	SPI_0.SR.R = 0xFCFE0000;                 //清除标志位
}

int main(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

    SysClk_Init();
    InitPeriClkGen();

    gpio_init();
    LED1_ON;
    LED2_ON;
    LED3_OFF;

    SPI_Pin_Init();
    SPI_Init();					//LTC6804通信SPI初始化
    PIT0_CH0_Init(5000);    	//时钟为50MHz,此处计数时间为0.1ms   5000
    Start_Pit0_CH0;				//开启定时器
    PIT0_CH1_Init(500000);    	//时钟为50MHz,此处计数时间为10ms    500000
    Start_Pit0_CH1;				//开启定时器


    //这里必须加while(1)死循环
    while(1)
    {
    	delay_test0(100);
    }

    return 0;
}
void delay_test0(unsigned int t)
{
	int i,j;
	j=1000;     //2  0.8us
	for(i=0;i<t;i++)
	{
		while(j > 0)
			j--;
	}
}

