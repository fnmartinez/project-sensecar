/*
 * usart_ctrl_module.c
 *
 *  Created on: 24/11/2012
 *      Author: facundo
 */

#include "../../../headers/comm_module/ctrl_module/usart_ctrl_module.h"

void init_ctrl() {
	MY_UBRRH = (MY_UBRR >> 8);
	MY_UBRRL = (MY_UBRR);

	MY_UCSRB |= (1 << RXEN) | (1 << TXEN);
	MY_UCSRB |= (1 << RXCIE) | (1 << TXCIE);
	MY_UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void ctrl_generate_cmd() {

	/* TODO: hay que pensar el protocolo de control! D=
	 * Se me había ocurrido basarlo en el protocolo que hicimos para
	 * protos con Vicky y Kevin. Adjunto el informe de nuestro TP
	 * como para tener una idea. En mi particular opinión, es
	 * bastante robusto y fácil de parsear, excepto por los
	 * comandos particulares. Hay que ver cómo se hace eso.
	 *
	 * regarts!
	 */

	command_fetched.cmd = NO_COMMAND;
}
