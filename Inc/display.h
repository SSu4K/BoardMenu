/*
 * display.h
 *
 *  Created on: Jun 4, 2024
 *      Author: es-2
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#define MAX_NUMBER 			(9999)
#define MIN_NUMBER 			(0)

#define DIGIT_COUNT 		(4)
#define DIGIT_DELAY 		(1)
#define NUMBER_DELAY			(DIGIT_COUNT*DIGIT_DELAY)

void display_init();
void display_digit(int value, const int place);
void display_number(int number);
void display_clear();

#endif /* INC_DISPLAY_H_ */
