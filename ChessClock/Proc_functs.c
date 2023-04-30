/*
 * Proc_functs.c
 *
 * Created: 2023-04-29 5:19:23 PM
 *  Author: patmc
 */ 

#include "ChessClock.h"

/***********************************
Purpose: output time
I/O: 
Author: Patrick W
***********************************/
void out_time(unsigned int ms_left, unsigned char s_left, char min_left, unsigned char time_format)
{
	unsigned char digit;
	
	output_digit_select(digit_out);
	
	switch(time_format)
	{
		case 0:		//min(2).sec(2)
			if(digit_out == 0)				//leftmost
			{
				digit = min_left / 10;		//tens digit
			} 
			else if (digit_out == 1)		//second left
			{
				digit = min_left % 10;		//ones digit
				digit = digit + 10;			//decimal place
			}
			else if(digit_out == 2)			//third left
			{
				digit = s_left / 10;
			}
			else if(digit_out == 3)			//rightmost
			{
				digit = s_left % 10;
			}
			break;
		case 1:		//sec(2).ms(2)
			if (digit_out == 0)			//leftmost
			{
				digit = s_left / 10;
			}
			else if (digit_out == 1)	//second left
			{
				digit = s_left % 10;
				digit = digit + 10;
			}
			else if (digit_out == 2)	//third left
			{
				digit = ms_left / 100;
			}
			else if (digit_out == 3)	//rightmost
			{
				digit = ms_left / 10;
				digit = digit % 10;
			}
			break;
		case 2:		//sec(1).ms(3)
			if (digit_out == 0)			//leftmost
			{
				digit = s_left % 10;	//redundant
				digit = digit + 10;
			}
			else if (digit_out == 1)	//second left
			{
				digit = ms_left / 100;
			}
			else if (digit_out == 2)	//third left
			{
				digit = ms_left / 10;
				digit = digit % 10;
			}
			else if (digit_out == 3)	//rightmost
			{
				digit = ms_left % 10;
			}
			break;
	}
	
	output_7seg(digit);
}