#include "SensorModule.h"

extern bool sensorIsOn;

void initSensors(int * sensorsStatus, int sensorsQty) {
	for(int i = 0; i < sensorsQty; i++) {
		sensorsStatus[i] = VACANT;
	}
}

bool checkSensors(int * sensors, int sensorsqty, int * sensorsStatus) {
//	Serial.print("CHECKING SENSORS for quantity: ");
//	Serial.println(sensorsqty, DEC);
	if(sensorIsOn) {
		bool sensorsChanged = false;

		for(int i = 0; i < sensorsqty; i++) {
	//		Serial.print("Sensor status: ");
	//		Serial.println(sensorsStatus[i], DEC);
	//		Serial.print("Sensor pin: ");
	//		Serial.println(sensors[i], DEC);
			bool pinStatus = digitalRead(sensors[i]);
	//		Serial.println("ASDFASDFASDFASDF");
	//		Serial.println("Status: " + pinStatus);
	//
	//		Serial.print("Before: SensorStatus[");
	//		Serial.print(i);
	//		Serial.print("] = ");
	//		Serial.println(this->sensorsStatus[i]);

			if(sensorsStatus[i] != OFF && (
					(pinStatus == true && sensorsStatus[i] == VACANT) ||
					(pinStatus == false && sensorsStatus[i] == OCCUPYED))) {
				sensorsChanged = true;

				Serial.println("SENSORS CHANGED!!!! adasdsad");
			}

	//		Serial.print("After: SensorStatus[");
	//		Serial.print(i);
	//		Serial.print("] = ");
	//		Serial.println(pinStatus);

			sensorsStatus[i] = pinStatus;
		}

		return sensorsChanged;
	} else {
		return false;
	}

}

