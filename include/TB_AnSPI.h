/*
 * TB_AnSPI.h
 *
 *  Created on: 2017Äê10ÔÂ14ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_ANSPI_H_
#define TB_ANSPI_H_

#include "project.h"

#define EEPROM_CS_high   SIUL2.GPDO[PC4].R  = 1
#define EEPROM_CS_low    SIUL2.GPDO[PC4].R  = 0

#define EEPROM_CLK_high  SIUL2.GPDO[PC5].R  = 1
#define EEPROM_CLK_low   SIUL2.GPDO[PC5].R  = 0

#define EEPROM_SO_high   SIUL2.GPDO[PC6].R  = 1
#define EEPROM_SO_low    SIUL2.GPDO[PC6].R  = 0

#define EEPROM_SI_state  SIUL2.GPDI[PC7].R

void EEPROM_Pin_Init();
void EEPROM_Write(short addr,uint8_t data);
uint8_t EEPROM_Read(short addr);
uint8_t SPI_ReadByte(short addr);
void EEPROM_Read_Mul(short addr,char num,char* des);
void EEPROM_Write_Mul(short addr,char num,char* src);
#endif /* TB_ANSPI_H_ */
