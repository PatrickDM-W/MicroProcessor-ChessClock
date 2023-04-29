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
	TCCR0A = 0x00;	//pg 86 of atmega328p sheet no need for special modes
	TCCR0B = 0x02;	//pg 87, prescale by 8
	TCNT0 = 0;		//start count at 0
	
	TIMSK0 = 0x01;	//enable overflow interrupt
	
	/*
	prescale by 8, 16MHz clock source
	new clock source = 16M/8 = 2M
	1 clock count = 500ns
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
