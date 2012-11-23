/*
 * main.h
 *
 *  Created on: 23/11/2012
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "../utils/utils.h"
#include "../comm_module/comm_module.h"
#include "../sense_module/sense_module.h"

command_t command_fetched;

void init(void);
void execute_cmd(void);

#endif /* MAIN_H_ */
