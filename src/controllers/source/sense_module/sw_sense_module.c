/*
 * sw_sense_module.c
 *
 *  Created on: 23/11/2012
 */

#include "../../headers/sense_module/sw_sense_module.h"

void init_sensors(void) {
	SWS_DDR = INPUT;
}

void read_sensors(void) {
	switch_t samples[SAMPLE_SIZE];
	uint32_t i;
	for (i = 0; i < SAMPLE_SIZE; i++) {
		samples[i] = SWS_NONE ^ SWS_PIN;
		_delay_ms(RIPPLE_DELAY);
	}

	switch_t result = evaluate_samples(samples, SAMPLE_SIZE);

	update_sensors(result);

}

switch_t evaluate_samples(switch_t* samples, uint32_t samples_left) {
	return (samples_left == 0) ?
			(switch_t) SWS_NONE :
			*samples & evaluate_samples(samples + 1, samples_left - 1);
}

void update_sensor(switch_t sensed_status) {
	uint32_t i = 0;

	for(i = 0; i < SENSORS_QTY; i++) {
		sensed_status >>= i;
		if(sensors[i] != sensed_status%2) {
			sensors_updated = true;
		}
		sensors[i] = sensed_status%2;
	}
}

boolean sensors_changed() {
	return sensors_updated;
}
