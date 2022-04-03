/*
 * timersCommon.c
 *
 * Created: 2022-03-27 12:19:43 AM
 *  Author: Andrew Ingram
 */

#include "common.h"
#include <avr/interrupt.h>

void timersClearRegisters(void)
{
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR2A = 0;
	TCCR2B = 0;
}