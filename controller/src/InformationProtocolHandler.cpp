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

	this->rawPacket = (byte*)&(this->iPacket);
	Serial.println("InformationProtocolHandler Set");
}

byte * InformationProtocolHandler::getRawpacket() {
	return this->rawPacket;
}

byte InformationProtocolHandler::getSensorsQty(){
	return this->iPacket.sensors_qty;
}

byte * InformationProtocolHandler::getSensorsStatus() {
	return this->iPacket.sensors_status;
}
