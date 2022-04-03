/*
 * ioCommon.c
 *
 * Created: 2022-03-26 1:52:27 PM
 * Author : Andrew Ingram
 */ 

#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

CoreStatus ioAnalogWrite(BoardPin bpin, uint16_t cycle) 
{
	CoreStatus coreStatus = CoreStatus_OK;

	if (!isDigitalBoardPin(bpin))
	{
		coreStatus = CoreStatus_ERROR;
		goto exit;
	}

	if (bpin == DBP3) 
	{
		// set UNO pin 3/PD3 to PinMode_OUTPUT, 488.3Hz
		ioSetBoardPinMode(DBP3, PinMode_OUTPUT);
		
		// TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00100011
		TCCR2A |= (BITVALUE(COM2B1) | BITVALUE(WGM21) | BITVALUE(WGM20));

		// TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
		TCCR2B |=  (BITVALUE(CS22) | BITVALUE(CS20));

		OCR2B = cycle;
	}
	else if (bpin == DBP5) 
	{
		// set UNO pin 5/PD5 to PinMode_OUTPUT, 976.6Hz
		ioSetBoardPinMode(DBP5, PinMode_OUTPUT);
		
		// TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM21 WGM20 ] = 00100011
		TCCR0A |= (BITVALUE(COM0B1) | BITVALUE(WGM21) | BITVALUE(WGM20));

		// TCCR0B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
		TCCR0B |=  (BITVALUE(CS21) | BITVALUE(CS20));

		OCR0B = cycle;
	}
	else if (bpin == DBP6) 
	{
		// set UNO pin 6/PD6 to PinMode_OUTPUT, 976.6Hz
		ioSetBoardPinMode(DBP6, PinMode_OUTPUT);
		
		// TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM21 WGM20 ] = 11000010
		TCCR0A |= (BITVALUE(COM0A1) | BITVALUE(COM0A0) | BITVALUE(WGM21) | BITVALUE(WGM20));

		// TCCR0B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
		TCCR0B |=  (BITVALUE(CS21) | BITVALUE(CS20));

		OCR0A = cycle;
	}
	else if (bpin == DBP9) 
	{
		// set UNO pin 9/PB1, 976.6Hz
		ioSetBoardPinMode(DBP9, PinMode_OUTPUT);
		
		// TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10 ] = 10000001
		TCCR1A |= (BITVALUE(COM1A1) | BITVALUE(WGM10));

		// TCCR1B [ 1CNC1 1CES1 0 WGM13 WGM12 CS12 CS11 CS10 ]
		TCCR1B |= (BITVALUE(WGM12) | BITVALUE(CS11) | BITVALUE(CS10));

		OCR1A = cycle;
	}
	else if (bpin == DBP10) 
	{
		// set UNO pin 10/PB2 to PinMode_OUTPUT, 976.6Hz
		ioSetBoardPinMode(DBP10, PinMode_OUTPUT);
		
		// TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10  ] = 00100001
		TCCR1A |= (BITVALUE(COM1B1) | BITVALUE(WGM10));

		// TCCR1B [ 1CNC1 1CES1 0 WGM13 WGM12 CS12 CS11 CS10 ]
		TCCR1B |= (BITVALUE(WGM12) | BITVALUE(CS11) | BITVALUE(CS10));

		OCR1B = cycle;
	}
	else if (bpin == DBP11) 
	{
		// set UNO pin 11/PB3 to PinMode_OUTPUT, 488.3Hz
		ioSetBoardPinMode(DBP11, PinMode_OUTPUT);
		
		// TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 10000011
		TCCR2A |= (BITVALUE(COM2A1) | BITVALUE(WGM21) | BITVALUE(WGM20));

		// TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
		TCCR2B |= (BITVALUE(CS22) | BITVALUE(CS20));

		OCR2A = cycle;
	}

exit:
	return coreStatus;
}

