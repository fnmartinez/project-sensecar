/*
 * utils.h
 *
 *  Created on: 23/11/2012
 *      Author: facundo
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

#define INPUT 0x00
#define OUTPUT 0xFF

typedef enum {
	false,
	true
} boolean;

typedef enum {
	NO_COMMAND
} command_type_t;

typedef struct _command_t command_t;
typedef uint8_t ip_t[4];

struct _command_t {
	command_type_t cmd;
	uint8_t args[512];
};

#endif /* UTILS_H_ */
