#include <CommandModule.h>

EthernetServer * server;

void beginTCP(int port) {
	server = new EthernetServer(port);
}

void verifyIncomingCommand() {
	EthernetClient client = server->available();
	if (client) {
	    Serial.println("new client");
//	    // an http request ends with a blank line
//	    while (client.connected()) {
//	      if (client.available()) {
//	        char c = client.read();
//	        Serial.write(c);
//	        // if you've gotten to the end of the line (received a newline
//	        // character) and the line is blank, the http request has ended,
//	        // so you can send a reply
//	        if (c == '\n' && currentLineIsBlank) {
//	          // send a standard http response header
//	          client.println("HTTP/1.1 200 OK");
//	          client.println("Content-Type: text/html");
//	          client.println("Connnection: close");
//	          client.println();
//	          client.println("<!DOCTYPE HTML>");
//	          client.println("<html>");
//	                    // add a meta refresh tag, so the browser pulls again every 5 seconds:
//	          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
//	          // output the value of each analog input pin
//	          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
//	            int sensorReading = analogRead(analogChannel);
//	            client.print("analog input ");
//	            client.print(analogChannel);
//	            client.print(" is ");
//	            client.print(sensorReading);
//	            client.println("<br />");
//	          }
//	          client.println("</html>");
//	          break;
//	        }
//	        if (c == '\n') {
//	          // you're starting a new line
//	          currentLineIsBlank = true;
//	        }
//	        else if (c != '\r') {
//	          // you've gotten a character on the current line
//	          currentLineIsBlank = false;
//	        }
//	      }
	    // give the web browser time to receive the data
	    delay(1);
	    // close the connection:
	    client.stop();
	    }
//	    Serial.println("client disonnected");
}


void checkForClients() {
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
