/*
 * ADC.h
 *
 *  Created on: 2017. okt. 30.
 *      Author: Patrik
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"

//ADC kezelõk
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

//ADC DMA kezelõk
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
DMA_HandleTypeDef hdma_adc3;

void ADC_Init();

void ADC1_Init(void);
void ADC2_Init(void);
void ADC3_Init(void);

#endif /* ADC_H_ */
