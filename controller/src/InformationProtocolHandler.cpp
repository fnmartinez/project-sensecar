/*
 * InformationProtocolHandler.cpp
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#include <InformationProtocolHandler.h>

InformationProtocolHandler::InformationProtocolHandler() {
	this->iPacket.sensors_qty = MAX_SENSORS;
	for(int i = 0; i < MAX_SENSORS; i++) {
		this->iPacket.sensors_status[i] = FREE;
	}

	this->rawPacket = (char*)&(this->iPacket);
	Serial.println("InformationProtocolHandler Set");
}

char * InformationProtocolHandler::getRawpacket() {
	return (char*)&(this->iPacket);
}

char InformationProtocolHandler::getSensorsQty(){
	return this->iPacket.sensors_qty;
}

char * InformationProtocolHandler::getSensorsStatus() {
	return this->iPacket.sensors_status;
}
