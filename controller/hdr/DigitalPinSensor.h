/*
 * DigitalPinSensor.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#ifndef DIGITALPINSENSOR_CPP_
#define DIGITALPINSENSOR_CPP_

#include <Sensor.h>


class DigitalPinSensor : public Sensor {
private:
	byte pin;
	byte onValue;
public:
	void DigitalPinSensor(byte pin, byte onValue);
	virtual bool isOn();
};

#endif /* DIGITALPINSENSOR_CPP_ */
