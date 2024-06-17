#include "lpuart.h"

void lpuart_init(){
	enable_gpio_clock(GPIO_C_CLK);
	(*LPUART_RCC) |= (LPUART_EN);

	// Configure TX pin
	GPIO_C->MODER &= ~MODE_ALT_MASK;
	GPIO_C->MODER |= MODE_ALT;
	GPIO_C->AFRL |= AF8;
	// Configure RX pin
	GPIO_C->MODER &= ~(MODE_ALT_MASK << 2);
	GPIO_C->MODER |= MODE_ALT << 2;
	GPIO_C->AFRL |= AF8 << 4;

	LPUART_REGISTER->CR1 &= ~(CR1_M1 | CR1_M0);
	LPUART_REGISTER->BRR = (OVERSAMPLING*F_CLK)/BAUD_RATE;

	LPUART_REGISTER->CR2 &= ~CR2_STOP;
	LPUART_REGISTER->CR1 |= CR1_UE;
	LPUART_REGISTER->CR3 &= ~CR3_DMAT;
	LPUART_REGISTER->CR3 &= ~CR3_DMAR;
	LPUART_REGISTER->CR1 |= CR1_RXNEIE;
	LPUART_REGISTER->CR1 |= (CR1_RE | CR1_TE);
}

void transmit_char(char c){
	while(!(LPUART_REGISTER->ISR & ISR_TXE)){}
	LPUART_REGISTER->TDR = c;
	while(!(LPUART_REGISTER->ISR & ISR_TC)){}
}

void transmit_string(char* const str){
	char * it = str;
	while(*it != '\0'){
		transmit_char(*it);
		it++;
	}
}

char recieve_char(){
	while(!(LPUART_REGISTER->ISR & ISR_RXNE)){}
	char c = LPUART_REGISTER->RDR;
	return c;
}

int  get_data_bit_count(){
	int val = LPUART_REGISTER->CR1 & (CR1_M1 | CR1_M0);
	if(val==0){
		return 8;
	}
	if(val==1){
		return 9;
	}
	if(val==2){
		return 7;
	}

	return -1;
}

int get_parity_bit_count(){
	if(LPUART_REGISTER->CR1 & CR1_PS){
		return 1;
	}
	return 0;
}

int get_baud_rate(){
	return (OVERSAMPLING*F_CLK)/LPUART_REGISTER->BRR;
}


