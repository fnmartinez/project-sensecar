#include "InfoModule.h"

EthernetUDP udpClient;

void beginUDP(int port) {
	udpClient.begin(port);
}

void sendPacket(IPAddress serverName, int serverPort, char* packet) {
	udpClient.beginPacket(serverName, serverPort);
	udpClient.write(packet);
	udpClient.endPacket();
}

void preparePacketToSend(char * buf, int * sensorStatus, int quantity) {
	buf[0] = (char) (quantity + 48);

	for (int i = 0; i < quantity; i++) {
		buf[i+1] = (char) (sensorStatus[i] + 48);
	}
	buf[quantity + 1] = '\0';
	buf[quantity + 2] = '\n';
}
