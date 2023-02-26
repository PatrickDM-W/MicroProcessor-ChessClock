/*
 * ChessClock.h
 *
 * Created: 2023-02-26 12:22:16 PM
 *  Author: patmc
 */ 


#ifndef CHESSCLOCK_H_
#define CHESSCLOCK_H_
/* global variables */
unsigned char tick;	//for counting timer overflows
unsigned char dig_7seg_select;	//keep track of what 7seg to output to
char white_OR_black = 0;	//flag for whose turn it is, 0 for white, 1 for black
unsigned int white_ms_left;		//number of ms left for white, range 0-1000,	2 bytes
unsigned char white_s_left;		//number of s left for white, range 0-60,		1 byte
unsigned char white_min_left;	//number of min left for white, range 0-99,		1 byte
unsigned int black_ms_left;		//number of ms left for black, range 0-1000,	2 bytes
unsigned char black_s_left;		//number of s left for black, range 0-60,		1 byte
unsigned char black_min_left;	//number of min left for black, range 0-99,		1 byte




#endif /* CHESSCLOCK_H_ */