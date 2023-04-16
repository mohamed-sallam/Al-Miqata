/* In the name of Allah, the Most Gracious, the Most Merciful */

#pragma once 

#include <avr/io.h>

/* Module inputs */
#define DDRseg DDRB
#define PORTseg PORTB
#define DDRdecoder_seg DDRC
#define PORTdecoder_seg PORTC
#define NUMBER_OF_DECODER_PORTS 6
#define REFRESH_RATE 0.1
/*38*/
#define NUMBER_OF_DIGITS 24
#define F_CPU 1000000UL

#include <util/delay.h>

void SevenSegments_init();
void SevenSegments_write(uint8_t digit, uint8_t digit_index);
void SevenSegments_writeDigits(uint8_t digits[NUMBER_OF_DIGITS]);