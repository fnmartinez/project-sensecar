/*
 * InformationProtocolHandler.cpp
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#include <InformationProtocolHandler.h>

InformationProtocolHandler::InformationProtocolHandler(IPAddress serverIP, uint32_t serverPort, uint32_t udpPort) {
	this->iPacket.sensors_qty = MAX_SENSORS;
	for(int i = 0; i < MAX_SENSORS; i++) {
		this->iPacket.sensors_status[i] = VACANT;
	}

//	this->rawPacket = (char*)&(this->iPacket);
	Serial.println("InformationProtocolHandler Set");
	this->serverIP = serverIP;
	this->serverPort = serverPort;
	this->udpPort = udpPort;
	Serial.println("EthernetInformationProtocolHandler over UDP set.");
}

byte * InformationProtocolHandler::getRawpacket() {
	this->rawPacket[0] = this->iPacket.sensors_qty + 48;
	for(int i = 0; i < this->iPacket.sensors_qty; i++) {
		this->rawPacket[i+1] = this->iPacket.sensors_status[i] + 48;
	}
	this->rawPacket[this->iPacket.sensors_qty + 2] = '\n';
	this->rawPacket[this->iPacket.sensors_qty + 3] = '\0';
	return this->rawPacket;
}

char InformationProtocolHandler::getSensorsQty(){
	return this->iPacket.sensors_qty;
}

char * InformationProtocolHandler::getSensorsStatus() {
	return this->iPacket.sensors_status;
}

void InformationProtocolHandler::begin() {
	Serial.println("EthernetInformationProtocolHandler over UDP running.");
	this->client.begin(this->udpPort);
}

void InformationProtocolHandler::sendPacket() {
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
