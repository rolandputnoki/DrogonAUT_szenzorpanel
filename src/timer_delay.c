/*
 * timer_delay.c
 *
 *  Created on: 2017. nov. 28.
 *      Author: Roland
 */

#include "timer_delay.h"

uint8_t delay_elapsed;
TIM_HandleTypeDef Tim7Handle;

void InitDelayTimer()
{
	// APB1: 42 MHz (TIMx: 84 MHz)
	__TIM7_CLK_ENABLE();

	// TIM7: 10 kHz (TIM7_FREQ)
	Tim7Handle.Instance = TIM7;
	Tim7Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim7Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim7Handle.Init.Prescaler = 0;
//	Tim7Handle.Init.Period = 12599;
	Tim7Handle.Init.Period = 83;
	Tim7Handle.State = HAL_TIM_STATE_RESET;
	Tim7Handle.Instance->CNT = 0;

	HAL_TIM_Base_Init(&Tim7Handle);

	HAL_NVIC_SetPriority(TIM7_IRQn, 3, 3);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

//	HAL_TIM_Base_Start(&Tim7Handle);
}

void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&Tim7Handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *handle)
{
	if (handle->Instance == TIM7)
		{
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
		HAL_TIM_Base_Stop_IT(&Tim7Handle);
		delay_elapsed = 1;
		}
}

void usec_delay(uint16_t usec_num){

	uint16_t counter = 0;
//	HAL_NVIC_EnableIRQ(TIM7_IRQn);
//	HAL_TIM_Base_Start_IT(&Tim7Handle);

	while(counter < usec_num){
		delay_elapsed = 0;
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
		HAL_TIM_Base_Start_IT(&Tim7Handle);
		while(!delay_elapsed);
		counter++;
	}

}
