/*
 * szervo_pwm.c
 *
 *  Created on: 2017. nov. 18.
 *      Author: Roland
 */

/*
 * gyari_szervo_pwm.c
 *
 *  Created on: 2017. okt. 29.
 *      Author: Roland
 */
#include <szervo_pwm.h>

TIM_HandleTypeDef Tim2Handle, Tim7Handle, Tim4Handle;
uint32_t loop_counter;
uint8_t is_delayed = 1;


// Alternate function GPIO lábak inicializálása
void Init_AF_szervo()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	__GPIOA_CLK_ENABLE();
	// GPIO alternate function lábak
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pin =  GPIO_PIN_5;
	GPIO_InitStructure.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}


//
void Init_GY_Szervo_PWM()
{
	__TIM2_CLK_ENABLE();
	Tim2Handle.Instance = TIM2;
	//84MHz
	// Timer2
	Tim2Handle.Instance = TIM2;
	Tim2Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim2Handle.Init.Prescaler = 21;
	Tim2Handle.Init.Period = 62426;
	Tim2Handle.State = HAL_TIM_STATE_RESET;

	HAL_TIM_Base_Init(&Tim2Handle);
	HAL_TIM_PWM_Init(&Tim2Handle);

	TIM_OC_InitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	TIM_OCInitStructure.Pulse = 0;
	TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
	TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;
	TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

	HAL_TIM_PWM_ConfigChannel(&Tim2Handle, &TIM_OCInitStructure, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&Tim2Handle, TIM_CHANNEL_1);

	Tim2Handle.Instance->CCR1 = 5902;
//	Tim2Handle.Instance->CCR1 = 63000;
}

void Init_Digit_Szervo_PWM()
{

	//TIM4 az APB1 buszra csatlakozik, így az órajele 84MHz
	__TIM2_CLK_ENABLE();
	Tim2Handle.Instance = TIM2;
	// Timer4 konfigurációja PWM üzemmódban
	Tim2Handle.Instance = TIM2;
	Tim2Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim2Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim2Handle.Init.Prescaler = 3;
	Tim2Handle.Init.Period = 63062;
	Tim2Handle.State = HAL_TIM_STATE_RESET;

	HAL_TIM_Base_Init(&Tim2Handle);
	HAL_TIM_PWM_Init(&Tim2Handle);

	TIM_OC_InitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	TIM_OCInitStructure.Pulse = 0;
	TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
	TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;
	TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

	HAL_TIM_PWM_ConfigChannel(&Tim2Handle, &TIM_OCInitStructure, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&Tim2Handle, TIM_CHANNEL_1);

	Tim2Handle.Instance->CCR1 = DIGIT_SZ_KOZEP;
}

void Init_sajat_Szervo_PWM()
{
	//TIM4 az APB1 buszra csatlakozik, így az órajele 84MHz
		__TIM4_CLK_ENABLE();
		Tim4Handle.Instance = TIM4;
		// Timer4 konfigurációja PWM üzemmódban
		Tim4Handle.Instance = TIM4;
		Tim4Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		Tim4Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
		Tim4Handle.Init.Prescaler = 25;
		Tim4Handle.Init.Period = 64514;
		Tim4Handle.State = HAL_TIM_STATE_RESET;

		HAL_TIM_Base_Init(&Tim4Handle);
		HAL_TIM_PWM_Init(&Tim4Handle);

		TIM_OC_InitTypeDef TIM_OCInitStructure;
		TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
		TIM_OCInitStructure.Pulse = 0;
		TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
		TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
		TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
		TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;
		TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

		HAL_TIM_PWM_ConfigChannel(&Tim4Handle, &TIM_OCInitStructure, TIM_CHANNEL_1);

		HAL_TIM_PWM_Start(&Tim4Handle, TIM_CHANNEL_1);

		Tim4Handle.Instance->CCR1 = 4846;
}

void set_compare_value_gy_szervo(uint16_t value){

	if(value > GYARI_SZ_MAX_CMP)
	{
		Tim4Handle.Instance->CCR1 = GYARI_SZ_MAX_CMP;
	} else if(value < GYARI_SZ_MIN_CMP)
	{
		Tim4Handle.Instance->CCR1 = GYARI_SZ_MIN_CMP;
	} else {
		Tim4Handle.Instance->CCR1 = value;
	}
}

void set_compare_value_sajat_szervo(uint16_t value){

	if(value > SAJAT_SZ_MAX_CMP)
	{
		Tim4Handle.Instance->CCR1 = SAJAT_SZ_MAX_CMP;
	} else if(value < SAJAT_SZ_MIN_CMP)
	{
		Tim4Handle.Instance->CCR1 = SAJAT_SZ_MIN_CMP;
	} else {
		Tim4Handle.Instance->CCR1 = value;
	}
}

void set_compare_value_digit_szervo(uint16_t value){

	if(value > DIGIT_SZ_MAX_CMP)
	{
		Tim2Handle.Instance->CCR1 = DIGIT_SZ_MAX_CMP;
	} else if(value < DIGIT_SZ_MIN_CMP)
	{
		Tim2Handle.Instance->CCR1 = DIGIT_SZ_MIN_CMP;
	} else {
		Tim2Handle.Instance->CCR1 = value;
	}
}





/*

void TimerHandler() {
//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	is_delayed = 0;
}



uint16_t elso, masodik;
int32_t kuszob;
uint8_t overflow;
void wait_for_x_time(){
	elso = Tim7Handle.Instance->CNT;
	if(elso > 52400){
		overflow = 1;
	} else {
		overflow = 0;
	}
	if(overflow){
		kuszob = 12600 - (65000-elso);
		masodik = Tim7Handle.Instance->CNT;

	} else {
		kuszob = 12600;
	}

	return;
}
*/
