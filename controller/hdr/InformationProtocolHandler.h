/*
 * InformationProtocolHandler.h
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#ifndef INFORMATIONPROTOCOLHANDLER_H_
#define INFORMATIONPROTOCOLHANDLER_H_

#include <Arduino.h>
#include <IPAddress.h>
#include <Ethernet.h>
#include <commons.h>

typedef struct information_packet InfoPacket;
struct information_packet {
	char sensors_qty;
	char sensors_status[MAX_SENSORS];
};

class InformationProtocolHandler {
private:
	IPAddress serverIP;
	uint32_t serverPort;
	uint32_t udpPort;
	EthernetUDP client;
	InfoPacket iPacket;
	byte rawPacket[MAX_SENSORS + 2];
public:
	InformationProtocolHandler(IPAddress serverIP, uint32_t serverPort, uint32_t udpPort);
	char getSensorsQty();
	char * getSensorsStatus();
	byte * getRawpacket();
	virtual void begin();
	virtual void sendPacket();
	virtual ~InformationProtocolHandler() {};

	friend class InformationProtocolTranslator;
	friend class CommunicationManager;
};

#endif /* INFORMATIONPROTOCOLHANDLER_H_ */
