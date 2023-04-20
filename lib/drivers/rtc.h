#pragma once

#include <avr/io.h>

typedef struct
{
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;  
} Date;

typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
} Time;


void Rtc_init();
void Rtc_setDateTime(const Date *const date, const Time *const time);
void Rtc_getTime(Time *const time);
void Rtc_getDate(Date *const date);
