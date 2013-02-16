/*
 * DigitalPinSensor.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#include <DigitalPinSensor.h>

DigitalPinSensor::DigitalPinSensor(byte pin, byte onValue) {
	this->pin = pin;
	this->onValue = onValue;
}

DigitalPinSensor::isOn() {
	return this->onVal == digitalRead(this->pin);
}
