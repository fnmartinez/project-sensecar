/*
 * leds_info_module.c
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#include "../../headers/comm_module/info_module/leds_info_module.h"

/*
 * XXX: Este código no es para NADA representativo de lo que debería
 * hacer el protocolo de módulo de información más que en un sentido
 * estrictamente básico. O sea, informa del estado de cada sensor.
 *
 * El módulo debería llamar a funciones provistas por el protocolo de
 * información, que permiten codificar los mensajes, y
 * eso después enviarlo por el medio que dicho módulo encapsula.
 *
 */
void init_info() {
	led_status  = 0x00;

	LEDS_DDR = OUTPUT;
}

void info_comm_changes(sensors_t sensors) {

	uint32_t i;

	for(i = 0; i < SENSORS_QTY; i++) {
		if(sensors[i] == SENSOR_ON) {
			led_on(leds[i]);
		}
		else if (sensors[i] == SENSOR_OFF) {
			led_off(leds[i]);
		}
	}

	sensors_updated = false;
}
