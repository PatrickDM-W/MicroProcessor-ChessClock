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

/* global variables */
unsigned char tick;	//for counting timer overflows

char white_OR_black;	//flag for whose turn it is, 0 for white, 1 for black
int white_ms_left;		//number of ms left for white, range 0-1000,	2 bytes
char white_s_left;		//number of s left for white, range 0-60,		1 byte
char white_min_left;	//number of min left for white, range 0-99,		1 byte
int black_ms_left;		//number of ms left for black, range 0-1000,	2 bytes
char black_s_left;		//number of s left for black, range 0-60,		1 byte
char black_min_left;	//number of min left for black, range 0-99,		1 byte

/***********************************
hardware initialization functions
***********************************/
void init_timer0(void);			//prepare timer0 for use
void init_hardware(void);		//prepare I/O pins for use

/***********************************
general functions
***********************************/
void output_digit_select(char digit_select);		//select digit to output
void output_7seg(char digit);	//output function for 7seg
void raise_flag(void);			//function to raise flag when out of time	

#endif /* CHESSCLOCK_H_ */