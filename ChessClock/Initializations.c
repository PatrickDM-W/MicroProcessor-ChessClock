/*
 * Initializations.c
 *
 * Created: 2023-03-25 8:54:24 AM
 *  Author: patmc
 */ 

#include "ChessClock.h"

/***********************************
Purpose: prepare timer for use
I/O: nothing
Author: Patrick W
***********************************/
void init_timer0(void)
{
	GTCCR = 0x00;	//general timer/counter control reg, this is redundancy
	TCCR0A = 0x00;	//timer control reg A, pg 106 MEGA168P datasheet, used for OC pin
	TCCR0B = 0x02;	//reg B, pg 109 in datasheet, prescale by 8
	/*
	prescale by 8, 8MHz clock source
	new clock source = 8M/8 = 1M
	1 clock count = 1us
	*/
	tick = 0;
}

/***********************************
Purpose: prepare I/O ports
I/O: nothing
Author: Patrick W
***********************************/
void init_hardware(void)
{
	DDRB = 0x3F;
	DDRC = 0x3F;
}
