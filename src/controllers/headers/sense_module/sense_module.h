/*
 * sense_module.h
 *
 *  Created on: 23/11/2012
 *      Author: facundo
 */

#ifndef SENSE_MODULE_H_
#define SENSE_MODULE_H_
#include "../headers/main_module/main.h"

void init_sensors(void);
void read_sensors(void);
boolean sensors_changed(void);


#endif /* SENSE_MODULE_H_ */
