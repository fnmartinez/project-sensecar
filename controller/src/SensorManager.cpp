/*
 * SensorManager.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */
#include <commons.h>
#include <SensorManager.h>

SensorManager::SensorManager(Sensor * sensorArray, int sensorsQty) {
	this->sensors = sensorArray;
	this->sensorsQty = sensorsQty;
	this->checkSensors();
}

bool SensorManager::sensorsChanged() {
	return this->sensorsChange;
}

void SensorManager::checkSensors() {


	for(int i = 0; i < MAX_SENSORS; i++) {
		bool status = this->sensors[i]->isOn();

		if(this->sensorsStatus[i] != OFF && (
				(status == true && this->sensorsStatus[i] == VACANT) ||
				(status == false && this->sensorsStatus[i] == OCCUPYED))) {
			this->sensorsChange = true;
		}

		this->sensorsStatus[i] = status;
	}
}

byte * SensorManager::getSensorsStatus() {
	return this->sensorsStatus;
}

void SensorManager::reset() {
	this->sensorsChange = false;
}
