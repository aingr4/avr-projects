/*
 * common.h
 *
 * Created: 2022-03-26 12:42:35 PM
 *  Author: Andrew Ingram
 */ 
#ifndef COMMON_H
#define COMMON_H


// INCLUDES
#include <stdint.h>
#include <stdbool.h>


// DEFINES
#define RUN_LED_PIN DBP13 // The run-indication LED: 0 OFF, 1 ON
#define RUN_LED_BLINK_DELAY 100

#define F_CPU 16000000 // Clock frequency


// MACROS
#define BITVALUE(x) (1 << x)


// ENUMS
typedef enum {
	PinMode_INPUT = 0,
	PinMode_OUTPUT = 1
} PinMode;

typedef enum {
	PinValue_LOW = 0,
	PinValue_HIGH = 1	
} PinValue;

typedef enum {
	// Digital Board Pins
	DBP0 = 0,
	DBP1,
	DBP2,
	DBP3,
	DBP4,
	DBP5,
	DBP6,
	DBP7,
	DBP8,
	DBP9,
	DBP10,
	DBP11,
	DBP12,
	DBP13,
	// Analog Board Pins
	ABP0 = 14,
	ABP1,
	ABP2,
	ABP3,
	ABP4,
	ABP5
} BoardPin;

typedef enum {
	CoreStatus_OK,
	CoreStatus_ERROR
} CoreStatus;

// FUNCTIONS
// Writing
CoreStatus ioAnalogWrite(BoardPin bpin, uint16_t cycle);

// Board Pins
bool       isDigitalBoardPin(uint16_t bpin);
bool       isAnalogBoardPin(uint16_t bpin);
bool       ioIsBoardPin(uint16_t bpin);
uint16_t   ioBoardPinToRegisterPin(BoardPin bpin);
CoreStatus ioSetBoardPinValue(BoardPin bpin, PinValue pinValue);
CoreStatus ioSetBoardPinMode(BoardPin bpin, PinMode pinMode);

// Timers and Counters
void timersClearRegisters(void);

// Run LED
void ioRunLedOn(void);
void ioRunLedOff(void);
void ioRunLedBlink(uint16_t times);

#endif /* COMMON_H */