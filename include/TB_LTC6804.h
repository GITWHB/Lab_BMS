#include "project.h"

#ifndef TB_LTC6804_H_
#define TB_LTC6804_H_

#define WRCFG1 	 	(1)
#define WRCFG2 		(2)
#define WRCFG3 		(3)
#define ADCV1 		(4)
#define ADCV2 		(5)
#define ADCV3		(6)
#define SPIWAIT		(7)
#define RDCVA1 		(8)
#define RDCVB1 		(9)
#define RDCVC1 		(10)
#define RDCVD1 	 	(11)
#define RDCVA2		(12)
#define RDCVB2		(13)
#define RDCVC2 		(14)
#define RDCVD2 		(15)
#define RDCVA3 		(16)
#define RDCVB3  	(17)
#define RDCVC3       (18)
#define RDCVD3 		(19)
#define ADCVAX1   	(20)
#define ADCVAX2 	(21)

#define SPIWAIT2 	(22)

#define RDAUXA1		(23)
#define RDAUXB1 	(24)
#define RDAUXA2	 	(25)
#define RDAUXB2 	(26)

#define SPIHOLD 	(27)
#define ADOWU1  	(28)
#define ADOWU2		(29)
#define ADOWU3		(30)
#define ADOWD1 		(31)
#define ADOWD2 		(32)
#define ADOWD3		(33)
#define SPIRESET        (34)

unsigned short pec15(char *data , short len);
void SPI_Pin_Init();
void SPI_Init2();
unsigned char SPI_DataRec();
uint8_t SPI_DataSend(uint8_t Data_Tx);
void SPI_Send_Continuous(uint8_t *Data_Tx,uint8_t length);
void DataOrganization();
void SPISendReceive();
void SPI_Init();
unsigned char SPI_DataRec0();
void SPI_Send_Continuous0(uint8_t *Data_Tx,uint8_t length);
void vol_sample();
void delay_test(unsigned char t);
uint8_t SPI_mid_DataSend(uint8_t Data_Tx);


#endif /* TB_LTC6804_H_ */
