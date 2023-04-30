/*
 * ChessClock.h
 *
 * Created: 2023-02-26 12:22:16 PM
 *  Author: patmc
 */ 


#ifndef CHESSCLOCK_H_
#define CHESSCLOCK_H_

//global libraries
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL		//16MHz internal clock source

#include <util/delay.h>

/* global variables */
unsigned char tick;	//for counting timer overflows
unsigned char digit_out;		//what digit to output to
	/*
	0 = leftmost
	1 = second left
	2 = third left
	3 = rightmost
	*/ 

unsigned char white_OR_black;	//flag for whose turn it is, 0 for white, 1 for black

/* time variables */
unsigned int white_ms_left;		//number of ms left for white, range 0-1000,	2 bytes
unsigned char white_s_left;		//number of s left for white, range 0-60,		1 byte
char white_min_left;	//number of min left for white, range 0-99,		1 byte
unsigned int black_ms_left;		//number of ms left for black, range 0-1000,	2 bytes
unsigned char black_s_left;		//number of s left for black, range 0-60,		1 byte
char black_min_left;	//number of min left for black, range 0-99,		1 byte

/* 
formatting variables 
0 = min(2).sec(2)
1 = sec(2).ms(2)
2 = sec(1).ms(3)
*/
unsigned char white_time_format;
unsigned char black_time_format;

/***********************************
hardware initialization functions
***********************************/
void init_timer0(void);			//prepare timer0 for use
void init_hardware(void);		//prepare I/O pins for use

/***********************************
general functions
***********************************/
void output_digit_select(unsigned char digit_select);		//select digit to output
void output_7seg(unsigned char digit);	//output function for 7seg
void raise_flag(void);			//function to raise flag when out of time	
void out_time(unsigned int ms_left, unsigned char s_left, char min_left, unsigned char time_format);

#endif /* CHESSCLOCK_H_ */