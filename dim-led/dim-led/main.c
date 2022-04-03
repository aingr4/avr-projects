/*
 * main.c
 *
 * Created: 2022-03-26 1:52:27 PM
 * Author : Andrew Ingram
 */

#include "common.h"
#include "log.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DIM_LED_PIN DBP9

void dimLedMain();

int main() 
{	
	LOG_INIT(LogMethod_USART);
	
	while (true)
	{
		LOG(LogLevel_ERROR, "Error\n");
		_delay_ms(500);
		LOG(LogLevel_INFO, "Info\n");
		_delay_ms(500);
		LOG(LogLevel_DEBUG, "Debug\n");
		_delay_ms(500);
	}
	
	return EXIT_SUCCESS;
}

void dimLedMain()
{
		uint16_t duty_cycle = 0; // 63/255 = 25%
		uint16_t direction  = 0;

		ioRunLedBlink(5); // Blink run led 5 times
		timersClearRegisters(); // Clear timer and counter registers

		while(true)
		{
			ioAnalogWrite(DIM_LED_PIN, duty_cycle);
			
			if (duty_cycle == 0)
			{
				direction = 1;
			}
			else if (duty_cycle == 255)
			{
				direction = 0;
			}

			if (direction == 1)
			{
				duty_cycle++;
			}
			else
			{
				duty_cycle--;
			}
			_delay_ms(4);
		}
}