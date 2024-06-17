#include "menu.h"
#include "lpuart.h"

#define SECTION_COUNT 			(5)

#define HOME_COMMAND_COUNT 		(5)
#define DIODE_COMMAND_COUNT 	(7)
#define SEGMENT_COMMAND_COUNT 	(5)
#define JOY_COMMANDS_COUNT		(3)
#define LPUART_COMMANDS_COUNT	(3)

int go_section_home(char *arg);
int go_section_diode(char *arg);
int go_section_segment(char *arg);
int go_section_joy(char *arg);
int go_section_lpuart(char *arg);
int help_commands(char *arg);

const command_t UP_COMMAND = {"UP", "go to the home section.", 0, go_section_home};
const command_t HELP_COMMAND = {"HELP", "show help", 0, help_commands};

command_t HOME_COMMANDS[HOME_COMMAND_COUNT] = {
		{"DIODE", "go to the diode section.", 0, go_section_diode},
		{"7SEG", "go to the 7 segment display section.", 0, go_section_segment},
		{"JOY", "go to the joystick section.", 0, go_section_joy},
		{"LPUART", "go to the lpuart section.", 0, go_section_lpuart},
		HELP_COMMAND
};

command_t DIODE_COMMANDS[DIODE_COMMAND_COUNT] = {
		UP_COMMAND,
		{"SET", "set <id> - set #id diode.", 1, diode_enable},
		{"RESET", "reset <id> - reset #id diode.", 1, diode_disable},
		{"TOGGLE", "toggle <id> - toggle #id diode.", 1, diode_flip},
		{"STATUS", "status <id> - get status of #id diode.", 1, diode_status},
		{"BLINK", "blink <id> - start blinking for #id diode.", 1, diode_start_blink},
		HELP_COMMAND
};

command_t SEGMENT_COMMANDS[SEGMENT_COMMAND_COUNT] = {
		UP_COMMAND,
		{"DISPLAY", "display <number> - show number on the 7 segment display.", 1, controller_display_number},
		{"CLEAR", "clear the the 7 segment display.", 0, controller_display_clear},
		{"READ", "read and show the the 7 segment display content.", 0, controller_display_read},
		HELP_COMMAND
};

command_t JOY_COMMANDS[SEGMENT_COMMAND_COUNT] = {
		UP_COMMAND,
		{"READ", "read <key> - read joystick key (L, R, U, D, C).", 1, controller_joy_read},
		HELP_COMMAND
};

command_t LPUART_COMMANDS[LPUART_COMMANDS_COUNT] = {
		UP_COMMAND,
		{"STATUS", "Get current configuration of the lpuart device.", 0, controller_lpuart_status},
		HELP_COMMAND
};

section_t SECTIONS[SECTION_COUNT] = {
		{"", HOME_COMMAND_COUNT, HOME_COMMANDS},
		{"DIODE", DIODE_COMMAND_COUNT, DIODE_COMMANDS},
		{"7SEG", SEGMENT_COMMAND_COUNT, SEGMENT_COMMANDS},
		{"JOY", JOY_COMMANDS_COUNT, JOY_COMMANDS},
		{"LPUART",  LPUART_COMMANDS_COUNT, LPUART_COMMANDS},
};

int current_section_id = 0;

void menu_init(){
	controller_init();
}

char* get_section_name(){
	return SECTIONS[current_section_id].name;
}

int handle_command(char * input){
	section_t section = SECTIONS[current_section_id];
	char * command = strtok(input, " ");
	char * arg = strtok(NULL, " ");
	char * end = strtok(NULL, " ");

	if(*end != '\0'){
		return TooManyArg;
	}

	for(int i=0;i<section.command_count; i++){
		command_t section_command = section.commands[i];
		if(strcasecmp(command, section_command.name)==0){
			if(section_command.has_arg == 1 && arg == NULL){
				return MissingArg;
			}
			if(section_command.has_arg == 0 && arg != NULL){
				return TooManyArg;
			}
			return section_command.run(arg);
			//return 0;
		}
	}
	return Invalid;
}

int go_section_home(char *arg){
	current_section_id = 0;
	return Success;
}

int go_section_diode(char *arg){
	current_section_id = 1;
	return Success;
}

int go_section_segment(char *arg){
	current_section_id = 2;
	return Success;
}

int go_section_joy(char *arg){
	current_section_id = 3;
	return Success;
}

int go_section_lpuart(char *arg){
	current_section_id = 4;
	return Success;
}

int help_commands(char *arg){
	transmit_string("\n\rAvailable commands:\n\r");
	section_t section = SECTIONS[current_section_id];
	for(int i=0;i<section.command_count; i++){
		command_t command = section.commands[i];
		transmit_string("   - ");
		transmit_string(command.name);
		transmit_string(": ");
		transmit_string(command.help);
		transmit_string("\n\r");
	}
	return Success;
}
