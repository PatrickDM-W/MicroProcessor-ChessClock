/*
 * ChessClock.c
 *
 * Created: 2023-02-12 8:37:24 PM
 * Author : Patrick W
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL		//8MHz internal clock source

/***********************************
globals, may be moved to a header
***********************************/
unsigned int tick;	//for counting timer overflows
char white_OR_black = 0;	//flag for whose turn it is, 0 for white, 1 for black
unsigned int white_ms_left;		//number of ms left for white, range 0-1000,	2 bytes
unsigned char white_s_left;		//number of s left for white, range 0-60,		1 byte
unsigned char white_min_left;	//number of min left for white, range 0-99,		1 byte
unsigned int black_ms_left;		//number of ms left for black, range 0-1000,	2 bytes
unsigned char black_s_left;		//number of s left for black, range 0-60,		1 byte
unsigned char black_min_left;	//number of min left for black, range 0-99,		1 byte

/***********************************
functions, may move to a header
***********************************/
void 7seg_dis_time(void);
void raise_flag(void);


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
	*/
	tick++;
	
	if(white_OR_black == 0)		//should move all this to a function
	{
		white_ms_left -= 2;		//decrement by 2ms every overflow
		if (white_ms_left <= 0)	//1 second gone
		{
			white_s_left--;
			white_ms_left = 1000;
			if(white_s_left <= 0)	//1 minute gone
			{
				white_min_left--;
				
				if(white_min_left <= 0)
				{
					raise_flag();		//white has lost
				}
				else
				{
				white_s_left = 60;
				}
			}
		}
	}
	else
	{	
		black_ms_left -= 2;		//decrement by 2ms every overflow
	}
}

int main(void)
{
	/* initialize */
	init_timer0();
	tick = 0;
	
	/* enable interrupts */
	sei();
	
    while (1) 
    {
		
    }
}

/***********************************
Purpose: prepare timer for use
I/O: nothing
Author: Patrick W
***********************************/
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

/***********************************
Purpose: output time in min:sec to 7seg display
I/O: none
Author: Patrick W

function converts given time to min:sec
	or sec:ms
	as needed
turn is accessed as global
white or black time is accessed as globals
	to save memory
***********************************/
void 7seg_dis_time(void)
{
	
	if (white_OR_black == 0)		//white turn
	{
		if(white_min_left > 0)		//display as min.sec
		{
			
		}
		else
		{
			
		}
		
	}
	else							//black turn
	{
		
	}
}