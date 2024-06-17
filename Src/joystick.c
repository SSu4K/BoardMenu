/*
 * joystick.c
 *
 *  Created on: Jun 13, 2024
 *      Author: es-2
 */
#include "gpio_pinned.h"
#include "joystick.h"

#define KEY_COUNT	(5)

pin_t KEYS[KEY_COUNT]={
		{GPIO_E, 0},
		{GPIO_E, 1},
		{GPIO_E, 2},
		{GPIO_E, 3},
		{GPIO_E, 15}
};

void joystick_init(){
	enable_gpio_clock(GPIO_E_CLK);
	init_t init_struct = {0};
	init_struct.mode = MODE_IN;
	init_struct.pull = PULL_NO;
	init_struct.speed = SPEED_LOW;

	for(int i=0;i<KEY_COUNT;i++){
		init_pin(&KEYS[i], &init_struct);
	}
}

int  joystick_read(int key){
	return read_pin(&KEYS[key]) != PIN_SET;
}

