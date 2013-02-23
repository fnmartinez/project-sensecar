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
	int pin;
	byte onValue;
public:
	DigitalPinSensor(int pin, byte onValue);
	virtual bool isOn();
	virtual int getPin();
};

#endif /* DIGITALPINSENSOR_CPP_ */
