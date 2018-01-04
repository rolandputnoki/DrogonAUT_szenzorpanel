/*
 * bsp_spi.c
 *
 *  Created on: 2017. nov. 5.
 *      Author: Dominik
 */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "spi.h"

#include "global_variables.h"

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi;

	uint16_t tomb[32];

const uint32_t spi_timeout = 5000;


//LED meghajtó IC engedélyezése vagy tiltása,  1->engedélyez 0->tilt
void SPI3_EnableChip_LEDS(int enable)
{
	if(enable)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, RESET);
	}
}

//TCRT meghajtó IC engedélyezése vagy tiltása, 1->engedélyez 0->tilt
void SPI3_EnableChip_TCRTS(int enable)
{
	if(enable)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
	}
}

//LED meghajtó IC kimenetének engedélyezése vagy tiltása, 1->engedélyez 0->tilt
void SPI3_EnableOutput_LEDS(int enable)
{
	if(enable)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);
	}
}

//TCRT meghajtó IC kimenetének engedélyezése vagy tiltása, 1->engedélyez 0->tilt
void SPI3_EnableOutput_TCRTS(int enable)
{
	if(enable)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, SET);
	}
}

// SPI adatküldés
HAL_StatusTypeDef SPI3_Send(uint8_t* pData, uint16_t dataSize)
{
	HAL_SPI_Transmit(&hspi3, pData, dataSize, spi_timeout);

	return HAL_OK;
}

// SPI adat fogadás
HAL_StatusTypeDef SPI_Receive(uint8_t* pData, uint16_t dataSize)
{
	HAL_SPI_Receive(&hspi, pData, dataSize, spi_timeout);

	return HAL_OK;
}

//Írás a LED-ekre SPI3-al, kiirandó adat, adatméret byte-ban
void SPI3_Write_LEDS(uint8_t* pData, uint16_t dataSize)
{
	SPI3_EnableOutput_LEDS(0);			//OE tiltás
	SPI3_EnableChip_LEDS(1);			//LE engedélyezés
	SPI3_Send(pData, dataSize);			//adatok küldése
	SPI3_EnableChip_LEDS(0);			//LE tiltás
	SPI3_EnableOutput_LEDS(1);			//OE engedélyezés
}

//Írás a TCRT-kre SPI3-al, kiirandó adat, adatméret byte-ban
void SPI3_Write_TCRTS(uint8_t* pData, uint16_t dataSize)
{
	SPI3_EnableOutput_TCRTS(0);			//OE tiltás
	SPI3_EnableChip_TCRTS(1);			//LE engedélyezés
	SPI3_Send(pData, dataSize);			//adatok küldése
//	HAL_Delay(1);
	SPI3_EnableChip_TCRTS(0);			//LE tiltás
	SPI3_EnableOutput_TCRTS(1);			//OE engedélyezés
}

// SPI küldés és fogadás egyszerre.
HAL_StatusTypeDef SPI_SendReceive(uint8_t* pDataIn, uint8_t *pDataOut, uint16_t dataSize)
{
	HAL_SPI_TransmitReceive(&hspi, pDataOut, pDataIn, dataSize, spi_timeout);

	return HAL_OK;
}

//SPI1 inicializálás
HAL_StatusTypeDef SPI1_Init()
{
  hspi1.Instance = SPI1;											//SPI azonosító
  hspi1.Init.Mode = SPI_MODE_SLAVE;								//Master mód
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;						//Adatirány
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;							//Adatméret (shifregiszer)
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;						//SPI órajel (SCLK) alapállapota (ha inaktív)
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;							//elsõ órajeltõl adat
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;									//Slave select szoftveres
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;			//SPI órajel elõállítása belsõ órajelbõl osztással
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;							//MSB-t küldjük elõször
  hspi1.Init.TIMode = SPI_TIMODE_DISABLED;							//TI mód tiltás
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;			//CRC számolás tiltása
//  hspi1.Init.CRCPolynomial = 10;

	HAL_NVIC_SetPriority(SPI1_IRQn, 0,0);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);



  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
  return HAL_SPI_Init(&hspi1);
}

/* SPI3 init function */
void SPI3_Init()
{
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
   // _Error_Handler(__FILE__, __LINE__);
  }


}

//SPI-ok inicializálása egy függvénybõl
void SPI_Init()
{
	SPI1_Init();
	SPI3_Init();
}


void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&hspi1);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *handle){
	/*
	if(handle->Instance == SPI1){
		if(is_buffer1_okay){
			HAL_SPI_Transmit_IT(&hspi1, adcAdatok1, 64);
		} else{
			HAL_SPI_Transmit_IT(&hspi1, adcAdatok2, 64);
		}
	}
	*/
}


void HAL_SPI_TxCpltCallback (SPI_HandleTypeDef * hspi){

	if(hspi->Instance == SPI1){
	}
}
