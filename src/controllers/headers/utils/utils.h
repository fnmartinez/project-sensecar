/*
 * utils.h
 *
 *  Created on: 23/11/2012
 *      Author: facundo
 */

#ifndef UTILS_H_
#define UTILS_H_

typedef enum {
	false,
	true
} boolean;

typedef enum {
	NO_COMMAND
} command_type_t;

typedef struct _command_t command_t;

struct _command_t {
	command_type_t cmd;
};
#endif /* UTILS_H_ */
