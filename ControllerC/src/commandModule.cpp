#include "CommandModule.h"
#include "commons.h"

extern bool sensorIsOn;

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
	Commands_t currentState = NOOP;
	char incommingCmd[MAX_COMMAND_SIZE];

	EthernetClient client = server->available();

	if(client) {
		Serial.println("NEW CLIENT");
//		while(client.connected() && client.available()) {
			int i = 0;
			do {
				incommingCmd[i] = client.read();
				i ++;
			} while (incommingCmd[i-1] != '\n');
			incommingCmd[i-1] = ' ';
			Serial.println("FINISHED READING");
			char * splittedCmd;
			splittedCmd = strtok(incommingCmd, " ");

			for(int i = 0; i < TOTAL_COMMANDS; i++) {
				Serial.println(commandsString[i]);
				Serial.println(splittedCmd);
				if(strcasecmp(commandsString[i], splittedCmd) == 0) {
					currentState = commands[i];
				}
			}


			Serial.println("------------------------------");
			Serial.print("currentState: ");
			Serial.println(currentState);
			if(currentState == NOOP) {
				Serial.println("ES NOOP");
			}
			Serial.println("------------------------------");

			switch(currentState) {
				case NOOP:
					respond(client, OK_RESPONSE, "NOOP!", RESPONSE_TERMINATOR);
					break;
				case TURN_ON:
					turnOn();
					respond(client, OK_RESPONSE, "TURN_ON!", RESPONSE_TERMINATOR);
					break;
				case TURN_OFF:
					turnOff();
					respond(client, OK_RESPONSE, "TURN_OFF!", RESPONSE_TERMINATOR);
					break;
				case SHOW_NETWORK_INFO:
					showNetworkInfo();
					respond(client, OK_RESPONSE, "SHOW_NETWORK_INFO!", RESPONSE_TERMINATOR);
					break;
				case SET_SERVER_IP:
					setServerIp();
					respond(client, OK_RESPONSE, "SET_SERVER_IP!", RESPONSE_TERMINATOR);
					break;
				case SET_SERVER_PORT:
					setServerPort();
					respond(client, OK_RESPONSE, "SET_SERVER_PORT!", RESPONSE_TERMINATOR);
					break;
				case SENSOR_ON:
					sensorOn();
					respond(client, OK_RESPONSE, "SENSOR_ON!", RESPONSE_TERMINATOR);
					break;
				case SENSOR_OFF:
					sensorOff();
					respond(client, OK_RESPONSE, "SENSOR_OFF!", RESPONSE_TERMINATOR);
					break;
				case GET_STATUS:
					getStatus();
					respond(client, OK_RESPONSE, "GET_STATUS!", RESPONSE_TERMINATOR);
					break;
				case INFORM_STATUS:
					informStatus();
					respond(client, OK_RESPONSE, "INFORM_STATUS!", RESPONSE_TERMINATOR);
					break;
				case EXIT:
					exit(client);
//					respond(client, OK_RESPONSE, "EXIT!", RESPONSE_TERMINATOR);
					break;
				default:
					break;
			}


	}
}


void turnOn() {
	sensorIsOn = true;
}

void turnOff() {
	sensorIsOn = false;
}

void showNetworkInfo() {

}

void setServerIp() {

}

void setServerPort() {

}

void sensorOn() {

}

void sensorOff() {

}

void getStatus() {

}

void informStatus() {

}

void exit() {
//	respond(client, OK_RESPONSE, "BYEEE!", RESPONSE_TERMINATOR);
//	client.stop();
}
