/*
 * bsp_spi.h
 *
 *  Created on: 2017. nov. 5.
 *      Author: Dominik
 */

#ifndef BSP_SPI_H_
#define BSP_SPI_H_

//SPI kezelõk
extern SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;

HAL_StatusTypeDef SPI1_Init();
void SPI3_Init();
void SPI_Init();

void SPI3_EnableChip_LEDS(int enable);
void SPI3_EnableChip_TCRTS(int enable);
void SPI3_EnableOutput_LEDS(int enable);
void SPI3_EnableOutput_TCRTS(int enable);


HAL_StatusTypeDef SPI3_Send(uint8_t* pData, uint16_t dataSize);

HAL_StatusTypeDef SPI_Receive(uint8_t* pData, uint16_t dataSize);
HAL_StatusTypeDef SPI_SendReceive(uint8_t* pDataIn, uint8_t *pDataOut, uint16_t dataSize);

void SPI3_Write_LEDS(uint8_t* pData, uint16_t dataSize);
void SPI3_Write_TCRTS(uint8_t* pData, uint16_t dataSize);


#endif /* BSP_SPI_H_ */
