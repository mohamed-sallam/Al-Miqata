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
void Rtc_getTime(uint8_t out[4]);
void Rtc_getDate(uint8_t out[8]);
uint8_t Rtc_getDay();
