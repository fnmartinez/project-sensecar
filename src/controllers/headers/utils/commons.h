/*
 * commons.h
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#ifndef COMMONS_H_
#define COMMONS_H_

#include "utils.h"
#define SENSORS_QTY 8
#define SENSOR_ON 1
#define SENSOR_OFF 0
typedef uint8_t sensors_t[SENSORS_QTY];

boolean sensors_updated;
sensors_t sensors;
boolean command_arrived;
command_t command_fetched;

#endif /* COMMONS_H_ */
