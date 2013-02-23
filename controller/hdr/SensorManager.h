/*
 * SensorManager.h
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#ifndef SENSORMANAGER_H_
#define SENSORMANAGER_H_

#include <commons.h>
#include <Sensor.h>
#include <DigitalPinSensor.h>

class SensorManager {
private:
	DigitalPinSensor * sensors;
	byte sensorsStatus[MAX_SENSORS];
	int sensorsQty;
	bool sensorsChange;
public:
	SensorManager(DigitalPinSensor * sensorArray, int sensorsQty);
	bool sensorsChanged();
	void setSensorsChanged(bool changed);
	void checkSensors();
	byte * getSensorsStatus();
	void reset();

	friend class InformationProtocolTranslator;
};


#endif /* SENSORMANAGER_H_ */
