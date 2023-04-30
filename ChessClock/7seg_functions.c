/*
 * _7seg_functions.c
 *
 * Created: 2023-03-25 9:19:33 AM
 *  Author: patmc
 */ 

#include "ChessClock.h"


/***********************************
Purpose: set 7seg display
I/O: digit_DP_select
Author: Patrick W

must run BEFORE output_7seg
works perfectly - April 29, 2023
***********************************/
void output_digit_select(unsigned char digit_select)
{
	switch (digit_select)
	{
		case 0:					//leftmost digit
			PORTB = 0x18;
			PORTC = 0x01;
			break;	
		case 1:					//second left digit
			PORTB = 0x11;
			PORTC = 0x01;
			break;
		case 2:					//third left digit
			PORTB = 0x09;
			PORTC = 0x01;
			break;
		case 3:					//rightmost digit
			PORTB = 0x19;
			PORTC = 0x00;
			break;
		default:				//invalid selection
			PORTB = 0x00;		//all digits
			PORTC = 0x00;
			break;
	}
}

/***********************************
Purpose: output to 7seg display with DP
I/O: digit to output
Author: Patrick W

takes ones digit as digit to display
anything greater than 9 is given a decimal

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
	digit 1 is leftmost, digit 4 is rightmost

This function works perfectly - April 29, 2023
***********************************/
void output_7seg(unsigned char digit)
{	
	switch (digit % 10)
	{
		case 0:
			PORTB |= 0x26;
			PORTC |= 0x34;
			break;
		case 1:
			PORTB |= 0x20;
			PORTC |= 0x04;
			break;
		case 2:
			PORTB |= 0x22;
			PORTC |= 0x32;
			break;
		case 3:
			PORTB |= 0x22;
			PORTC |= 0x16;
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
			PORTC |= 0x06;
			break;
	}
	
	if(digit / 10)
		PORTC |= 0x08;
	return;
}