/*
 * Sensor.h
 *
 *  Created on: 14/02/2013
 *      Author: facundo
 */

#ifndef SENSOR_H_
#define SENSOR_H_


class Sensor {
public:
	virtual byte isOn() =0;
	virtual ~Sensor();
};


#endif /* SENSOR_H_ */
