#include <avr/io.h>

#include "prayer_times.h"

#define F_CPU 8000000UL

void timer1_init();
void timer1_countdown(int16_t minutes);