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
	Serial.println("EthernetInformationProtocolHandler over UDP set.");
}

void EthernetInformationProtocolHandler::begin() {
	this->client.begin(this->udpPort);
	Serial.println("EthernetInformationProtocolHandler over UDP running.");
}

void EthernetInformationProtocolHandler::sendPacket() {
//	Serial.print("SENDING UDP PACKET to: ");
//	Serial.print(this->serverIP);
//	Serial.print(" at port: ");
//	Serial.print(this->serverPort);
//
//	Serial.print("IPACKET STATUS: ");
//	Serial.print(this->getSensorsStatus()[0]);
//	Serial.print(" SENSORS QUANTITY: ");
//	Serial.print(this->getSensorsQty());

	this->client.beginPacket(this->serverIP, this->serverPort);
	this->client.write(this->getRawpacket());
	this->client.endPacket();
}
