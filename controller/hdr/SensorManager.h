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


class SensorManager {
private:
	Sensor ** sensors;
	byte sensorsStatus[MAX_SENSORS];
	int sensorsQty;
	bool sensorsChange;
public:
	SensorManager(Sensor ** sensorArray, int sensorsQty);
	bool sensorsChanged();
	void checkSensors();
	byte * getSensorsStatus();
	void reset();

	friend class InformationProtocolTranslator;
};


#endif /* SENSORMANAGER_H_ */
