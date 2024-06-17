#include "main.h"
#include "gpio_pinned.h"
#include "timer.h"
#include "display.h"
#include <stdlib.h>

#define SEGMENT_COUNT 		(7)
#define NUMBER_COUNT 		(10)
#define EMPTY_DIGIT			(10)

#define DELAY 				(1000)

const pin_t SEGMENT[SEGMENT_COUNT] = {
		{GPIO_G, 0},
		{GPIO_G, 1},
		{GPIO_G, 2},
		{GPIO_G, 3},
		{GPIO_G, 4},
		{GPIO_G, 5},
		{GPIO_G, 6},
};

const pin_t DIGIT[DIGIT_COUNT] = {
		{GPIO_B, 5},
		{GPIO_B, 4},
		{GPIO_B, 3},
		{GPIO_B, 2},
};

const pin_t JOY_OK = {GPIO_E, 15};

const uint16_t NUMBER_SEGMENTS[NUMBER_COUNT] = {
		0b0111111,
		0b0000110,
		0b1011011,
		0b1001111,
		0b1100110,
		0b1101101,
		0b1111101,
		0b0000111,
		0b1111111,
		0b1101111
};

void display_init(){
	enable_gpio_clock(GPIO_G_CLK);
	enable_gpio_clock(GPIO_B_CLK);
	enable_vddio2();

	init_t init_struct = {0};
	init_struct.mode = MODE_OUT;
	init_struct.type = TYPE_PP;
	init_struct.pull = PULL_NO;
	init_struct.speed = SPEED_LOW;
	  //init_joy();
	for(int i=0;i<SEGMENT_COUNT;i++){
		init_pin(&SEGMENT[i], &init_struct);
		write_pin(&SEGMENT[i], PIN_RESET);
	}

	for(int i=0;i<DIGIT_COUNT;i++){
		init_pin(&DIGIT[i], &init_struct);
		write_pin(&DIGIT[i], PIN_RESET);
	}
}

void display_digit(int value, const int place){

	uint16_t segments = 0;
	if(value >= 0 || value <= 9){
		segments = NUMBER_SEGMENTS[value];
	}

	if(place < 0 || place >= DIGIT_COUNT) return;

	for(int i=0;i<SEGMENT_COUNT;i++){
		write_pin(&SEGMENT[i], PIN_SET & (segments & 0x1));
		segments >>= 1;
	}
	write_pin(&DIGIT[place], PIN_SET);
	timer_delay(DIGIT_DELAY);
	write_pin(&DIGIT[place], PIN_RESET);
}

void display_number(int number){
	for(int i=0;i<DIGIT_COUNT;i++){
		if(number == 0 && i!=0){
			display_digit(10, i);
		}else{
			display_digit(number%10, i);
			number /= 10;
		}
	}
}

void display_clear(){
	for(int i=0;i<DIGIT_COUNT;i++){
		display_digit(EMPTY_DIGIT, i);
		write_pin(&DIGIT[i], PIN_RESET);
	}
}

