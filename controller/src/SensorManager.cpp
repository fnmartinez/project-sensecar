/*
 * SensorManager.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */
#include <commons.h>
#include <SensorManager.h>
#include <Ethernet.h>

SensorManager::SensorManager(DigitalPinSensor * sensorArray, int sensorsQty) {
	this->sensors = sensorArray;
	this->sensorsQty = sensorsQty;
	this->sensorsChange = false;
	for(int i = 0; i < sensorsQty; i++) {
		this->sensorsStatus[i] = VACANT;
	}
//	this->checkSensors();
}

bool SensorManager::sensorsChanged() {
	return this->sensorsChange;
}

void SensorManager::setSensorsChanged(bool changed) {
	this->sensorsChange = changed;
}

void SensorManager::checkSensors() {
//Serial.println("Checking sensors:");

//	for(int i = 0; i < MAX_SENSORS; i++) {
//		bool status = VACANT;
//		this->sensorsChange = true;
//		this->sensorsStatus[i] = VACANT;
//	}

	for(int i = 0; i < sensorsQty; i++) {
		bool pinStatus = this->sensors[i].isOn();
//		Serial.println("Status: " + pinStatus);
//
//		Serial.print("Before: SensorStatus[");
//		Serial.print(i);
//		Serial.print("] = ");
//		Serial.println(this->sensorsStatus[i]);

		if(this->sensorsStatus[i] != OFF && (
				(pinStatus == true && this->sensorsStatus[i] == VACANT) ||
				(pinStatus == false && this->sensorsStatus[i] == OCCUPYED))) {
			this->sensorsChange = true;
		}

//		Serial.print("After: SensorStatus[");
//		Serial.print(i);
//		Serial.print("] = ");
//		Serial.println(pinStatus);

		this->sensorsStatus[i] = pinStatus;

	}

}

byte * SensorManager::getSensorsStatus() {
	return this->sensorsStatus;
}

void SensorManager::reset() {
	this->sensorsChange = false;
}
