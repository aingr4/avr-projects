/*
 * main.c
 *
 * Created: 2022-03-26 12:17:45 AM
 * Author : Andrew Ingram
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define BITVALUE(x) (1 << x)

#define PRESCALER 10 // 10 bits.... 1024
#define CLOCK_RATE 15998976 // 16 MHZ

// How many times the timer ticks in a second
#define COUNTER_VALUE (CLOCK_RATE >> PRESCALER)

// Timer1 compare interrupt service routine
ISR(TIMER1_COMPA_vect) {
	PORTB ^= BITVALUE(PORTB5);
}

int main() {

	DDRB |= BITVALUE(PORTB5); //B5 in output mode

	OCR1A = COUNTER_VALUE*3; // On compare, call interrupt

	TCCR1A = 0x00; // ??
	TCCR1B |= (1<<WGM12); // Clear Timer on Compare successfull mode
	TCCR1B |= (1<<CS10) | (1<<CS12); // Prescale to 1024

	
	TIMSK1 |= (1<<OCIE1A); // I want an interrupt

	sei(); // Global enable interrupts

	while(true) {
		// do some useful stuff here
	}
}

