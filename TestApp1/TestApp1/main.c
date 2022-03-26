/*
 * TestApp1.c
 *
 * Created: 2022-03-23 3:22:24 PM
 * Author : Andrew Ingram
 */ 
#define OUTPUT_PIN PORTB4 // The run-indication LED: 0 OFF, 1 ON
#define F_CPU 1000000UL // Clock frequency

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << OUTPUT_PIN);
	
    while (1) 
    {
		PORTB ^= (1 << OUTPUT_PIN);
		_delay_ms(500);
    }
}

