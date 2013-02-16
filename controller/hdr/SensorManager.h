/*
 * SensorManager.h
 *
 *  Created on: 12/02/2013
 *      Author: facundo
 */

#ifndef SENSORMANAGER_H_
#define SENSORMANAGER_H_

#include <Sensor.h>
#define MAX_SENSOR_ARRAY 256


class SensorManager {
private:
	Sensor sensors[MAX_SENSOR_ARRAY];
	byte sensorsStatus[MAX_SENSOR_ARRAY];
	bool sensorsChange;
public:
	void SensorManager(Sensor sensorArray[MAX_SENSOR_ARRAY]);
	bool sensorsChanged();
	void checkSensors();
	byte * getSensorsStatus();
	void reset();
};


#endif /* SENSORMANAGER_H_ */
