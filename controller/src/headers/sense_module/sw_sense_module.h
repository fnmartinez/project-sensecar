/*
 * sw_sense_module.c
 *
 *  Created on: 23/11/2012
 */

#ifndef SW_SENSE_MODULE_C_
#define SW_SENSE_MODULE_C_
#include "sense_module.h"
#include "../utils/switches.h"
#include <util/delay.h>

#define RIPPLE_DELAY 140
#define SAMPLE_SIZE 3

void update_sensor(switch_t sensed_status);
switch_t evaluate_samples(switch_t* samples, uint32_t samples_left);

#endif /* SW_SENSE_MODULE_C_ */
