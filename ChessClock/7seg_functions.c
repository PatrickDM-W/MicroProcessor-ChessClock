/*
 * _7seg_functions.c
 *
 * Created: 2023-03-25 9:19:33 AM
 *  Author: patmc
 */ 

#include "ChessClock.h"

/***********************************
Purpose: process info for output to 7seg
I/O: none
Author: Patrick W

called ever .25ms

function converts given time to min:sec
	or sec:ms
	as needed
	sends digit for 7seg to display to external function
turn is accessed as global
white or black time is accessed as globals
	to save memory
***********************************/
void process_7seg_time(void)
{
	char digit, dig_select_check;
	dig_select_check = dig_DP_7seg_select && 0x0F;	//use to decode info of dig_DP variable
	
	if (white_OR_black == 0)		//white turn
	{
		if(white_min_left > 0)		//display as (2)min.(2)sec
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x40;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit,	0bxxxx.1000
			{
				digit = white_min_left/10;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = white_min_left%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = white_s_left/10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = white_s_left%10;
			}
		}
		else if(white_s_left > 9)		//display as (2)sec.(2)ms
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x40;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit
			{
				digit = white_s_left/10;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = white_s_left%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = white_ms_left/100;
				digit = digit%10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = white_ms_left/10;
				digit = digit%10;
			}
		}
		else							//display as (1)sec.(3)ms
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x80;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit
			{
				digit = white_s_left;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = white_ms_left/100;
				digit = digit%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = white_ms_left/10;
				digit = digit%10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = white_ms_left%10;
			}
		}
	}
	else							//black turn
	{
		if(black_min_left > 0)		//display as (2)min.(2)sec
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x40;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit
			{
				digit = black_min_left/10;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = black_min_left%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = black_s_left/10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = black_s_left%10;
			}
		}
		else if(black_s_left > 9)		//display as (2)sec.(2)ms
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x40;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit
			{
				digit = black_s_left/10;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = black_s_left%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = black_ms_left/100;
				digit = digit%10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = black_ms_left/10;
				digit = digit%10;
			}
		}
		else							//display as (1)sec.(3)ms
		{
			dig_DP_7seg_select &= 0x0F;		//clear upper nibble
			dig_DP_7seg_select |= 0x80;		//set DP location
			
			if(dig_select_check == 8)	//leftmost digit
			{
				digit = black_s_left;
			}
			else if (dig_select_check == 4)	//second digit from left
			{
				digit = black_ms_left/100;
				digit = digit%10;
			}
			else if (dig_select_check == 2)	//third digit from left
			{
				digit = black_ms_left/10;
				digit = digit%10;
			}
			else if (dig_select_check == 1)	//rightmost digit
			{
				digit = black_ms_left%10;
			}
		}
	}
	
	output_digit_select();			//set proper digit
	output_7seg_time(digit);		//send to be output
	
	dig_DP_7seg_select &= 0xF0;	//clear bottom nibble
	
	switch(dig_select_check)		//set next digit to check
	{
		case 8:
			dig_DP_7seg_select |= 0x04;
			break;
		case 4:
			dig_DP_7seg_select |= 0x02;
			break;
		case 2:
			dig_DP_7seg_select |= 0x01;
			break;
		case 1:
			dig_DP_7seg_select |= 0x08;
			break;
		default:
			dig_DP_7seg_select |= 0x08;
	}
	return;
}

/***********************************
Purpose: set 7seg display
I/O: none
Author: Patrick W
***********************************/
void output_digit_select(void)
{
	char dig_select_test = dig_DP_7seg_select && 0x0F;	//lower nibble
	char DP_select_test = dig_DP_7seg_select && 0xF0;	//upper nibble
	
	if(dig_select_test == 8)		//first digit
	{
		PORTB = 0x18;
		PORTC = 0x01;
		
		if(DP_select_test == 128)
			PORTC |= 0x08;
	}
	else if (dig_select_test == 4)	//second digit
	{
		PORTB = 0x11;
		PORTC = 0x01;
		
		if(DP_select_test == 64)
			PORTC |= 0x08;
	}
	else if (dig_select_test == 2)	//third digit
	{
		PORTB = 0x09;
		PORTC = 0x01;
		
		if(DP_select_test == 32)
			PORTC |= 0x08;
	}
	else if (dig_select_test == 1)	//fourth digit
	{
		PORTB = 0x19;
		PORTC = 0x00;
		
		if(DP_select_test == 16)
			PORTC |= 0x08;
	}
	return;
}

/***********************************
Purpose: output to 7seg display
I/O: digit to output
Author: Patrick W

pin map to follow:
	LED model: 5641AS
	pins follow CCW count starting at bottom left 1-12
	pin		segment/digit	PORT		PIN
	1		e				PC5			a5	
	2		d				PC4			a4
	3		DP				PC3			a3
	4		c				PC2			a2
	5		g				PC1			a1
	6		digit 4			PC0			a0
	7		b				PB5			d13
	8		digit 3			PB4			d12
	9		digit 2			PB3			d11
	10		f				PB2			d10
	11		a				PB1			d9
	12		digit 1			PB0			d8
***********************************/
void output_7seg_time(char digit)
{	
	switch (digit)
	{
		case 0:
			PORTB |= 0x26;
			PORTC |= 0x36;
			break;
		case 1:
			PORTB |= 0x22;
			PORTC |= 0b00;
			break;
		case 2:
			PORTB |= 0x22;
			PORTC |= 0x32;
			break;
		case 3:
			PORTB |= 0x22;
			PORTC |= 0x14;
			break;
		case 4:
			PORTB |= 0x24;
			PORTC |= 0x06;
			break;
		case 5:
			PORTB |= 0x06;
			PORTC |= 0x16;
			break;
		case 6:
			PORTB |= 0x06;
			PORTC |= 0x36;
			break;
		case 7:
			PORTB |= 0x22;
			PORTC |= 0x04;
			break;
		case 8:
			PORTB |= 0x26;
			PORTC |= 0x36;
			break;
		case 9:
			PORTB |= 0x26;
			PORTC |= 0x16;
			break;
	}
	return;
}