/*
 * EthernetCommandProtocolHandler.h
 *
 *  Created on: 23/02/2013
 *      Author: facundo
 */

#ifndef ETHERNETCOMMANDPROTOCOLHANDLER_H_
#define ETHERNETCOMMANDPROTOCOLHANDLER_H_

#include <Ethernet.h>
#include <EthernetServer.h>
#include <CommandProtocolHandler.h>

class EthernetCommandProtocolHandler: public CommandProtocolHandler {
private:
	int port;
	EthernetServer * server;
	void respond(EthernetClient c, char * response, char * msg, char * terminator);
public:
	EthernetCommandProtocolHandler(int port);
	virtual void checkForClients();
	virtual void begin();
	virtual ~EthernetCommandProtocolHandler();
};


#endif /* ETHERNETCOMMANDPROTOCOLHANDLER_H_ */
