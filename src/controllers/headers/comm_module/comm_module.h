/*
 * comm_module.h
 *
 *  Created on: 23/11/2012
 *      Author: facundo
 */

#ifndef COMM_MODULE_H_
#define COMM_MODULE_H_
#include "../utils/commons.h"
#include "info_module/info_module.h"
#include "ctrl_module/ctrl_module.h"

void init_comm(void);
void communicate_changes(void);
void checkout_cmd();
boolean command_recieved(void);

#endif /* COMM_MODULE_H_ */
