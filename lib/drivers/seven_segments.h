/* In the name of Allah, the Most Gracious, the Most Merciful */

#pragma once 

#include <avr/io.h>

/* Module inputs */
#define DDRseg DDRB
#define PORTseg PORTB
#define INIT_DECODER_PORT DDRD |= (((1 << 6) - 1) << 2);
#define SET_DECODER_PORT(digit_index) PORTD = (PORTD & 0x03) | (digit_index << 2)
#define REFRESH_RATE 0.05
#define NUMBER_OF_DIGITS 38

#include <util/delay.h>

void SevenSegments_init();
void SevenSegments_write(uint8_t digit, uint8_t digit_index);
void SevenSegments_writeDigits(uint8_t digits[NUMBER_OF_DIGITS]);