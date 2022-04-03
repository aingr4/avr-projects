/*
 * common.h
 *
 * Created: 2022-03-26 12:42:35 PM
 *  Author: Andrew Ingram
 */ 


#ifndef COMMON_H
#define COMMON_H

// DEFINES
#define RUN_LED_PIN PORTB5 // The run-indication LED: 0 OFF, 1 ON
#define F_CPU 10000000UL // Clock frequency

// MACROS
#define BITVALUE(x) (1 << x)


#endif /* COMMON_H */