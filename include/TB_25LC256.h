/*
 * TB_25LC256.h
 *
 *  Created on: 2017Äê10ÔÂ13ÈÕ
 *      Author: WangHongBo
 */

#ifndef TB_25LC256_H_
#define TB_25LC256_H_

#include "project.h"

void SPI_25LC256_Pin_Init();
void SPI_25LC256_Init();
unsigned char SPI_25LC256_DataRec();
void SPI_25LC256_DataSend(uint8_t Data_Tx);
void SPI_25LC256_Send_Continuous(uint8_t *Data_Tx, uint8_t length);
void SPI_25LC256_WriteMul(short addr, unsigned int num, char* src);
void SPI_25LC256_ReadMul(short addr,int num,char* des);
unsigned int SPI_25LC256_ReadSingle(short addr);


#endif /* TB_25LC256_H_ */

