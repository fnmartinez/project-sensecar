/*
 * comm_module.c
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#include "../headers/comm_module/comm_module.h"

void init_comm(void) {
	init_info();
	init_ctrl();
}

void communicate_changes(void) {

	info_comm_changes(sensors);

}

void checkout_cmd() {

	ctrl_generate_cmd();

}

boolean command_recieved(void) {
	return command_arrived;
}
