/*
 * TB_DS1302.c
 *
 *  Created on: 2017年9月27日
 *      Author: WangHongBo
 */

#include "TB_DS1302.h"
//                       秒     分      时          日       月    星期     年
unsigned char TIME[7] = {0, 0,0x08, 28, 9, 4, 17};
unsigned char READ_RTC_ADDR[7]  = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
unsigned char WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
unsigned char Time_Read[7];

void delay_10us()
{
	unsigned char t=100;
	while(t--);
}
void delay_ms(unsigned char t)
{
  unsigned int i,j=10000;
  for(i=0;i<t;i++)
  {
    while(j>0)
    	j--;
  }
}
void DS1302_PinInit()
{
	SIUL2.MSCR[PB6].B.OBE  = 1;   		 //RT_SCLK引脚
	SIUL2.MSCR[PD1].B.OBE  = 1;  		 //RT_RST 引脚

	SIUL2.MSCR[PD0].B.OBE  = 1;  		 //RT_IO  引脚(数据引脚)
	SIUL2.MSCR[PD0].B.IBE  = 0;  		 //RT_IO  引脚(数据引脚)
}
void DS1302_Wtite_Byte(unsigned char addr,unsigned char data)
{
  unsigned char i;
  DS1302_RST_low;
  delay_10us();
  DS1302_SCK_low;
  delay_10us();
  DS1302_RST_high;
  delay_ms(3);
  SIUL2.MSCR[PD0].B.OBE  = 1;  		 //RT_IO  引脚(数据引脚)
  SIUL2.MSCR[PD0].B.IBE  = 0;  		 //RT_IO  引脚(数据引脚)
  for(i=0;i<8;i++)
  {
    if((addr&0x01) == 0x01)
    {
      DS1302_DATA_high;
    }
    else
    {
      DS1302_DATA_low;
    }
    delay_10us();
    DS1302_SCK_high;
    delay_10us();
    DS1302_SCK_low;
    delay_10us();
    addr = addr>>1;
  }
  for(i=0;i<8;i++)
  {
    if((data&0x01) == 0x01)
    {
      DS1302_DATA_high;
    }
    else
    {
      DS1302_DATA_low;
    }
    delay_10us();
    DS1302_SCK_high;
    delay_10us();
    DS1302_SCK_low;
    delay_10us();
    data = data>>1;
  }
  DS1302_RST_low;
  delay_10us();
}
unsigned char DS1302_READ_Byte(unsigned char addr)
{
  unsigned char i,temp,data;
  temp=0;data=0;
  DS1302_RST_low;
  delay_10us();
  DS1302_SCK_low;
  delay_10us();
  DS1302_RST_high;
 // delay_ms(3);     //此处加延时会出问题，时间会不准
  SIUL2.MSCR[PD0].B.OBE  = 1;  		 //RT_IO  引脚(数据引脚)
  SIUL2.MSCR[PD0].B.IBE  = 0;  		 //RT_IO  引脚(数据引脚)
  for(i=0;i<8;i++)
  {
    if((addr&0x01) == 0x01)
    {
      DS1302_DATA_high;
    }
    else
    {
      DS1302_DATA_low;
    }
    delay_10us();
    DS1302_SCK_high;
    delay_10us();
    DS1302_SCK_low;
    delay_10us();
    addr = addr>>1;
  }
  SIUL2.MSCR[PD0].B.OBE  = 0;  		 //RT_IO  引脚(数据引脚)
  SIUL2.MSCR[PD0].B.IBE  = 1;  		 //RT_IO  引脚(数据引脚)
  for(i=0;i<8;i++)
  {
    temp>>=1;
    data = DS1302_DATA_Read;
    if(data)
    {
     temp|= 0x80;
    }
    else
    {
      temp&=~0x80;
    }
    DS1302_SCK_high;
   // delay_10us();//新加
    DS1302_SCK_low;
   // delay_10us();//新加
  }
  SIUL2.MSCR[PD0].B.OBE  = 1;  		 //RT_IO  引脚(数据引脚)
  SIUL2.MSCR[PD0].B.IBE  = 0;  		 //RT_IO  引脚(数据引脚)
  DS1302_RST_low;
 // delay_10us();//新加
  return temp;
}
//引脚及时间数据初始化
void DS1302_Init()
{
  DS1302_PinInit();
  unsigned char i=0;
  DS1302_Wtite_Byte(0x8E,0x00);
  for(i=0;i<7;i++)
  {
    DS1302_Wtite_Byte(WRITE_RTC_ADDR[i],TIME[i]);
    //delay_10us();
  }
  DS1302_Wtite_Byte(0x8E,0x80);
}
void DS1302_Read()
{
  unsigned char i;
  for(i=0;i<7;i++)
  {
    Time_Read[i] = DS1302_READ_Byte(READ_RTC_ADDR[i]);
  }
}
