#ifndef COMMANDPROTOCOLHANDLER_H
#define COMMANDPROTOCOLHANDLER_H

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
	SET_NETWORK_INFO,
	SET_SERVER_IP,
	SET_SERVER_PORT,
	SENSOR_ON,
	SENSOR_OFF,
	GET_STATUS,
	INFORM_STATUS,
	EXIT
};

typedef enum Commands_enum Commands_t;

class CommandProtocolHandler {
private:
	Commands_t allCommands[TOTAL_COMMANDS];
	char * commandsString[];
	int totalCommand;
public:
	CommandProtocolHandler();
	Commands_t * getProtocolCommands();
	char ** getProtocolCommandsString();
	int getProtocolCommandsQuantity();
	virtual void checkForClients() =0;
	virtual void begin()=0;
	virtual ~CommandProtocolHandler();
};

#endif
