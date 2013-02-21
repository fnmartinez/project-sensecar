/*
 * main.cpp
 *
 *  Created on: 10/02/2013
 *      Author: facundo
 */
//#include <main.h>
#include <Arduino.h>
#include <IPAddress.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>

/*
#define MAX_SENSORS 256
#define SENSORS_QTY 3

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);

IPAddress server_ip(192,168,1,1);
uint32_t server_port = 8888;

uint32_t udp_port = 8888;
EthernetUDP udp;

EthernetServer cmd_server(8080);

typedef struct info_packet info_packet_t;
struct info_packet {
	byte sensor_qty;
	byte sensors[MAX_SENSORS];
};

byte sensors_pin[SENSORS_QTY] = {};
info_packet_t infop;

bool new_data = false;

void check_incomming_comm() {

	Serial.println("Checking server");
	EthernetClient c = cmd_server.available();

	if(c) {
		Serial.println("New client!");
		while(c.connected()) {
			c.println("+OK bye");
			c.stop();
			Serial.println("Client dispatched");
		}
	}
}

void check_sensors() {
	Serial.println("Chequeando sensores");
	for (int i = 0; i < SENSORS_QTY; ++i) {
		int sensor = digitalRead(sensors_pin[i]);
		if(sensor != infop.sensors[i]) {
			Serial.println("Nueva info disponible en sensor " + i);
			new_data = true;
		}
		infop.sensors[i] = sensor;
	}
}

void set_pins() {
	for (int i = 0; i < SENSORS_QTY; i++) {
		pinMode(sensors_pin[i], INPUT);
	}
}

void inform_data() {
	udp.beginPacket(server_ip, server_port);
	udp.write(((uint8_t *)(&infop)), SENSORS_QTY + sizeof(byte));
	udp.endPacket();
	Serial.println("Data sent");
}

void setup() {
	Serial.begin(9600);

	Ethernet.begin(mac, ip);
	cmd_server.begin();

	//UDP Server
	udp.begin(udp_port);
	set_pins();

	Serial.println("Arduino set");
}

void loop() {

	check_incomming_comm();
	check_sensors();

	if(new_data) {
		inform_data();
		new_data = false;
	}
	delay(1000);

}*/

#include <CommunicationManager.h>
#include <InformationProtocolHandler.h>
#include <EthernetInformationProtocolHandler.h>

#include <SensorManager.h>
#include <Sensor.h>
#include <DigitalPinSensor.h>

#define DEFAULT_SERVER_IP 192,168,1,1
#define DEFAULT_SERVER_PORT 2002
#define DEFAULT_UDP_PORT 2002
#define SENSORS_QTY 1

CommunicationManager * cm;
SensorManager * sm;


//int pins[SENSORS_QTY] = {
//		7
//};
//
//Sensor * s[SENSORS_QTY];

byte CommunicationManager::default_MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress CommunicationManager::default_IP(192,168,1,177);
IPAddress CommunicationManager::default_mask(255,255,255,0);
IPAddress CommunicationManager::default_gateway(192,168,1,1);
IPAddress CommunicationManager::default_server_IP = CommunicationManager::default_gateway;

DigitalPinSensor dSensors[SENSORS_QTY] = {
		DigitalPinSensor(7, HIGH)
};
void setup() {
	Serial.begin(9600);

	for(int i = 0; i < SENSORS_QTY; i++) {
//		s[i] = &DigitalPinSensor(pins[i], HIGH);
	}
	Serial.println("2Puto!");

	sm = &SensorManager(dSensors, SENSORS_QTY);

	Serial.println("3Puto!");
	EthernetInformationProtocolHandler iph(IPAddress(DEFAULT_SERVER_IP), DEFAULT_SERVER_PORT, DEFAULT_UDP_PORT);

	cm = &CommunicationManager(iph);

	Serial.println("Arduino set");
}

void loop() {

	cm->checkIncommingComm();

	sm->checkSensors();

	if (sm->sensorsChanged()) {
		cm->informData(sm);
	}

}

int main(void) {

	init();
	setup();

	do {
		loop();
	} while(true);

}
