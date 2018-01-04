/*
 * ADC.c
 *
 *  Created on: 2017. okt. 30.
 *      Author: Patrik
 */

#include "adc.h"

//mindh�rom ADC inicializ�l�snak h�v�sa egy f�ggv�nnyel
void ADC_Init()
{
	ADC1_Init();
	ADC2_Init();
	ADC3_Init();
}

//ADC1 iniciliz�l�sa
//multichannel m�d --> k�t l�bon l�v� konverzi� egym�s ut�n
//nem folytonos m�d, csak h�v�skor konvert�l
//DMA m�d haszn�lata
void ADC1_Init()
{
  ADC_ChannelConfTypeDef sConfig;

  hadc1.Instance = ADC1;												//azonos�t�, melyik ADC
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;					//ADC �rajele
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;							//felbont�s
  hadc1.Init.ScanConvMode = ENABLE;										//multichannel kapcsol�sa
  hadc1.Init.ContinuousConvMode = DISABLE;								//folytonos m�d kapcsol�s
  hadc1.Init.DiscontinuousConvMode = ENABLE;							//nem folytonos m�d kapcsol�s
  hadc1.Init.NbrOfDiscConversion = 2;									//nem folytonos konverzi�k sz�ma
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;		//k�ls� trigger esem�ny �l �ll�t�s
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;						//mire induljon a konverzi�
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;							//adat hozz�rendel�s a regiszterben
  hadc1.Init.NbrOfConversion = 2;										//konverzi�k sz�ma
  hadc1.Init.DMAContinuousRequests = ENABLE;							//DMA enged�lyez�s
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;						//konvert�l�s v�ge flag mire aktiv�l�djon
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
  }

  sConfig.Channel = ADC_CHANNEL_14;							//channel v�laszt�s, melyik l�bat konvert�lja
  sConfig.Rank = 1;											//ha multichannel a Rankok sorrendj�ben v�gzi a konverzi�kat
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;			//�rajelb�l �s adatlapi konstansb�l sz�molva ~4-5us sz�ks�ges a stabil m�k�d�shez
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
}

//ADC2 iniciliz�l�sa
//single m�d --> egy l�bon l�v� konverzi�
//nem folytonos m�d, csak h�v�skor konvert�l
//DMA m�d haszn�lata
void ADC2_Init()
{
  ADC_ChannelConfTypeDef sConfig;

  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = ENABLE;
  hadc2.Init.NbrOfDiscConversion = 1;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;			//�rajelb�l �s adatlapi konstansb�l sz�molva
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

}

//ADC3 iniciliz�l�sa
//single m�d --> egy l�bon l�v� konverzi�
//nem folytonos m�d, csak h�v�skor konvert�l
//DMA m�d haszn�lata
void ADC3_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = ENABLE;
  hadc3.Init.NbrOfDiscConversion = 1;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
  }

  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)		//�rajelb�l �s adatlapi konstansb�l sz�molva
  {
   // _Error_Handler(__FILE__, __LINE__);
  }
}

