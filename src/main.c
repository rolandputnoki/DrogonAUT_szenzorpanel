/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "sysclk.h"
#include "adc.h"
#include "spi.h"
#include "dma.h"
#include "gpio.h"
#include "vonalsensor.h"
#include "szervo_pwm.h"

#include "global_variables.h"

#define KP 5000
#define KD 5000

uint16_t adcAdatok1[32] = {0};	//szenzorétékek
uint16_t adcAdatok2[32] = {0};	//szenzorétékek
uint8_t is_buffer1_okay = 1;


float D = 0.0f;
float error = 0.0f;
float prev_error = 0.0f;
float setValue = 0.0f;
float output = 0.0f;
float delta_t = 0.01;


int16_t pd_value = 0;
uint16_t szervo_value = 0;
uint16_t szervo_value_prev = 0;
uint32_t szumma_adc_values = 0;
int32_t szumma_sulyozott = 0;
float p = 0.0f;
TIM_HandleTypeDef Tim2Handle;

extern		uint16_t tomb[32];

int main(void)
{
	HAL_Init(); 			//init HAL library
	SystemClock_Config(); 	//set system clock
	GPIO_Init();			//init GPIOs
	DMA_Init();				//init DMAs
	ADC_Init();				//init ADCs
	SPI_Init();				//init SPIs

	InitDelayTimer();



	/******  Logikai analizátoros idõméréshez segéd láb ************/
/*
	GPIO_InitTypeDef  GPIO_InitStructure;
	__GPIOA_CLK_ENABLE();
	// GPIO alternate function lÃ¡bak
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pin =  GPIO_PIN_5;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
*/


/*	Gyári szervóhoz
	Init_GY_Szervo_PWM();
*/

	/* Digitális szervóhoz */
//	Init_AF_szervo();
//	Init_Digit_Szervo_PWM();



	int8_t sorszam[32] = {-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};		//szenzorsorszámok a súlyozáshoz



	SPI3_EnableOutput_TCRTS(0);	//TCRT meghajtók kimenetének tiltása
	SPI3_EnableOutput_LEDS(0);	//LED meghajtók kimenetének tiltása

	set_Leds_Tcrts();			//kezdeti állapot állítása led-eken, tcrt-ken


	float ez = 20.16f;
	char * kuld = "abac";
	unsigned char * chptr;
	unsigned char kuldes[4];
	chptr = (unsigned char *) &ez;


	for(uint8_t l = 0; l<32; l++){
		tomb[l] = l;
	}

	while(1)
		{



			if(is_buffer1_okay){
				HAL_SPI_Transmit_IT(&hspi1, adcAdatok1, 64);
			} else {
				HAL_SPI_Transmit_IT(&hspi1, adcAdatok2, 64);
			}


			if(is_buffer1_okay){
				vonal(adcAdatok2);
				is_buffer1_okay = 0;
			} else {
				vonal(adcAdatok1);
				is_buffer1_okay = 1;

			}


//			adcAdatok[31] -= 70;
//			adcAdatok[30] -= 10;
//			adcAdatok[29] -= 20;
//			adcAdatok[0] += 30;


			/*
			for(int i = 0; i < 32; i++)				//arányos tényezõ számí  tása
			{
				szumma_adc_values += adcAdatok[i];
				adcAdatok[i] = adcAdatok[i] * sorszam[i];			//súlyozás
				szumma_sulyozott += adcAdatok[i];
			}
			p = (float)szumma_sulyozott/szumma_adc_values;
			uint8_t valami = 0;
	*/





		}
}


/************ Patrik féle szabályzó ***********/
/*
error = ((float)szumma_sulyozott/szumma_adc_values - 0.50)*hiba_szab_suly;
output = (float)(KP*error + KD*(error - prev_error)/delta_t);
prev_error = error;


/********* P_szabályzó  *************/
/*
szervo_value = DIGIT_SZ_KOZEP + hiba_szab_suly*p;
if(szervo_value > DIGIT_SZ_MAX_CMP){
	szervo_value = DIGIT_SZ_MAX_CMP;
} else if( szervo_value < DIGIT_SZ_MIN_CMP){
	szervo_value = DIGIT_SZ_MIN_CMP;
}
*/
