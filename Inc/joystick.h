/*
 * joystick.h
 *
 *  Created on: Jun 13, 2024
 *      Author: es-2
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

enum JoyKeys{
	JOY_R,
	JOY_L,
	JOY_D,
	JOY_U,
	JOY_C
};

void joystick_init();
int  joystick_read(int key);


#endif /* INC_JOYSTICK_H_ */
