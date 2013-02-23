/*
 * DigitalPinSensor.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */
#include <Arduino.h>
#include <DigitalPinSensor.h>

DigitalPinSensor::DigitalPinSensor(int pin, byte onValue) {
	this->pin = pin;
	this->onValue = onValue;
//	pinMode(this->pin, INPUT);
}

bool DigitalPinSensor::isOn() {
	return this->onValue == digitalRead(this->pin);
}

int DigitalPinSensor::getPin() {
	return this->pin;
}
