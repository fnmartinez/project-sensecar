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
	Serial.println("EthernetInformationProtocolHandler over UDP running.");
	this->client.begin(this->udpPort);
}

void EthernetInformationProtocolHandler::sendPacket() {
//	Serial.print("SENDING UDP PACKET to: ");
//	Serial.print(this->serverIP);
//	Serial.print(" at port: ");
//	Serial.print(this->serverPort);
//
	Serial.print(" SENSORS QUANTITY: ");
	Serial.print(this->getRawpacket()[0], DEC);
	Serial.print("\t RAWPACKET STATUS[1]: ");
	Serial.print(this->getRawpacket()[1], DEC);
	Serial.print("\t RAWPACKET STATUS[2]: ");
	Serial.print(this->getRawpacket()[2], DEC);
	Serial.print("\t RAWPACKET STATUS[3]: ");
	Serial.println(this->getRawpacket()[3], DEC);

	this->client.beginPacket(this->serverIP, this->serverPort);
	this->client.write((char*)this->getRawpacket());
	this->client.endPacket();
}
