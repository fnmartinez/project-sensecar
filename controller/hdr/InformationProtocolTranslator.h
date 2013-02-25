/*
 * InformationProtocolTranslator.h
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#ifndef INFORMATIONPROTOCOLTRANSLATOR_H_
#define INFORMATIONPROTOCOLTRANSLATOR_H_

#include <InformationProtocolHandler.h>
#include <SensorManager.h>


class InformationProtocolTranslator {
public:
	static void translate(InformationProtocolHandler iph, SensorManager sm);
};

#endif /* INFORMATIONPROTOCOLTRANSLATOR_H_ */
