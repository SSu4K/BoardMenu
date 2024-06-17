/*
 * timer.h
 *
 *  Created on: Apr 19, 2024
 *      Author: es-2
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdint.h>

#define TIMER_RCC 		((uint32_t *)(0x40021000+0x58))
#define TIMER_REGISTER 	((timer_t *)0x40001000)

typedef struct {
	volatile uint16_t CR1;
	volatile uint16_t CR1reserved;
	volatile uint8_t CR2;
	volatile uint8_t CR2reserved[3];
	volatile uint32_t RESERVED;
	volatile uint16_t DIER;
	volatile uint16_t DIERReserved;
	volatile uint16_t SR;
	volatile uint16_t SRReserved;
	volatile uint16_t EGR;
	volatile uint16_t EGRReserved;
	volatile uint32_t RESERVED2[3];
	volatile uint32_t CNT;
	volatile uint16_t PSC;
	volatile uint16_t PSCReserved;
	volatile uint16_t ARR;
	volatile uint16_t ARRReserved;
}timer_t;

void timer_reset();
void timer_init(uint16_t tick_period, uint16_t arr);

void timer_delay(int ticks);

#endif /* INC_TIMER_H_ */
