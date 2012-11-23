/*
 * sw_sense_module.c
 *
 *  Created on: 23/11/2012
 */

#include "../headers/sense_module/sw_sense_module.h"


void init_sensors(void) {
	SWS_DDR = INPUT;
}

void read_sensors(void) {
	switch_t sws;
	uint32_t i;
	sws = SWS_NONE ^ SWS_PIN;
}
