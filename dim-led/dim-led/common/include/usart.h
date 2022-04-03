/*
 * usart.h
 *
 * Created: 2022-04-02 3:21:39 AM
 *  Author: Andrew Ingram
 */ 


#ifndef USART_H
#define USART_H

#include "common.h"

// DEFINES
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)
#define TX_BUFFER_SIZE 1024


// STRUCTS
typedef struct {
	char    buf[TX_BUFFER_SIZE]; // TX_BUFFER_SIZE bytes
	uint8_t readPos;
	uint8_t writePos;
} UsartSerialBuffer;


// FUNCTIONS
void usartSerialWrite(char *c);
void usartSerialRead(void);
void usartInit(void);

#endif /* USART_H */