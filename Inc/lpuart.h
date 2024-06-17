/*
 * usart.h
 *
 *  Created on: May 7, 2024
 *      Author: es-2
 */

#ifndef INC_LPUART_H_
#define INC_LPUART_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "gpio_pinned.h"

#define LPUART_REGISTER 	((lpuart_t*)(0x40008000))
#define LPUART_RCC			((uint32_t*)(RCC_REGS + 0x5C))
#define LPUART_EN	 		(1<<0)
#define LP_CLK_EN			(1<<5)

#define AF8		 			(8)

#define CR1_M1 				(1<<28)
#define CR1_M0 				(1<<12)
#define CR1_PS 				(1<<9)

#define CR1_UE 				(1<<0)
#define CR1_RE				(1<<2)
#define CR1_TE				(1<<3)
#define CR1_RXNEIE 			(1<<5)
#define CR2_STOP	 		(3<<12)
#define CR3_DMAT 			(1<<7)
#define CR3_DMAR 			(1<<6)
#define ISR_TC				(1<<6)
#define ISR_TXE				(1<<7)
#define ISR_RXNE			(1<<5)

#define F_CLK	 			(4000000)
#define BAUD_RATE	 		(115200)
#define OVERSAMPLING		(256)

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t BRR;
	uint32_t RESERVED[2];
	volatile uint8_t RQR;
	uint8_t RQR_RESERVED[3];
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint16_t RDR;
	uint16_t RDR_RESERVED;
	volatile uint16_t TDR;
	uint16_t TDR_RESERVED;
} lpuart_t;

void lpuart_init();
void transmit_char(char c);
void transmit_string(char* const str);
char recieve_char();

int get_data_bit_count();
int get_parity_bit_count();
int get_baud_rate();

#endif /* INC_LPUART_H_ */
