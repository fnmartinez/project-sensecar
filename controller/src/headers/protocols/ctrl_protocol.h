/*
 * ctrl_protocol.h
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#ifndef CTRL_PROTOCOL_H_
#define CTRL_PROTOCOL_H_
#include "../utils/commons.h"

#define CMDS_QTY 5
#define STANDBY "standby"
#define WAKEUP "wakeup"
#define CHANGEIP "changeip"
#define CHANGEMASTERIP "changemasterip"
#define STATUS "status"

#define OKRESPONSE "+OK"
#define ERRRESPONSE "-ERR"

#define COMMAND_MAX_LEN 128

#define RESPONSE_MAX_LEN 128

typedef enum {
	standby = 0,
	wakeup,
	changeip,
	changemasterip,
	status
} commands_t;

char ** cmd_headers = {
		STANDBY,
		WAKEUP,
		CHANGEIP,
		CHANGEMASTERIP,
		STATUS
};


#endif /* CTRL_PROTOCOL_H_ */
