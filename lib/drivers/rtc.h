#pragma once

#include <avr/io.h>

typedef struct __attribute__((packed))
{
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;  
} Date;

typedef struct __attribute__((packed))
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
} Time;

typedef enum __attribute__((packed))
{
    ClockTimeFormat_24h = 0,
    ClockTimeFormat_12h = 1
} ClockTimeFormat;

void Rtc_init( );
void Rtc_setDateTime(const Date *const date, const Time *const time);
void Rtc_getTime12H(uint8_t out[4], uint8_t* const is_pm);
void Rtc_getDate(uint8_t out[8]);
uint8_t Rtc_getDay();
