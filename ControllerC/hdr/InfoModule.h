#ifndef INFO_MODULE_H_
#define INFO_MODULE_H_

#include <SPI.h>
#include <Ethernet.h>
#include "commons.h"

#define UDP_BUFFER_SIZE 256

void beginUDP(int port);
void sendPacket(IPAddress serverName, int serverPort, char* packet);
void preparePacketToSend(char * buf, int * sensorStatus, int quantity);

#endif /* INFO_MODULE_H_ */
