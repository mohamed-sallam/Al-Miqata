#include <avr/io.h>

#define F_CPU 8000000UL

void timer0_init(unsigned char *digits);
void timer0_countdown(unsigned char minutes);