/*
 * info_module.h
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#ifndef INFO_MODULE_H_
#define INFO_MODULE_H_
#include "../../utils/commons.h"
#include "../../protocols/info_protocol.h"

void init_info();
void info_comm_changes(sensors_t sensors);

#endif /* INFO_MODULE_H_ */
