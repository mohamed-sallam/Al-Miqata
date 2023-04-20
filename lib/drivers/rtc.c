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

void Rtc_getTime(Time *const out)
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x00);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    out->sec = I2c_read(1);
    out->min = I2c_read(1);
    out->hour = I2c_read(0);
    I2c_stop();
}

void Rtc_getDate(Date *const out)
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x03);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    out->day = I2c_read(1);
    out->date = I2c_read(1);
    out->month = I2c_read(1);
    out->year = I2c_read(0);
    I2c_stop();
}
