/*
 * controller.h
 *
 *  Created on: Jun 11, 2024
 *      Author: es-2
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

#include <string.h>
#include <stdlib.h>
#include "lpuart.h"
#include "diodes.h"
#include "timer.h"
#include "display.h"

typedef enum CommandStatus{
	Invalid, 		// Invalid command
	MissingArg,		// Missing argument
	InvalidArg,		// Invalid argument
	TooManyArg,		// Too many arguments
	ValidArg,		// Valid argument
	Failed,			// Command failed
	Success,		// Command succeeded
}command_status_t;

void controller_init();
void controller_step();

int diode_enable(char *arg);
int diode_disable(char *arg);
int diode_flip(char *arg);
int diode_status(char *arg);
int diode_start_blink(char *arg);

int controller_display_number(char *arg);
int controller_display_clear(char *arg);
int controller_display_read(char *arg);
int controller_joy_read(char *arg);
int controller_lpuart_status(char *arg);

#endif /* INC_CONTROLLER_H_ */
