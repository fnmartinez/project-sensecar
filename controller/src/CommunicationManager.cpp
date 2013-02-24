/*
 * CommunicationManager.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#include <CommunicationManager.h>


CommunicationManager::CommunicationManager(InformationProtocolHandler * infoPHandler, CommandProtocolHandler * cmdPHandler) {
	this->infoPHandler = infoPHandler;
	this->cmdPHandler = cmdPHandler;
	Serial.print("infoPHandler:");
	Serial.println((int)this->infoPHandler, HEX);
	Ethernet.begin(default_MAC, default_IP);
	Serial.println("Communication Module up and running.");
	delay(2000);
	this->infoPHandler->begin();
	this->cmdPHandler->begin();
}

void CommunicationManager::informData(SensorManager * sm) {
	InformationProtocolTranslator::translate(*(this->infoPHandler), sm);
	this->infoPHandler->sendPacket();
}

void CommunicationManager::changeIP(IPAddress ip) {

}

void CommunicationManager::changePort(uint32_t port) {

}

void CommunicationManager::changeServerIP(IPAddress ip) {

}

void CommunicationManager::changeServerPort(uint32_t port) {

}

void CommunicationManager::checkIncommingComm() {

}
