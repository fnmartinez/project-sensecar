/*
 * EthernetCommandProtocolHandler.cpp
 *
 *  Created on: 23/02/2013
 *      Author: facundo
 */

#include <EthernetCommandProtocolHandler.h>

EthernetCommandProtocolHandler::EthernetCommandProtocolHandler(int port) {
	this->port = port;
	this->server = &EthernetServer(this->port);
}

void EthernetCommandProtocolHandler::respond(EthernetClient c, char * response, char * msg, char * terminator) {
	c.print(response);
	if(msg != NULL) {
		c.print(msg);
	}
	c.print(terminator);
}

void EthernetCommandProtocolHandler::checkForClients() {
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

void EthernetCommandProtocolHandler::begin() {
	this->server->begin();
}

EthernetCommandProtocolHandler::~EthernetCommandProtocolHandler() {

}
