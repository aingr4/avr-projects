/*
 * fast-blink.c
 *
 * Created: 2022-03-26 12:13:27 AM
 * Author : Andrew Ingram
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BITVALUE(x) (1 << x)

int main() {

	DDRB |= BITVALUE(PORTB5)

	while (true) {
		PORTB ^= BITVALUE(PORTB5)
		_delay_ms(20);
	}
}



