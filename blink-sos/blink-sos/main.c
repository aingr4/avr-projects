/*
 * main.c
 *
 * Created: 2022-03-26 12:19:53 AM
 * Author : Andrew Ingram
 */ 

#include "include/common.h" // Must be included first
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>



#define DELAY_S 300
#define DELAY_O 800

void morse(char letter);

int main() {

	DDRB |= BITVALUE(RUN_LED_PIN);

	while (true) {
		morse('s');
		morse('o');
		morse('s');
		_delay_ms(1000);
	}
}

void morse(char letter) {
	
	if (letter == 's') 
	{
		for (int i = 0; i < 3; i++) 
		{
			PORTB |= BITVALUE(RUN_LED_PIN);
			_delay_ms(DELAY_S);
			PORTB &= ~BITVALUE(RUN_LED_PIN);
			_delay_ms(DELAY_S);
		}
	} 
	else 
	{
		for (int i = 0; i < 3; i++) 
		{
			PORTB ^= BITVALUE(RUN_LED_PIN);
			_delay_ms(DELAY_O);
			PORTB &= ~BITVALUE(RUN_LED_PIN);
			_delay_ms(DELAY_S);
		}
	}
}

