/*
 * InformationProtocolTranslator.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#include <InformationProtocolTranslator.h>

void InformationProtocolTranslator::translate(InformationProtocolHandler &iph, SensorManager * sm) {

	iph.iPacket.sensors_qty = sm->sensorsQty;

	for (int i = 0; i < sm->sensorsQty; i++) {
		iph.iPacket.sensors_status[i] = sm->sensorsStatus[i];
	}

}


