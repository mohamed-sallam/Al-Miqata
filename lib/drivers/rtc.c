#include "rtc.h"

#include "communication/i2c.h"

void Rtc_init()
{
    I2c_init();
    I2c_start();

    I2c_write(0xD0);
    I2c_write(0x07);
    I2c_write(0x00);

    I2c_stop();
}

void Rtc_setDateTime(const Date *const date, const Time *const time)
{
    I2c_start();

    I2c_write(0xD0);
    I2c_write(0x00);

    I2c_write(time->sec);
    I2c_write(time->min);
    I2c_write(time->hour);
    I2c_write(date->day);
    I2c_write(date->date);
    I2c_write(date->month);
    I2c_write(date->year);

    I2c_stop();
}

void Rtc_getTime12H(uint8_t out[4], uint8_t *const is_pm)
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x01);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    uint8_t min = I2c_read(1);
    uint8_t hour = I2c_read(0);
    I2c_stop();

    out[0] = min & 0x0F;
    out[1] = (min >> 4) & 0x0F;
    hour = (hour & 0x0F) + ((hour >> 4) & 0x0F) * 10;
    *is_pm = (hour >= 12);
    hour = (hour + 11) % 12 + 1;
    out[2] = hour % 10;
    out[3] = (hour / 10) % 10;
}

void Rtc_getTime24H(uint8_t out[4])
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x01);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    uint8_t min = I2c_read(1);
    uint8_t hour = I2c_read(0);
    I2c_stop();

    /* Minutes digits */
    out[0] = min & 0x0F;
    out[1] = (min >> 4) & 0x0F;

    /* Hour digits */
    out[2] = hour & 0x0F;
    out[3] = (hour >> 4) & 0x0F;
}

void Rtc_getDate(uint8_t out[8])
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x04);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    uint8_t date = I2c_read(1);
    uint8_t month = I2c_read(1);
    uint8_t year = I2c_read(0);
    I2c_stop();

    /* Year digits */
    out[0] = year & 0x0F;
    out[1] = (year >> 4) & 0x0F;
    out[2] = 0;
    out[3] = 2;

    /* Date digits */
    out[4] = date & 0x0F;
    out[5] = (date >> 4) & 0x0F;

    /* Month digits */
    out[6] = month & 0x0F;
    out[7] = (month >> 4) & 0x0F;
}

uint8_t Rtc_getDay()
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x03);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    uint8_t day = I2c_read(0);
    I2c_stop();

    return day - 1;
}
