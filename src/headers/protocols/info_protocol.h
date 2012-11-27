/*
 * info_protocol.h
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#ifndef INFO_PROTOCOL_H_
#define INFO_PROTOCOL_H_
#include "../utils/commons.h"

typedef enum {
	OCCUPIED,
	VACANT
} spot_state_t;

typedef uint32_t spot_id_t;

typedef struct _individual_info_t individual_info_t;

struct _individual_info_t {
	spot_id_t spot;
	spot_state_t state;
};

typedef individual_info_t info_packet_t[SENSORS_QTY];

info_packet_t packet;

typedef uint8_t raw_info_packet_t[SENSORS_QTY*sizeof(individual_info_t)];

raw_info_packet_t raw_packet;

void codify_info_packet();


#endif /* INFO_PROTOCOL_H_ */
