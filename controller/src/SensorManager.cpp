/*
 * SensorManager.cpp
 *
 *  Created on: 16/02/2013
 *      Author: facundo
 */

#include  <SensorManager.h>

SensorManager::SensorManager(Sensor sensorArray[MAX_SENSOR_ARRAY]) {
	this->sensors = sensorArray;
	this->checkSensors();
}

SensorManager::sensorsChanged() {
	return this->sensorsChange;
}

SensorManager::checkSensors() {


	for(int i = 0; i < MAX_SENSOR_ARRAY; i++) {
		byte status = this->sensors[i].getStatus();

		if(status != this->sensorsStatus[i]) {
			this->sensorsChange = true;
		}

		this->sensorsStatus[i] = status;
	}
}

SensorManager::getSensorsStatus() {
	return this->sensorsStatus;
}

SensorManager::reset() {
	this->sensorsChange = false;
}
