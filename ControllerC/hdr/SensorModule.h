#ifndef SENSOR_MODULE_H_
#define SENSOR_MODULE_H_

#include <Ethernet.h>
#include "commons.h"

void initSensors(int * sensorsStatus, int sensorsQty);
bool checkSensors(int * sensors, int sensorsqty, int * sensorsStatus);

#endif /* SENSOR_MODULE_H_ */
