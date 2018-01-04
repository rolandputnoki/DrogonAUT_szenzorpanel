/*
 * ADC.c
 *
 *  Created on: 2017. okt. 30.
 *      Author: Patrik
 */

#include "adc.h"

//mindhárom ADC inicializálásnak hívása egy függvénnyel
void ADC_Init()
{
	ADC1_Init();
	ADC2_Init();
	ADC3_Init();
}

//ADC1 inicilizálása
//multichannel mód --> két lábon lévõ konverzió egymás után
//nem folytonos mód, csak híváskor konvertál
//DMA mód használata
void ADC1_Init()
{
  ADC_ChannelConfTypeDef sConfig;

  hadc1.Instance = ADC1;												//azonosító, melyik ADC
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;					//ADC órajele
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;							//felbontás
  hadc1.Init.ScanConvMode = ENABLE;										//multichannel kapcsolása
  hadc1.Init.ContinuousConvMode = DISABLE;								//folytonos mód kapcsolás
  hadc1.Init.DiscontinuousConvMode = ENABLE;							//nem folytonos mód kapcsolás
  hadc1.Init.NbrOfDiscConversion = 2;									//nem folytonos konverziók száma
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;		//külsõ trigger esemény él állítás
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;						//mire induljon a konverzió
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;							//adat hozzárendelés a regiszterben
  hadc1.Init.NbrOfConversion = 2;										//konverziók száma
  hadc1.Init.DMAContinuousRequests = ENABLE;							//DMA engedélyezés
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;						//konvertálás vége flag mire aktiválódjon
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
  }

  sConfig.Channel = ADC_CHANNEL_14;							//channel választás, melyik lábat konvertálja
  sConfig.Rank = 1;											//ha multichannel a Rankok sorrendjében végzi a konverziókat
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;			//órajelbõl és adatlapi konstansból számolva ~4-5us szükséges a stabil mûködéshez
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

//ADC2 inicilizálása
//single mód --> egy lábon lévõ konverzió
//nem folytonos mód, csak híváskor konvertál
//DMA mód használata
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
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;			//órajelbõl és adatlapi konstansból számolva
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

}

//ADC3 inicilizálása
//single mód --> egy lábon lévõ konverzió
//nem folytonos mód, csak híváskor konvertál
//DMA mód használata
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
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)		//órajelbõl és adatlapi konstansból számolva
  {
   // _Error_Handler(__FILE__, __LINE__);
  }
}

