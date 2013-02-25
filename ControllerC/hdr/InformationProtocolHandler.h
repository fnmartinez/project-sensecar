///*
// * InformationProtocolHandler.h
// *
// *  Created on: 12/02/2013
// *      Author: facundo
// */
//
//#ifndef INFORMATIONPROTOCOLHANDLER_H_
//#define INFORMATIONPROTOCOLHANDLER_H_
//
//#include <Arduino.h>
//#include <commons.h>
//
//#define FREE 0
//#define OCCUPIED 1
//#define OFF 2
//
//typedef struct information_packet InfoPacket;
//struct information_packet {
//	char sensors_qty;
//	char sensors_status[MAX_SENSORS];
//};
//
//class InformationProtocolHandler {
//private:
//	InfoPacket iPacket;
//	byte rawPacket[MAX_SENSORS + 2];
//public:
//	InformationProtocolHandler();
//	char getSensorsQty();
//	char * getSensorsStatus();
//	byte * getRawpacket();
//	virtual void begin()=0;
//	virtual void sendPacket() =0;
//	virtual ~InformationProtocolHandler() {};
//
//	friend class InformationProtocolTranslator;
//	friend class CommunicationManager;
//};
//
//#endif /* INFORMATIONPROTOCOLHANDLER_H_ */
