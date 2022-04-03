/*
 * main.c
 *
 * Created: 2022-03-26 12:13:27 AM
 * Author : Andrew Ingram
 */ 

#include "include/common.h" // Include first
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int main() {

	DDRB |= BITVALUE(RUN_LED_PIN);

	while (true) {
		PORTB ^= BITVALUE(RUN_LED_PIN);
		_delay_ms(50);
	}
}

