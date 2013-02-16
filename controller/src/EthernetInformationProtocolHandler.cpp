/*
 * EthernetInformationProtocolHandler.cpp
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */
#include <EthernetInformationProtocolHandler.h>

EthernetInformationProtocolHandler::EthernetInformationProtocolHandler(IPAddress serverIP, uint32_t serverPort, uint32_t udpPort) {
	this->serverIP = serverIP;
	this->serverPort = serverPort;
	this->udpPort = udpPort;
	this->client.begin(this->udpPort);
	Serial.println("UDP InformationProtocolHandler set.");
}

EthernetInformationProtocolHandler::sendPacket() {
	this->client.beginPacket(this->serverIP, this-serverPort);
	this->client.write(this->getRawpacket(), this->getSensorsQty());
	this->client.endPacket();
}
