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
unsigned char tick;	//for counting timer overflows
unsigned char dig_7seg_select;	//keep track of what 7seg to output to
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
void process_7seg_time(void);
void output_7seg_time(unsigned char digit);
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
	256 * 1us = 256us for 1 overflow
	*/
	tick++;
	7seg_dis_time();
	
	/*
	every tick, 7seg should be updated
	every 4 ticks (~1ms), clock time should be updated
	*/
	
	if(tick >= 4)
	{
		if(white_OR_black == 0)		//white turn
		{
			white_ms_left--;		//decrement by 1ms every 4 ticks
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
			black_ms_left--;		//decrement by 1ms every overflow
			if(black_ms_left <= 0)
			{
				black_s_left--;
				black_ms_left = 1000;
				if(black_s_left <= 0)	//1 minute gone
				{
					black_min_left--;
					
					if(black_min_left <= 0)
					{
						raise_flag();		//black has lost
					}
					else
					{
						black_s_left = 60;
					}
				}
			}
		}
		tick = 0;
	}
	
}

int main(void)
{
	/* initialize */
	init_timer0();
	
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
	TCCR0B = 0x02;	//reg B, pg 109 in datasheet, prescale by 8
	/*
	prescale by 8, 8MHz clock source
	new clock source = 8M/8 = 1M
	1 clock count = 1us
	*/
	tick = 0;
}

/***********************************
Purpose: process info for output to 7seg
I/O: none
Author: Patrick W

function converts given time to min:sec
	or sec:ms
	as needed
turn is accessed as global
white or black time is accessed as globals
	to save memory
***********************************/
void process_7seg_time(void)
{
	unsigned char digit;
	
	if (white_OR_black == 0)		//white turn
	{
		if(white_min_left > 0)		//display as (2)min.(2)sec
		{
			switch (dig_7seg_select)
			{
				case 0:
					digit = white_min_left/10;
					break;
				
				case 1:
					digit = white_min_left%10;
					break;
				
				case 2:
					digit = white_s_left/10;
					break;
				
				case 3:
				digit = white_s_left%10;
					break;
			}
		}
		else if(white_s_left > 9)		//display as (2)sec.(2)ms
		{
			switch (dig_7seg_select)
			{
				case 0:					//leftmost digit
					digit = white_s_left/10;
					break;
				
				case 1:					//second left digit
					digit = white_s_left%10;
					break;
				
				case 2:					//third digit from left
					digit = white_ms_left/100;
					digit = digit%10;
					break;
				
				case 3:					//rightmost digit
					digit = white_ms_left/10;
					digit = digit%10;
					break;
			}
		}
		else							//display as (1)sec.(3)ms
		{
			switch (dig_7seg_select)
			{
				case 0:
				break;
				
				case 1:
				break;
				
				case 2:
				break;
				
				case 3:
				break;
			}
		}
		
	}
	else							//black turn
	{
		
	}
	
	dig_7seg_select++;
	if(dig_7seg_select >= 4)
		dig_7seg_select=0;
	return;
}