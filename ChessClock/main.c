/*
 * ChessClock.c
 *
 * Created: 2023-02-12 8:37:24 PM
 * Author : patmc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL		//8MHz internal clock source

/***********************************
globals, may be moved to a header
***********************************/
unsigned int tick;	//for counting timer overflows
char white_OR_black = 0;	//flag for whose turn it is, 0 for white, 1 for black
unsigned long whiteTime_ms;		//time for white in ms
unsigned long blackTime_ms;		//time for black in ms

/***********************************
hardware initializations, may move to a header
***********************************/
void init_timer0(void);

/***********************************
interrupts, may be moved to header
***********************************/
ISR(TIMER0_OVF_vect)
{
	/*
	256 * 8us = 2.048ms for 1 overflow
	5 overflows = 10.24ms = 0.01024s
	something in this function should
		also be done for 7segs
	*/
	tick++;
	
	if(white_OR_black == 0)
		whiteTime_ms-=2;
	else
		blackTime_ms-=2;
}

int main(void)
{
	init_timer0();
	tick = 0;
	
	/* enable interrupts */
	sei();
	
    while (1) 
    {
		
    }
}

void init_timer0(void)
{
	GTCCR = 0x00;	//general timer/counter control reg, this is redundancy
	TCCR0A = 0x00;	//timer control reg A, pg 106 MEGA168P datasheet, used for OC pin
	TCCR0B = 0x03;	//reg B, pg 109 in datasheet, prescale by 64
	/*
	prescale by 64, 8MHz clock source
	new clock source = 8M/64 = 125k
	1 clock count = 8us
	*/
}
