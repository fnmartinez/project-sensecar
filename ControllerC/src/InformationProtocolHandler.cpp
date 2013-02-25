///*
// * InformationProtocolHandler.cpp
// *
// *  Created on: 12/02/2013
// *      Author: facundo
// */
//
//#include <InformationProtocolHandler.h>
//
//InformationProtocolHandler::InformationProtocolHandler() {
//	this->iPacket.sensors_qty = MAX_SENSORS;
//	for(int i = 0; i < MAX_SENSORS; i++) {
//		this->iPacket.sensors_status[i] = FREE;
//	}
//
////	this->rawPacket = (char*)&(this->iPacket);
//	Serial.println("InformationProtocolHandler Set");
//}
//
//byte * InformationProtocolHandler::getRawpacket() {
//	this->rawPacket[0] = this->iPacket.sensors_qty + 48;
//	for(int i = 0; i < this->iPacket.sensors_qty; i++) {
//		this->rawPacket[i+1] = this->iPacket.sensors_status[i] + 48;
//	}
//	this->rawPacket[this->iPacket.sensors_qty + 2] = '\n';
//	this->rawPacket[this->iPacket.sensors_qty + 3] = '\0';
//	return this->rawPacket;
//}
//
//char InformationProtocolHandler::getSensorsQty(){
//	return this->iPacket.sensors_qty;
//}
//
//char * InformationProtocolHandler::getSensorsStatus() {
//	return this->iPacket.sensors_status;
//}
