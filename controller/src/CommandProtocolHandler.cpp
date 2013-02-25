
#include <CommandProtocolHandler.h>

CommandProtocolHandler::CommandProtocolHandler(int port) {
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

	this->port = port;
	this->server = &EthernetServer(this->port);
	Serial.println("Ethernet Command server over TCP set");
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

void CommandProtocolHandler::begin() {
	this->server->begin();
	Serial.println("Ethernet Command server over TCP running");
}

void CommandProtocolHandler::respond(EthernetClient c, char * response, char * msg, char * terminator) {
	c.print(response);
	if(msg != NULL) {
		c.print(msg);
	}
	c.print(terminator);
}

void CommandProtocolHandler::checkForClients() {
	bool firstContact = true;
	Commands_t currentState = NOOP;
	char incommingCmd[MAX_COMMAND_SIZE];
	char outcommingResponse[MAX_RESPONSE_SIZE];
	const Commands_t * cmdArray = this->getProtocolCommands();
	const int cmdQty = this->getProtocolCommandsQuantity();
	char ** cmdStrings = this->getProtocolCommandsString();

	EthernetClient client = this->server->available();

	while(client.connected()) {
		if(firstContact) {
			this->respond(client, OK_RESPONSE, "HI!", RESPONSE_TERMINATOR);
			firstContact = false;
		}
		if(client.available() > 0) {
			int i = 0;
			bool terminatorFound = false;
			do {
				incommingCmd[i] = client.read();
				if(incommingCmd[i] == '\n') {
					terminatorFound = true;
					incommingCmd[i] = '\0';
				}
			} while (++i < MAX_COMMAND_SIZE && !terminatorFound);

			for(int i = cmdQty -1;	i>0; i--) {
				if(strncasecmp(cmdStrings[i], incommingCmd, strlen(cmdStrings[i])) == 0){
					currentState = cmdArray[i];
				}
			}

			switch(currentState) {
			case NOOP:
				break;
			case TURN_ON:
				break;
			case TURN_OFF:
				break;
			case SET_NETWORK_INFO:
				break;
			case SET_SERVER_IP:
				break;
			case SET_SERVER_PORT:
				break;
			case SENSOR_ON:
				break;
			case SENSOR_OFF:
				break;
			case GET_STATUS:
				break;
			case INFORM_STATUS:
				break;
			case EXIT:
				client.stop();
				break;
			default:
				break;
			}
		}
	}

}

CommandProtocolHandler::~CommandProtocolHandler() {

}
