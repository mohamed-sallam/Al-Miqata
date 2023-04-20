#include "seven_segments.h"


void SevenSegments_init()
{
    DDRseg |= 0x7F;
    INIT_DECODER_PORT; 
}

void SevenSegments_write(uint8_t digit, uint8_t digit_index)
{
    const uint8_t digit_patterns[12] = {
        0x3f, /*0*/
        0x06, /*1*/
        0x5b, /*2*/
        0x4f, /*3*/
        0x66, /*4*/
        0x6d, /*5*/
        0x7d, /*6*/
        0x07, /*7*/
        0x7f, /*8*/
        0x6f, /*9*/
        0x4F, /*E*/
        0x05  /*r*/
    };

    SET_DECODER_PORT(digit_index);
    PORTseg = digit_patterns[digit % 12];
}

void SevenSegments_writeDigits(uint8_t digits[NUMBER_OF_DIGITS]) 
{
    for(uint8_t i = 0; i < NUMBER_OF_DIGITS; ++i) 
    {
        SevenSegments_write(digits[i], i);
        _delay_ms(REFRESH_RATE);
    }
}