#include "gpio_pinned.h"

void enable_gpio_clock(int index){
	*GPIO_RCC |= (1<<index);
}

void enable_vddio2(){
	(*PWR_REGISTER_CR) |= VDDIO2_MASK;
}


void init_pin(const pin_t* pin, init_t* init){
	if(pin->number>MAX_PIN_NUMBER || pin->number<MIN_PIN_NUMBER){
		return;
	}
	gpio_t* gpio = pin->gpio;
	const uint16_t number = pin->number;

	gpio->MODER &= ~(3<<(2*number));
	gpio->MODER |= (init->mode<<(2*number));

	gpio->OTYPER &= ~(3<<(2*number));
	gpio->OTYPER |= (init->type<<(2*number));

	gpio->OSPEEDR &= ~(3<<(2*number));
	gpio->OSPEEDR |= (init->speed<<(2*number));

	gpio->PUPDR &= ~(3<<(2*number));
	gpio->PUPDR |= (init->pull<<(2*number));
}

void write_pin(const pin_t* pin, int state){
	if(pin->number>MAX_PIN_NUMBER || pin->number<MIN_PIN_NUMBER){
		return;
	}
	if(state == PIN_SET){
		pin->gpio->BSRR |= (1<<(pin->number));
	}
	else{
		pin->gpio->BRR |= (1<<(pin->number));
	}

}

int read_pin(const pin_t* pin){
	if(pin->number>MAX_PIN_NUMBER || pin->number<MIN_PIN_NUMBER){
		return PIN_RESET;
	}
	int value = (pin->gpio->IDR & (1<<pin->number));
	if(value != 0x00){
		return PIN_SET;
	}
	else{
		return PIN_RESET;
	}
}
