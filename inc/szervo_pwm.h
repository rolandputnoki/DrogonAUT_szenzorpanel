/*
 * gyari_szervo_pwm.h
 *
 *  Created on: 2017. okt. 29.
 *      Author: Roland
 */

#pragma once
#ifndef SZERVO_PWM_H_
#define SZERVO_PWM_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include "vonalsensor.h"


extern uint16_t szervo_value;

//Min-Max értéke az RC PWM jel pulzusszélességéhez
#define GYARI_SZ_MIN_CMP 3817
#define GYARI_SZ_MAX_CMP 8017

#define GYARI_SZ_KOZEP 5902

#define DIGIT_SZ_MIN_CMP 24500
#define DIGIT_SZ_MAX_CMP 38500
#define DIGIT_SZ_KOZEP 31500

//alap = 1666
#define hiba_szab_suly 3000


#define SAJAT_SZ_MIN_CMP 23099
#define SAJAT_SZ_MAX_CMP 40739

extern TIM_HandleTypeDef Tim4Handle, Tim2Handle, Tim7Handle;
extern uint32_t loop_counter;

extern uint8_t is_delayed;


void Init_GY_Szervo_PWM();
void Init_Digit_Szervo_PWM();
void Init_sajat_Szervo_PWM();
void Init_AF_szervo();
void set_compare_value_gy_szervo(uint16_t);
void set_compare_value_sajat_szervo(uint16_t);
void set_compare_value_digit_szervo(uint16_t);



#endif /* SZERVO_PWM_H_ */
