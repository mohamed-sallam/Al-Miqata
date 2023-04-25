#include "led.h"

void Led_init()
{
    DDRleds |= 0x7F;
    INIT_LED_DECODER_PORT; 
}

void Led_lit(Led led)
{
    SET_LED_DECODER_PORT(led.group_index);
    PORTleds = (1 << led.index);
}

void Led_litLeds(Led leds[NUMBER_OF_LED_GROUPS]) 
{
    for(uint8_t i = 0; i < NUMBER_OF_LED_GROUPS; ++i) 
    {
        Led_lit(leds[i]);
        _delay_ms(LED_REFRESH_RATE);
    }
}

