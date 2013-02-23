
#include <CommandProtocolHandler.h>

CommandProtocolHandler::CommandProtocolHandler() {
	this->allCommands[0] = 	NOOP;
	this->allCommands[1] = 	TURN_ON;
	this->allCommands[2] = 	TURN_OFF;
	this->allCommands[3] = 	SET_NETWORK_INFO;
	this->allCommands[4] = 	SET_SERVER_IP;
	this->allCommands[5] = 	SET_SERVER_PORT;
	this->allCommands[6] = 	SENSOR_ON;
	this->allCommands[7] = 	SENSOR_OFF;
	this->allCommands[8] = 	GET_STATUS;
	this->allCommands[9] = 	INFORM_STATUS;
	this->allCommands[10] = EXIT;
	this->commandsString[0] =(char*) "NOOP";
	this->commandsString[1] =(char*) "TURN_ON";
	this->commandsString[2] =(char*) "TURN_OFF";
	this->commandsString[3] =(char*) "SET_NETWORK_INFO";
	this->commandsString[4] =(char*) "SET_SERVER_IP";
	this->commandsString[5] =(char*) "SET_SERVER_PORT";
	this->commandsString[6] =(char*) "SENSOR_ON";
	this->commandsString[7] =(char*) "SENSOR_OFF";
	this->commandsString[8] =(char*) "GET_STATUS";
	this->commandsString[9] =(char*) "INFORM_STATUS";
	this->commandsString[10] =(char*) "EXIT";
	this->totalCommand = TOTAL_COMMANDS;
}

char ** CommandProtocolHandler::getProtocolCommandsString() {
	return this->commandsString;
}

Commands_t * CommandProtocolHandler::getProtocolCommands() {
	return this->allCommands;
}

int CommandProtocolHandler::getProtocolCommandsQuantity() {
	return this->totalCommand;
}

CommandProtocolHandler::~CommandProtocolHandler() {

}
