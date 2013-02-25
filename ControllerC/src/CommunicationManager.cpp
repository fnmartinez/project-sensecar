///*
// * CommunicationManager.cpp
// *
// *  Created on: 16/02/2013
// *      Author: facundo
// */
//
//#include <CommunicationManager.h>
//
//
//CommunicationManager::CommunicationManager(InformationProtocolHandler &infoPHandler) {
//	this->infoPHandler = &infoPHandler;
//	Ethernet.begin(default_MAC, default_IP);
//	this->infoPHandler->begin();
//	Serial.println("Communication Module up and running.");
//}
//
//void CommunicationManager::informData(SensorManager * sm) {
//	InformationProtocolTranslator::translate(*(this->infoPHandler), sm);
//	this->infoPHandler->sendPacket();
//}
//
//void CommunicationManager::changeIP(IPAddress ip) {
//
//}
//
//void CommunicationManager::changePort(uint32_t port) {
//
//}
//
//void CommunicationManager::changeServerIP(IPAddress ip) {
//
//}
//
//void CommunicationManager::changeServerPort(uint32_t port) {
//
//}
//
//void CommunicationManager::checkIncommingComm() {
//
//}
