/*
 * timer.c
 *
 *  Created on: Apr 19, 2024
 *      Author: es-2
 */
#include "timer.h"

#define RCC_TIM6 (1<<4);
#define OPM 	(1<<3)
#define CEN 	(1<<0)
#define URS		(1<<2)
#define UDIS	(1<<1)
#define ARPE	(1<<7)

void timer_reset(){
	TIMER_REGISTER->SR &= ~0x1;
	TIMER_REGISTER->CR1 |= CEN;
}

void timer_init(uint16_t tick_period, uint16_t arr){
	*TIMER_RCC |= RCC_TIM6;

	TIMER_REGISTER->CR1 &= ~OPM;

	TIMER_REGISTER->PSC = tick_period;
	TIMER_REGISTER->ARR = arr;
	TIMER_REGISTER->CR1 |= CEN;
}

void timer_delay(int ticks){
	for(int i=0;i<ticks;i++){
		TIMER_REGISTER->SR &= ~(1<<0);
		while(TIMER_REGISTER->SR != 1){}
	}
}
