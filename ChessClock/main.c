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
	
	if(tick % 2)
	{
		if(digit_out >= 3)
			digit_out = 0;
		else
			digit_out++;
			
		if(white_OR_black)		//black turn
		{
			out_time(black_ms_left, black_s_left, black_min_left, black_time_format);
		}
		else
		{						//white turn
			out_time(white_ms_left, white_s_left, white_min_left, white_time_format);	
		}
	}
	
	if(tick >= 8)
	{
		if(white_OR_black == 0)		//white turn
		{
			if (white_ms_left <= 0)
			{
				if(white_s_left <= 0)
				{
					if(white_min_left == 0)
					{
						raise_flag();
					}
					else
					{
						white_min_left--;
						white_s_left = 59;
					}
				}
				else
				{
					white_s_left--;
					white_ms_left = 999;
				}
			}
			else
			{
				white_ms_left--;
			}
		}
		else
		{ 
			if(black_ms_left <= 0)
			{
				if(black_s_left <= 0)	//1 minute gone
				{
					if(black_min_left == 0)
					{
						raise_flag();
					}
					else
					{
						black_min_left--;
						black_s_left = 59;
					}
				}
				else
				{
					black_s_left--;
					black_ms_left = 999;
				}
			}
			else
			{
				black_ms_left--;
			}
		}
		
		tick = 0;
	}
	
	if (white_min_left > 0)
	{
		white_time_format = 0;
	}
	else if (white_s_left > 9)
	{
		white_time_format = 1;
	}
	else
	{
		white_time_format = 2;
	}
	
	if (black_min_left > 0)
	{
		black_time_format = 0;
	}
	else if(black_s_left > 9)
	{
		black_time_format = 1;
	}
	else
	{
		black_time_format = 2;
	}
}

int main(void)
{
	/* initialize */
	init_timer0();
	init_hardware();
	
	white_OR_black = 0;
	white_min_left = 0;
	white_s_left = 15;
	white_ms_left = 500;
	white_time_format = 0;
	digit_out = 0;
	
	/* enable interrupts */
	sei();
	
    while (1) 
    {
		
    }
}

/***********************************
Purpose: light LED for game over
I/O: none
Author: Patrick W
PORT		pin			LED
***********************************/
void raise_flag()
{	
	TIMSK0 = 0x00;
	
	output_digit_select(5);		//turn on all digits
	PORTB |= 0x02;				//turn on segs a,d,g
	PORTC |= 0x12;
}