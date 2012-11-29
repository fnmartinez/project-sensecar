/*
 * main.c
 *
 *  Created on: 23/11/2012
 */
#include "../headers/main_module/main.h"

int main() {

	init();

	while(true){

		if(command_recieved() == true) {
			checkout_cmd();
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

void execute_cmd(void) {

}
