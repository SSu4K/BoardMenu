/*
 * controller.c
 *
 *  Created on: Jun 11, 2024
 *      Author: es-2
 */
#include "controller.h"
#include "joystick.h"

#define MAX_TIME	(100)
#define BLINK_COUNT	(40)
#define NO_BLINK	(-1)


int blink_times[DIODE_COUNT] = {};
int blink_counts[DIODE_COUNT] = {};
int current_number = 0;
int is_display_number = 0;


static int time = 0;

void controller_init(){
	time = 0;
	current_number = 0;
	is_display_number = 0;
	timer_init(9, 399);
	display_init();
	diodes_init();
	joystick_init();
	for(int i=0;i<DIODE_COUNT;i++){
		blink_times[i] = NO_BLINK;
		blink_counts[i] = 0;
	}
}

void increment_time(){
	time++;
	if(time>=MAX_TIME){
		time = 0;
	}
}

void controller_step(){
	for(int i=0;i<DIODE_COUNT;i++){
		if(blink_times[i] != NO_BLINK && blink_counts[i] > 0){
			if((((time-blink_times[i]) + MAX_TIME)%MAX_TIME) % MAX_TIME == 0){
				diode_toggle(i);
				blink_counts[i]--;
			}
		}
	}
	if(is_display_number){
		display_number(current_number);
	}
	else{
		timer_delay(NUMBER_DELAY);
	}
	increment_time();
}

int get_diode_id(char *arg, int *error){
	if(arg == NULL){
		*error = MissingArg;
		return -1;
	}
	*error = ValidArg;
	if(strcasecmp("r", arg) == 0){
		return 8;
	}
	if(strcasecmp("g", arg) == 0){
		return 9;
	}
	if(strcasecmp("b", arg) == 0){
		return 10;
	}

	char *endptr;
	int i = strtol(arg, &endptr, 10);

	if(*endptr == '\0' && i>=0 && i<8){
		return i;
	}

	*error = InvalidArg;
	return -1;
}

int diode_enable(char *arg){
	int error;
	int i = get_diode_id(arg, &error);
	if(error == ValidArg){
		return diode_set(i) ? Success : Failed;
	}
	return error;
}
int diode_disable(char *arg){
	int error;
	int i = get_diode_id(arg, &error);
	if(error == ValidArg){
		return diode_reset(i) ? Success : Failed;
	}
	return error;
}
int diode_flip(char *arg){
	int error;
	int i = get_diode_id(arg, &error);
	if(error == ValidArg){
		return diode_toggle(i) ? Success : Failed;
	}
	return error;
}
int diode_status(char *arg){
	int error;
	int i = get_diode_id(arg, &error);
	if(error == ValidArg){
		if(diode_read(i)){
			transmit_string("\n\rDiode ON");
		}
		else{
			transmit_string("\n\rDiode OFF\n\r");
		}
		return Success;
	}
	return error;
}

int diode_start_blink(char *arg){
	int error;
	int i = get_diode_id(arg, &error);
	if(error == ValidArg){
		blink_times[i] = time;
		blink_counts[i] = 2*BLINK_COUNT;
		diode_reset(i);
		return Success;
	}
	return error;
}

int controller_display_number(char *arg){
	if(arg == NULL){
		return MissingArg;
	}
	char *endptr;
	int i = strtol(arg, &endptr, 10);
	if(*endptr == '\0' && i>=MIN_NUMBER && i<MAX_NUMBER){
		current_number = i;
		is_display_number = 1;
		return Success;
	}

	return InvalidArg;
}

int controller_display_clear(char *arg){
	display_clear();
	is_display_number = 0;
	return Success;
}

int controller_display_read(char *arg){
	transmit_string("\n\rCurrently displaying: ");
	char buffer[5];
	if(is_display_number){
		itoa(current_number, buffer, 10);
		transmit_string(buffer);
	}
	else{
		transmit_string("NOTHING");
	}
	return Success;
}

int controller_joy_read(char *arg){
	if(arg == NULL){
		return MissingArg;
	}
	int error = ValidArg;
	int value = 0;
	if(strcasecmp(arg, "L") == 0){
		value = joystick_read(JOY_L);
	}
	else if(strcasecmp(arg, "R") == 0){
		value = joystick_read(JOY_R);
	}
	else if(strcasecmp(arg, "U") == 0){
		value = joystick_read(JOY_U);
	}
	else if(strcasecmp(arg, "D") == 0){
		value = joystick_read(JOY_D);
	}
	else if(strcasecmp(arg, "C") == 0){
		value = joystick_read(JOY_C);
	}
	else{
		error = InvalidArg;
	}

	if(error == ValidArg){
		if(value == 1){
			transmit_string("\n\rPRESSED");
		}
		else{
			transmit_string("\n\rNOT PRESSED");
		}
		error = Success;
	}

	return error;
}

int controller_lpuart_status(char *arg){
	char baud_message[25] = "\n\r  Baud rate: ";
	char * ptr = strchr(baud_message, '\0');
	itoa(get_baud_rate(), ptr, 10);
	char data_message[20] = "\n\r  Data bits: ";
	ptr = strchr(data_message, '\0');
	itoa(get_data_bit_count(), ptr, 10);
	char parity_message[20] = "\n\r  Parity bits: ";
	ptr = strchr(parity_message, '\0');
	itoa(get_parity_bit_count(), ptr, 10);

	transmit_string(baud_message);
	transmit_string(data_message);
	transmit_string(parity_message);
	return Success;
}
