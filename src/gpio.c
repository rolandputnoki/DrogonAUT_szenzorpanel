/*
 * gpio.c
 *
 *  Created on: 2017. nov. 17.
 *      Author: Patrik
 */

#include "gpio.h"

void GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	    //GPIO Portok órajel engedélyezése
	   __HAL_RCC_GPIOC_CLK_ENABLE();
	   __HAL_RCC_GPIOH_CLK_ENABLE();
	   __HAL_RCC_GPIOA_CLK_ENABLE();
	   __HAL_RCC_GPIOB_CLK_ENABLE();

	   //Minden MUX engedélyezés
	   GPIO_InitStruct.Pin = GPIO_PIN_12;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	   //MUX1 címzés
	   GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	   //MUX2 címzés
	   GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOC,&GPIO_InitStruct);

	   //MUX3 címzés
	   GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	   //MUX4 címzés
	   GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOC,&GPIO_InitStruct);

	   //ADC1 GPIO Configuration
	   //PC4     ------> ADC1_IN14
	   //PC5     ------> ADC1_IN15
	   GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
	   GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   //ADC2 GPIO Configuration
	   //PC0    ------> ADC2_IN10
	   GPIO_InitStruct.Pin = GPIO_PIN_0;
	   GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   //ADC3 GPIO Configuration
	   //PC3     ------> ADC3_IN13
	   GPIO_InitStruct.Pin = GPIO_PIN_3;
	   GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	   //SPI3 GPIO Configuration
	   //PC1     ------> SPI3_MOSI
	   //PC10    ------> SPI3_SCK
	   //PB7 	------> SPI3 OE LEDS
	   //PB8 	------> SPI3 LE LEDS
	   //PB9     ------> SPI3 OE TCRTS
	   //PB10    ------> SPI3 LE TCRTS
 	   GPIO_InitStruct.Pin = GPIO_PIN_1;
	   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   GPIO_InitStruct.Alternate = GPIO_AF5_SPI3;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   GPIO_InitStruct.Pin = GPIO_PIN_10;
	   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   //LED-ek LE
	   GPIO_InitStruct.Pin = GPIO_PIN_8;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	   HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	  	//LED-ek OE
	    GPIO_InitStruct.Pin = GPIO_PIN_7;
	  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	    //TCRT-k OE
	    GPIO_InitStruct.Pin = GPIO_PIN_9;
	  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);

	  	//TCRTek LE
	    GPIO_InitStruct.Pin = GPIO_PIN_10;
	  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}
