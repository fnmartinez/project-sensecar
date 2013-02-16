/*
 * InformationProtocolHandler.h
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#ifndef INFORMATIONPROTOCOLHANDLER_H_
#define INFORMATIONPROTOCOLHANDLER_H_

#include <Arduino.h>

#define MAX_SENSORS 256
#define FREE 0
#define OCCUPIED 1
#define OFF 2

typedef struct information_packet InfoPacket;
struct information_packet {
	byte sensors_qty;
	byte sensors_status[MAX_SENSORS];
};

class InformationProtocolHandler {
private:
	InfoPacket iPacket;
	byte* rawPacket;
public:
	void InformationProtocolHandler();
	//TODO: put getters definitions in the .cpp
	byte getSensorsQty() { return this->iPacket.sensors_qty;}
	byte * getSensorsStatus() { return this->iPacket.sensors_status;}
	byte * getRawpacket();
	void preparePacket(int sensorsQty, byte * sensorsStatus);
	virtual void sendPacket() =0;
	virtual ~InformationProtocolHandler() {};
};

#endif /* INFORMATIONPROTOCOLHANDLER_H_ */
