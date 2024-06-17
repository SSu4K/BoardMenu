/*
 * diodes.h
 *
 *  Created on: Jun 11, 2024
 *      Author: es-2
 */

#ifndef INC_DIODES_H_
#define INC_DIODES_H_

#include "gpio_pinned.h"
#define DIODE_COUNT 11

void diodes_init();
int diode_set(int i);
int diode_reset(int i);
int diode_toggle(int i);
int diode_read(int i);

#endif /* INC_DIODES_H_ */
