/*
 * TB_ADC.h
 *
 *  Created on: 2017��9��17��
 *      Author: WangHongBo
 */

#ifndef TB_ADC_H_
#define TB_ADC_H_

#include "project.h"

#define ADC_VREF       3300      //�ο���ѹ ��λ: ���� mV

void ADC1_CH3_PinInit();
void ADC1_CH2_PinInit();
uint32_t ADC1_Calibration();
void ADC1_Init();
void ADC1_StartConvert();
uint16_t ADC1_CH3_ReadData();
uint16_t ADC1_CH2_ReadData();
#endif /* TB_ADC_H_ */
