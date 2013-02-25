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
#include <CommandProtocolHandler.h>

#include <SensorManager.h>
#include <Sensor.h>
#include <DigitalPinSensor.h>

#define DEFAULT_SERVER_IP 192,168,1,10
#define DEFAULT_SERVER_PORT 2002
#define DEFAULT_UDP_PORT 2002
#define DEFAULT_LISTENING_PORT 8888
#define SENSORS_QTY 3

byte CommunicationManager::default_MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress CommunicationManager::default_IP(192,168,1,20);
IPAddress CommunicationManager::default_mask(255,255,255,0);
IPAddress CommunicationManager::default_gateway(192,168,1,10);
IPAddress CommunicationManager::default_server_IP = CommunicationManager::default_gateway;

DigitalPinSensor dSensors[SENSORS_QTY] = {
		DigitalPinSensor(5, HIGH),
		DigitalPinSensor(6, HIGH),
		DigitalPinSensor(7, HIGH)
};

InformationProtocolHandler iph(IPAddress(DEFAULT_SERVER_IP), DEFAULT_SERVER_PORT, DEFAULT_UDP_PORT);
//InformationProtocolHandler iph(CommunicationManager::default_server_IP, DEFAULT_SERVER_PORT, DEFAULT_UDP_PORT);
CommandProtocolHandler cph(DEFAULT_LISTENING_PORT);
SensorManager sm(dSensors, SENSORS_QTY);
CommunicationManager cm(iph, cph);

//int pins[SENSORS_QTY] = {
//		7
//};
//
//Sensor * s[SENSORS_QTY];

void setup() {
	Serial.begin(9600);
	Serial.println("Setup finished");
	cm.begin();
}

void loop() {
	cm.checkIncommingComm();

	sm.checkSensors();

	if (sm.sensorsChanged()) {
		cm.informData(sm);
		sm.setSensorsChanged(false);
	}

}

int main(void) {

	init();
	setup();

	Serial.println("Esto estaba en el setup, pero si no va aca se resetea el arduino");
	//	for(int i = 0; i < SENSORS_QTY; i++) {
	//		s[i] = &DigitalPinSensor(pins[i], HIGH);
	//	}
	Serial.println("Initializing sensor manager:");

	Serial.println("Initializing EthernetInformationProtocolHandler:");

//	Ethernet.begin(CommunicationManager::default_MAC, CommunicationManager::default_IP);
//	iph.begin();

	for(int i = 0; i < SENSORS_QTY; i++) {
		pinMode(dSensors[i].getPin(), INPUT);
	}


	Serial.println("Sensor pins: ");
	Serial.println(dSensors[0].getPin());
	Serial.println(dSensors[1].getPin());

	Serial.println("Arduino set");

	Serial.println("Entering loop...");

	do {
		loop();
	} while(true);

}

