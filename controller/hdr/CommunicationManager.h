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
#include "information_protocol.h"

#define MAC_OCTETS 6

byte default_MAC[MAC_OCTETS] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress default_IP(192,168,1,177);
IPAddress default_mask(255,255,255,0);
IPAddress default_gateway(192,168,1,1);
IPAddress default_server_IP = default_gateway;

class CommunicationManager {
private:
	byte mac[MAC_OCTETS];
	IPAddress cmdServerAddress;
	IPAddress infoServerAddress;
	unsigned int infoServerPort;
	unsigned int cmdServerPort;
	EthernetUDP infoCommunicator;
	EthernetServer cmdServer;
public:
	void CommunicationManager();
	void begin();
	void checkComm();
	void informData();
	void changeIP(IPAddress ip);
	void changePort(uint32_t port);
	void changeServerIP(IPAddress ip);
	void changeServerPort(uint32_t port);
	void sendInfoPacket(infoPacket info_packet);
};

#endif /* COMMUNICATOR_H_ */
