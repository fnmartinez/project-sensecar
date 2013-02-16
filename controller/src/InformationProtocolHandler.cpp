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

	this->rawPacket = &this->iPacket;
}

InformationProtocolHandler::preparePacket(int sensorsQty, byte * sensorsStatus) {
	if(sensorsQty > MAX_SENSORS){
		Serial.println("Sensors quantity exceeds the maximum sensor quantity allowed. No packet is prepared.");
		return;
	}

	this->iPacket.sensors_qty = sensorsQty;
	memcpy(this->iPacket.sensors_status, sensorsStatus, this->iPacket.sensors_qty);
}

InformationProtocolHandler::getRawpacket() {
	return this->rawPacket;
}

InformationProtocolHandler::getSensorsQty(){
	return this->iPacket.sensors_qty;
}

InformationProtocolHandler::getSensorsStatus() {
	return this->iPacket.sensors_status;
}
