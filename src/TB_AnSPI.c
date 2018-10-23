/*
 * TB_AnSPI.c
 *
 *  Created on: 2017年10月14日
 *      Author: WangHongBo
 */

#include "TB_AnSPI.h"

void delay_100ns(unsigned char N)
{
	unsigned char t=2;
	while(N--)
	{
		while(t--);
	}
}
void EEPROM_Pin_Init()
{
	//PC4 CS0
	SIUL2.MSCR[PC4].B.OBE = 1;
	SIUL2.GPDO[PC4].R     = 1;
	//PC5 SCK
	SIUL2.MSCR[PC5].B.OBE = 1;
	SIUL2.GPDO[PC5].R     = 1;
    //PC6 SOUT
	SIUL2.MSCR[PC6].B.OBE = 1;
	//PC7 SIN
	SIUL2.MSCR[PC7].B.IBE = 1;
	SIUL2.MSCR[PC7].B.PUE = 1;    //上拉/下拉使能
	SIUL2.MSCR[PC7].B.PUS = 1;    //配置为上拉
	//PD2 HOLD
    SIUL2.MSCR[PD2].B.OBE = 1;
	SIUL2.GPDO[PD2].R     = 1;
}
void SPI_WriteByte(uint8_t data)
{
	int i = 0,temp=0;
	EEPROM_CS_low;
	EEPROM_CLK_low;
	delay_100ns(2);
	for(i=0; i<8; i++)
	{
		temp = (data&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		data =(data<<1);
	}
}
uint8_t SPI_ReadByte(short addr)
{
	int i,temp=0,data=0;
	SPI_WriteByte(0x03);
	SPI_WriteByte((uint8_t)((addr&0xFF00)>>8));
	SPI_WriteByte((uint8_t)(addr&0x00FF));
	for(i=0;i<8;i++)
	{
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		temp = EEPROM_SI_state;
		if(temp)
		{
			data|=0x01;
		}
		else
		{
			data&=~0x01;
		}
		delay_100ns(2);
		if(i<7)
		data=data<<1;
	}
	EEPROM_CS_high;
	delay_100ns(2);
	EEPROM_CLK_high;
	return data;
}
void EEPROM_Write(short addr,uint8_t data)
{
	uint8_t i=0,temp=0x06,temp0;
	short temp_add;
	EEPROM_CS_low;
	EEPROM_CLK_low;
	delay_100ns(2);
	temp0 = 0x06;
	for(i=0;i<8;i++)
	{
		temp = (temp0&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		temp0 =(temp0<<1);
	}
	delay_100ns(5);
	EEPROM_CS_high;
 	delay_100ns(5);
	EEPROM_CS_low;

	temp0 = 0x02;
	for(i=0;i<8;i++)
	{
		temp = (temp0&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		temp0 =(temp0 << 1);
	}
	for(i=0;i<16;i++)
	{
		temp_add = (addr&0x8000);
		if(temp_add == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		addr = (addr<<1);
	}
	for(i=0;i<8;i++)
	{
		temp = (data&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		data =(data<<1);
	}
	EEPROM_CS_high;
	EEPROM_CLK_high;
}
uint8_t EEPROM_Read(short addr)
{
	uint8_t i=0,temp,data=0,temp0;
	short temp_addr;
	EEPROM_CS_low;
	delay_100ns(2);
	EEPROM_CLK_low;
	delay_100ns(2);
	temp0 = 0x03;
	for(i=0;i<8;i++)
	{
		temp = (temp0&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		temp0 =(temp0<<1);
	}

	for(i=0;i<16;i++)
	{
		temp_addr = (addr&0x8000);
		if(temp_addr == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);

		addr = (addr<<1);
	}

	for(i=0;i<8;i++)
	{
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		temp = EEPROM_SI_state;
		if(temp)
		{
			data|=0x01;
		}
		else
		{
			data&=~0x01;
		}
		delay_100ns(2);
		if(i<7)
		data=data<<1;
	}
	EEPROM_CS_high;
	delay_100ns(2);
	EEPROM_CLK_high;
	return data;
}
void EEPROM_Read_Mul(short addr,char num,char* des)
{
	int i,j,temp=0,data=0;
	SPI_WriteByte(0x03);
	SPI_WriteByte((uint8_t)((addr&0xFF00)>>8));
	SPI_WriteByte((uint8_t)(addr&0x00FF));
	for(j=0;j<(num);j++)
	{
		for(i=0;i<8;i++)
		{
			EEPROM_CLK_high;
			delay_100ns(2);
			EEPROM_CLK_low;
			temp = EEPROM_SI_state;
			if(temp)
			{
				data|=0x01;
			}
			else
			{
				data&=~0x01;
			}
			delay_100ns(2);
			if(i<7)
			data=data<<1;
		}
		*des = data;
		des++;
	}
	EEPROM_CS_high;
	delay_100ns(2);
	EEPROM_CLK_high;
}
void EEPROM_Write_Mul(short addr,char num,char* src)
{
	uint8_t i=0,j,temp=0x06,temp0,data;
	short temp_add;
	EEPROM_CS_low;
	EEPROM_CLK_low;
	delay_100ns(2);
	temp0 = 0x06;
	for(i=0;i<8;i++)
	{
		temp = (temp0&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		temp0 =(temp0<<1);
	}
	delay_100ns(5);
	EEPROM_CS_high;
 	delay_100ns(5);
	EEPROM_CS_low;

	temp0 = 0x02;
	for(i=0;i<8;i++)
	{
		temp = (temp0&0x80);
		if(temp == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		temp0 =(temp0 << 1);
	}
	for(i=0;i<16;i++)
	{
		temp_add = (addr&0x8000);
		if(temp_add == 0)
		{
			EEPROM_SO_low;
		}
		else
		{
			EEPROM_SO_high;
		}
		delay_100ns(2);
		EEPROM_CLK_high;
		delay_100ns(2);
		EEPROM_CLK_low;
		delay_100ns(2);
		addr = (addr<<1);
	}
	for(j=0;j<num;j++)
	{
		data = src[j];
		for(i=0;i<8;i++)
		{
			temp = (data&0x80);
			if(temp == 0)
			{
				EEPROM_SO_low;
			}
			else
			{
				EEPROM_SO_high;
			}
			delay_100ns(2);
			EEPROM_CLK_high;
			delay_100ns(2);
			EEPROM_CLK_low;
			delay_100ns(2);
			data =(data<<1);
		}
	}
	EEPROM_CS_high;
	EEPROM_CLK_high;
}