CoreStatus ioSetBoardPinMode(BoardPin bpin, PinMode pinMode)
{
	CoreStatus coreStatus = CoreStatus_OK;
	uint16_t rpin = ioBoardPinToRegisterPin(bpin);
	if (rpin == -1)
	{	
		coreStatus = CoreStatus_ERROR;
		goto exit;
	}
	
	if (bpin <= DBP7)
	{
		if (pinMode == PinMode_OUTPUT)
		{
			DDRD |= BITVALUE(rpin);
		}
		else if (pinMode == PinMode_INPUT)
		{
			DDRD &= ~BITVALUE(rpin);
		}
	}
	else if (bpin <= DBP13)
	{
		if (pinMode == PinMode_OUTPUT)
		{
			DDRB |= BITVALUE(rpin);
		}
		else if (pinMode == PinMode_INPUT)
		{
			DDRB &= ~BITVALUE(rpin);
		}
	}
	else if (bpin <= ABP5)
	{
		if (pinMode == PinMode_OUTPUT)
		{
			DDRC |= BITVALUE(rpin);
		}
		else if (pinMode == PinMode_INPUT)
		{
			DDRC &= ~BITVALUE(rpin);
		}
	}
	
exit:
	return coreStatus;
}

CoreStatus ioSetBoardPinValue(BoardPin bpin, PinValue pinValue)
{
	CoreStatus coreStatus = CoreStatus_OK;
	uint16_t rpin = ioBoardPinToRegisterPin(bpin);
	if (rpin == -1)
	{
		coreStatus = CoreStatus_ERROR;
		goto exit;
	}
	
	if (pinValue == PinValue_HIGH)
	{
		PORTB |= (BITVALUE(rpin));
	} 
	else if (pinValue == PinValue_LOW)
	{
		PORTB &= ~(BITVALUE(rpin));
	}
	
exit:
	return coreStatus;
}

bool ioIsDigitalBoardPin(uint16_t bpin)
{
	return (bpin >= DBP0 && bpin <= DBP13);
}

bool ioIsAnalogBoardPin(uint16_t bpin)
{
	return (bpin >= ABP0 && bpin <= ABP5);
}

bool ioIsBoardPin(uint16_t bpin)
{
	return (bpin >= ABP0 && bpin <= ABP5 && bpin >= DBP0 && bpin <= DBP13);
}

uint16_t ioBoardPinToRegisterPin(BoardPin bpin)
{
	int rpin = -1;
	switch (bpin)
	{
		case DBP0:
		rpin = PORTD0;
		break;
		case DBP1:
		rpin = PORTD1;
		break;
		case DBP2:
		rpin = PORTD2;
		break;
		case DBP3:
		rpin = PORTD3;
		break;
		case DBP4:
		rpin = PORTD4;
		break;
		case DBP5:
		rpin = PORTD5;
		break;
		case DBP6:
		rpin = PORTD6;
		break;
		case DBP7:
		rpin = PORTD7;
		break;
		case DBP8:
		rpin = PORTB0;
		break;
		case DBP9:
		rpin = PORTB1;
		break;
		case DBP10:
		rpin = PORTB2;
		break;
		case DBP11:
		rpin = PORTB3;
		break;
		case DBP12:
		rpin = PORTB4;
		break;
		case DBP13:
		rpin = PORTB5;
		break;
		case ABP0:
		rpin = PORTC0;
		break;
		case ABP1:
		rpin = PORTC1;
		break;
		case ABP2:
		rpin = PORTC2;
		break;
		case ABP3:
		rpin = PORTC3;
		break;
		case ABP4:
		rpin = PORTC4;
		break;
		case ABP5:
		rpin = PORTC5;
		break;
	}
	return rpin;
}

void ioRunLedOn(void)
{
	ioSetBoardPinMode(RUN_LED_PIN, PinMode_OUTPUT);
	ioSetBoardPinValue(RUN_LED_PIN, PinValue_HIGH);
}

void ioRunLedOff(void)
{
	ioSetBoardPinMode(RUN_LED_PIN, PinMode_OUTPUT);
	ioSetBoardPinValue(RUN_LED_PIN, PinValue_LOW);
}

void ioRunLedBlink(uint16_t times)
{
	for (int i=0;i<times;i++) {
		ioRunLedOn();
		_delay_ms(RUN_LED_BLINK_DELAY);
		ioRunLedOff();
		_delay_ms(RUN_LED_BLINK_DELAY);
	}
}