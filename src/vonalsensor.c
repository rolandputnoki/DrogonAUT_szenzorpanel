/*
 * vonalsensor.c
 *
 *  Created on: 2017. nov. 18.
 *      Author: Patrik
 */

#include "vonalsensor.h"
#include "adc.h"
#include "spi.h"
#include "szervo_pwm.h"
#define ADCKUSZOB 2000				//ADC érték mikor érzékelje vonalnak  0-4096

//ADC DMA-hoz
uint16_t pData1[2];		//channel 1
uint16_t pData2[1];		//channel 2
uint16_t pData3[1];		//channel 3


uint8_t pData_TCRT[4] =  {0x01,0x01,0x01,0x01};	//adattároló, melyik TCRT világítson, ezt küldjük ki SPI-al, kezdeti érték
uint8_t pData_LEDS[4] =  {0x00,0x00,0x00,0x00};	//adattároló, melyik LED világítson, ezt küldjük ki SPI-al, kezdeti érték
uint8_t pData_NULL[4] =  {0x00,0x00,0x00,0x00};	//adattároló, ha törölni kell a shiftergiszterek tartalmát, 0-t kell beleshiftelni

void set_Leds_Tcrts()
{
	SPI3_Write_TCRTS(pData_TCRT,4); //TCRT-k kezdeti állapotba
	SPI3_Write_LEDS(pData_LEDS,4);	//LED-ek kezdeti állapotba
}

void vonal(uint16_t *adcAdatok)
{

	for(int i = 0; i < 8; i++)				//egyszerre 4 szenzort olvasunk, 8-szor kell olvasni az összes értékhez
	{

		//SPI3_Write_TCRTS(pData_TCRT,4);					//aktuális TCRT állapot kiírása
		/*
		if(pData_TCRT[2] == 0x80 )						//túlcsorgás elsõ esete
		{
			pData_TCRT[0] = 0x01;
			pData_TCRT[1] = 0x01;
			pData_TCRT[2] = 0x01;
			pData_TCRT[3] = 0x01;
		}
		else if(pData_TCRT[2] == 0x40)					//túlcsorgás második esete
		{
			pData_TCRT[0] = 0x02;
			pData_TCRT[1] = 0x02;
			pData_TCRT[2] = 0x02;
			pData_TCRT[3] = 0x02;
		}
		else											//kettesével lépkedünk a TCRT-ken
		{
			pData_TCRT[0] *= 4;
			pData_TCRT[1] *= 4;
			pData_TCRT[2] *= 4;
			pData_TCRT[3] *= 4;
		}
		SPI3_Write_TCRTS(pData_TCRT,4);					//aktuális TCRT állapot kiírása
*/


		if(pData_TCRT[0] == 0x80 )						//túlcsorgás elsõ esete
		{
			pData_TCRT[0] = 0x01;
			pData_TCRT[1] = 0x01;
			pData_TCRT[2] = 0x01;
			pData_TCRT[3] = 0x01;
		}
		else											//kettesével lépkedünk a TCRT-ken
		{
			pData_TCRT[0] *= 2;
			pData_TCRT[1] *= 2;
			pData_TCRT[2] *= 2;
			pData_TCRT[3] *= 2;
		}

/*
		pData_TCRT[0] = 0x01;
		pData_TCRT[1] = 0x01;
		pData_TCRT[2] = 0x01;
		pData_TCRT[3] = 0x01;
*/

		SPI3_Write_TCRTS(pData_TCRT,4);					//aktuális TCRT állapot kiírása
		SPI3_Write_TCRTS(pData_TCRT,4);

		usec_delay(55);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);		//MUX-ok tiltása


		//MUX címzések számítása
		if(pData_TCRT[2] == 0x01)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);


		}
		else if(pData_TCRT[2] == 0x02)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

		}
		else if(pData_TCRT[2] == 0x04)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);

		}
		else if(pData_TCRT[2] == 0x08)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

		}
		else if(pData_TCRT[2] == 0x10)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

		}
		else if(pData_TCRT[2] == 0x20)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, RESET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

		}
		else if(pData_TCRT[2] == 0x40)
		{
			//MUX1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);

			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);

		}
		else if(pData_TCRT[2] == 0x80)
		{
			//MUX1

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, SET);


			//MUX2
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);

			//MUX3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);

			//MUX4
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);

		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
		}



		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);			//MUX-ok engedélyezése

		usec_delay(1);
//		HAL_Delay(1);

		HAL_ADC_Start_DMA(&hadc1, (uint32_t *) pData1, 2);
		HAL_ADC_Start_DMA(&hadc2, (uint32_t *) pData2, 1);
		HAL_ADC_Start_DMA(&hadc3, (uint32_t *) pData3, 1);


		while(!ADC_CSR_EOC1);
		usec_delay(7);
//		HAL_Delay(1);

		SPI3_Write_TCRTS(pData_NULL,4);			//TCRT-k kikapcsolása
		SPI3_Write_TCRTS(pData_NULL,4);
//		usec_delay(100);


		//melyik LED világítson kiszámolása, fordított bekötés

		if(pData_TCRT[0] == 0x01)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x80;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x80;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x80;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x80;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[31] = pData1[0];
			adcAdatok[23] = pData1[1];
			adcAdatok[15] = pData2[0];
			adcAdatok[7] = pData3[0];


		}
		else if(pData_TCRT[0] == 0x02)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x40;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x40;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x40;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x40;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[30] = pData1[0];
			adcAdatok[22] = pData1[1];
			adcAdatok[14] = pData2[0];
			adcAdatok[6] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x04)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x20;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x20;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x20;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x20;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[29] = pData1[0];
			adcAdatok[21] = pData1[1];
			adcAdatok[13] = pData2[0];
			adcAdatok[5] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x08)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x10;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x10;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x10;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x10;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[28] = pData1[0];
			adcAdatok[20] = pData1[1];
			adcAdatok[12] = pData2[0];
			adcAdatok[4] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x10)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x08;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x08;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x08;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x08;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[27] = pData1[0];
			adcAdatok[19] = pData1[1];
			adcAdatok[11] = pData2[0];
			adcAdatok[3] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x20)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x04;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x04;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x04;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x04;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[26] = pData1[0];
			adcAdatok[18] = pData1[1];
			adcAdatok[10] = pData2[0];
			adcAdatok[2] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x40)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x02;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x02;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x02;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x02;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}

			adcAdatok[25] = pData1[0];
			adcAdatok[17] = pData1[1];
			adcAdatok[9] = pData2[0];
			adcAdatok[1] = pData3[0];
		}
		else if(pData_TCRT[2] == 0x80)
		{
			if(pData1[0] > ADCKUSZOB)
			{
				pData_LEDS[1] = 0x01;
			}
			else
			{
				pData_LEDS[1] = 0x00;
			}
			if(pData1[1] > ADCKUSZOB)
			{
				pData_LEDS[0] = 0x01;
			}
			else
			{
				pData_LEDS[0] = 0x00;
			}
			if(pData2[0] > ADCKUSZOB)
			{
				pData_LEDS[3] = 0x01;
			}
			else
			{
				pData_LEDS[3] = 0x00;
			}
			if(pData3[0] > ADCKUSZOB)
			{
				pData_LEDS[2] = 0x01;
			}
			else
			{
				pData_LEDS[2] = 0x00;
			}
			adcAdatok[24] = pData1[0];
			adcAdatok[16] = pData1[1];
			adcAdatok[8] = pData2[0];
			adcAdatok[0] = pData3[0];
		}


		SPI3_Write_LEDS(pData_LEDS,4);					//LED-ek írása

	}
	return;
}





