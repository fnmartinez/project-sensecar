#ifndef COMMAND_MODULE_H_
#define COMMAND_MODULE_H_

#include <Ethernet.h>

#define OK_RESPONSE "+OK "
#define ERROR_RESPONSE "-ERR "
#define RESPONSE_TERMINATOR "\r\n.\r\n"
#define MAX_COMMAND_SIZE 257
#define MAX_RESPONSE_SIZE 257
#define COMMAND_MAX_SIZE 16
#define TOTAL_COMMANDS 11

enum Commands_enum {
	NOOP,
	TURN_ON,
	TURN_OFF,
	SHOW_NETWORK_INFO,
	SET_SERVER_IP,
	SET_SERVER_PORT,
	SENSOR_ON,
	SENSOR_OFF,
	GET_STATUS,
	INFORM_STATUS,
	EXIT
};

typedef enum Commands_enum Commands_t;

void beginTCP(int port);
void verifyIncomingCommand();
void respond(EthernetClient c, char * response, char * msg, char * terminator);

#endif /* COMMAND_MODULE_H_ */
