/*
 * information_protocol.h
 *
 *  Created on: 11/02/2013
 *      Author: facundo
 */

#ifndef INFORMATION_PROTOCOL_H_
#define INFORMATION_PROTOCOL_H_

#define MAX_SENSORS 256

typedef struct info_packet info_packet_t;
typedef info_packet_t * infoPacket;

struct info_packet {
	char sensors_qty;
	char sensors[MAX_SENSORS];
};


#endif /* INFORMATION_PROTOCOL_H_ */
