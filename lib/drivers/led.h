#pragma once

#include <avr/io.h>

/* Module inputs */
#define DDRleds DDRB
#define PORTleds PORTB
#define INIT_LED_DECODER_PORT DDRD |= (((1 << 6) - 1) << 2);
#define SET_LED_DECODER_PORT(digit_index) PORTD = (PORTD & 0x03) | (digit_index << 2)
#define LED_REFRESH_RATE 0.05
#define NUMBER_OF_LED_GROUPS 3

#include <util/delay.h>

typedef struct __attribute__((packed))
{
    uint8_t group_index;
    uint8_t index;
} Led;


void Led_init();
void Led_lit(Led led);
void Led_litLeds(Led leds[NUMBER_OF_LED_GROUPS]);
