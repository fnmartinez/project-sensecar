#include <CommandModule.h>

Commands_t commands[] = {
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

char * commandsString[] = {
	"NOOP",
	"TURN_ON",
	"TURN_OFF",
	"SET_NETWORK_INFO",
	"SET_SERVER_IP",
	"SET_SERVER_PORT",
	"SENSOR_ON",
	"SENSOR_OFF",
	"GET_STATUS",
	"INFORM_STATUS",
	"EXIT"
};

EthernetServer * server;

void beginTCP(int port) {
	server = new EthernetServer(port);
}

void respond(EthernetClient c, char * response, char * msg, char * terminator) {
	c.print(response);
	if(msg != NULL) {
		c.print(msg);
	}
	c.print(terminator);
}

void verifyIncomingCommand() {
	bool firstContact = true;
	char * response;
	char message[MAX_RESPONSE_SIZE];
	Commands_t currentState = NOOP;
	char incommingCmd[MAX_COMMAND_SIZE];

	EthernetClient client = server->available();

	while(client.connected()) {
		if(firstContact) {
			respond(client, OK_RESPONSE, "HI!", RESPONSE_TERMINATOR);
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

			for(int i = TOTAL_COMMANDS -1;	i>0; i--) {
				if(strncasecmp(commandsString[i], incommingCmd, strlen(commandsString[i])) == 0){
					currentState = commands[i];
				}
			}

			switch(currentState) {
			case NOOP:
				respond(client, OK_RESPONSE, "HI!", RESPONSE_TERMINATOR);
				break;
			case TURN_ON:
				break;
			case TURN_OFF:
				break;
			case SHOW_NETWORK_INFO:
				response = OK_RESPONSE;

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
				response = OK_RESPONSE;
				strcpy(message, "BYE!");
				respond(client, response, message, RESPONSE_TERMINATOR);
				client.stop();
				break;
			default:
				break;
			}
		}
	}
}


