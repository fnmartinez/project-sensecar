/*
 * leds.c
 *
 *  Created on: 13/09/2012
 *      Author: facundo
 */
#include "../../headers/utils/leds.h"

void change_leds() {
	LEDS_PORT = led_status;
}
void led_on(unsigned char led){
	led_status = led_status & (~led);
	change_leds();
}

void led_off(unsigned char led){
	led_status = led_status | led;
	change_leds();
}

void leds_on() {
	led_on(LED_ALL);
}

void leds_off() {
	led_off(LED_ALL);
}

void led_toggle(unsigned char led) {
	if( (led_status | led) != led_status )
	{
		led_off(led);
	}
	else
	{
		led_on(led);
	}
}

void leds_toggle() {
	led_status = ~led_status;
	change_leds();
}
