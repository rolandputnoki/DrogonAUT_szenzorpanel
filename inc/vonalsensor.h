/*
 * vonalsensor.h
 *
 *  Created on: 2017. nov. 18.
 *      Author: Patrik
 */

#ifndef VONALSENSOR_H_
#define VONALSENSOR_H_

#include "stm32f4xx.h"


void set_Leds_Tcrts();
void vonal(uint16_t *);

extern uint16_t kulonbseg[20];

#endif /* VONALSENSOR_H_ */
