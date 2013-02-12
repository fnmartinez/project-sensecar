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

#define MAX_SENSORS 256
#define SENSORS_QTY 1

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

}

int main(void) {

	init();
	setup();

	do {
		loop();
	} while(true);

}
