#ifndef INC_MENU_H__
#define INC_MENU_H__

#include <string.h>
#include <ctype.h>
#include "controller.h"

#define SECTION_NAME_COUNT 	4

typedef struct{
	char* 	name;
	char*	help;
	int   	has_arg;
	int		(*run)(char* arg);
}command_t;

typedef struct{
	char* name;
	int command_count;
	command_t* commands;
}section_t;

void menu_init();
char* get_section_name();
int handle_command(char* command);

#endif
