/*
 * main.c
 *
 * Created: 2022-03-26 12:19:53 AM
 * Author : Andrew Ingram
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BITVALUE(x) (1 << x)

#define DELAY_S 200
#define DELAY_O 500

void morse(char letter);

int main() {

	DDRB |= BITVALUE(PORTB1);

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
			PORTB ^= BITVALUE(PORTB1);
			_delay_ms(DELAY_S);
		}
	} 
	else 
	{
		for (int i = 0; i < 3; i++) 
		{
			PORTB ^= BITVALUE(PORTB1);
			_delay_ms(DELAY_O);
		}
	}
}

