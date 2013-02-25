/*
 * Communicator.h
 *
 *  Created on: 11/02/2013
 *      Author: facundo
 */

#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <IPAddress.h>
#include <CommandProtocolHandler.h>
#include <InformationProtocolHandler.h>
#include <InformationProtocolTranslator.h>
#include "information_protocol.h"

#define MAC_OCTETS 6


class CommunicationManager {
private:
	byte mac[MAC_OCTETS];
	IPAddress myIP;
	unsigned int cmdServerPort;
	CommandProtocolHandler * cmdPHandler;
	InformationProtocolHandler * infoPHandler;
public:
	static byte default_MAC[MAC_OCTETS];
	static IPAddress default_IP;
	static IPAddress default_mask;
	static IPAddress default_gateway;
	static IPAddress default_server_IP;
	CommunicationManager(InformationProtocolHandler infoPHandler, CommandProtocolHandler cmdPHandler);
	void begin();
	void checkIncommingComm();
	void informData(SensorManager sm);
	void changeIP(IPAddress ip);
	void changePort(uint32_t port);
	void changeServerIP(IPAddress ip);
	void changeServerPort(uint32_t port);
};


//byte CommunicationManager::default_MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress CommunicationManager::default_IP(192,168,1,177);
//IPAddress CommunicationManager::default_mask(255,255,255,0);
//IPAddress CommunicationManager::default_gateway(192,168,1,1);
//IPAddress CommunicationManager::default_server_IP = CommunicationManager::default_gateway;
#endif /* COMMUNICATOR_H_ */
