/*
 * diode.c
 *
 *  Created on: Jun 11, 2024
 *      Author: es-2
 */
#include "diodes.h"

const pin_t DIODE[DIODE_COUNT] = {
		{GPIO_C, 6},
		{GPIO_C, 7},
		{GPIO_C, 8},
		{GPIO_C, 9},
		{GPIO_E, 4},
		{GPIO_D, 3},
		{GPIO_E, 5},
		{GPIO_E, 6},
		{GPIO_D, 13},
		{GPIO_B, 8},
		{GPIO_D, 12}
};

void diodes_init(){
	enable_gpio_clock(GPIO_C_CLK);
	enable_gpio_clock(GPIO_E_CLK);
	enable_gpio_clock(GPIO_D_CLK);
	enable_gpio_clock(GPIO_B_CLK);
	init_t init = {
			MODE_OUT,
			TYPE_PP,
			PULL_NO,
			SPEED_LOW
	};
	for(int i=0;i<DIODE_COUNT;i++){
		init_pin(&DIODE[i], &init);
	}
}

int diode_set(int i){
	if(i < 0 || i >= DIODE_COUNT){
		return 0;
	}
	write_pin(&DIODE[i], PIN_SET);
	return 1;
}

int diode_reset(int i){
	if(i < 0 || i >= DIODE_COUNT){
		return 0;
	}
	write_pin(&DIODE[i], PIN_RESET);
	return 1;
}

int diode_toggle(int i){
	if(i < 0 || i >= DIODE_COUNT){
		return 0;
	}
	int val = read_pin(&DIODE[i]);
	write_pin(&DIODE[i], !val);
	return 1;
}

int diode_read(int i){
	if(i < 0 || i >= DIODE_COUNT){
		return 0;
	}
	return read_pin(&DIODE[i]);
}


