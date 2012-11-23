/*
 * main.c
 *
 *  Created on: 23/11/2012
 */
#include "../headers/main_module/main.h"

int main() {

	init();

	while(true){

		checkout_cmd();
		if(command_recieved() == true) {
			execute_cmd();
		}

		read_sensors();

		if(sensors_changed() == true) {
			communicate_changes();
		}

	}
}


void init(void) {

	init_sensors();
	init_comm();
}

boolean command_recieved(void) {
	return false;
}

void execute_cmd(void) {

}
