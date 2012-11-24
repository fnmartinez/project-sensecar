/*
 * usart.h
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "commons.h"

#define MY_UBRRH UBRRH
#define MY_UBRRL UBRRL
#define FOSC 3686400
#define DEF_BAUD 9600
#define MY_UBRR (FOSC/16/DEF_BAUD - 1)
#define MY_UDR UDR
#define MY_UCSRA UCSRA
#define MY_UCSRB UCSRB
#define MY_UCSRC UCSRC

void init_usart();

#endif /* USART_H_ */
