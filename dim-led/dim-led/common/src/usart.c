/*
 * usart.c
 *
 * Created: 2022-04-02 3:27:58 AM
 *  Author: Andrew Ingram
 */

#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

UsartSerialBuffer serialBuffer;

ISR(USART_TX_vect)
{
	usartSerialRead();
}

void usartInit(void)
{
	serialBuffer.readPos = 0;
	serialBuffer.writePos = 0;
	
	UBRR0H = (BRC >> 8);
	UBRR0L =  BRC;
	
	UCSR0B = (1 << TXEN0)  | (1 << TXCIE0); // Enable TX and TX Interrupt
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit character size
	
	sei();
}

void usartSerialWrite(char *c)
{
	while (*c)
	{
		serialBuffer.buf[serialBuffer.writePos++] = *c++;
		
		if (serialBuffer.writePos == TX_BUFFER_SIZE)
		{
			serialBuffer.writePos = 0;
		}
	}
	
	if (UCSR0A & (1 << UDRE0))
	{
		UDR0 = 0;
	}
}

void usartSerialRead(void)
{
	if (serialBuffer.readPos != serialBuffer.writePos)
	{
		UDR0 = serialBuffer.buf[serialBuffer.readPos++];
		
		if (serialBuffer.readPos == TX_BUFFER_SIZE)
		{
			serialBuffer.readPos = 0;
		}
	}
}
