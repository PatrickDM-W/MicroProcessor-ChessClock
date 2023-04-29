/*
 * ChessClock.c
 *
 * Created: 2023-02-12 8:37:24 PM
 * Author : Patrick W
 */ 

#include "ChessClock.h"

/***********************************
interrupts, may be moved to header
***********************************/
ISR(TIMER0_OVF_vect)
{
	/*
	256 * 500ns = 128us for 1 overflow
	this function is called every 128us
	*/
	tick++;
	
	/*
	every other tick, output to 7seg
	every 8 ticks (~1ms), process time internally
	*/
	
	if(tick >= 8)
	{
		if(white_OR_black == 0)		//white turn
		{
			white_ms_left--;		//decrement by 1ms every 8 ticks
			if (white_ms_left <= 0)	//1 second gone
			{
				white_s_left--;
				if(white_s_left <= 0)	//1 minute gone
				{
					white_min_left--;
					
					if(white_min_left < 0)
					{
						raise_flag();		//white has lost
					}
					else
					{
						white_s_left = 59;
					}
				}
				white_ms_left = 1000;
			}
		}
		else
		{
			black_ms_left--;		//decrement by 1ms every 8 ticks 
			if(black_ms_left <= 0)
			{
				black_s_left--;
				if(black_s_left <= 0)	//1 minute gone
				{
					black_min_left--;
					
					if(black_min_left < 0)
					{
						raise_flag();		//black has lost
					}
					else
					{
						black_s_left = 59;
					}
				}
				black_ms_left = 1000;
			}
		}
		tick = 0;
	}
}

int main(void)
{
	/* initialize */
	init_timer0();
	init_hardware();
	
	/* enable interrupts */
	//sei();
	
    while (1) 
    {
		raise_flag();
    }
}

/***********************************
Purpose: light LED for game over
I/O: none
Author: Patrick W
PORT		pin			LED

works perfectly - April 29, 2023
***********************************/
void raise_flag()
{
	TIMSK0 = 0x00;		//turn off timer interrupt
	
	output_digit_select(5);		//turn on all digits
	PORTB |= 0x02;				//turn on segs a,d,g
	PORTC |= 0x12;
}