#include "rtc.h"

#include "communication/i2c.h"

void Rtc_init()
{
    I2C_Init();
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

void Rtc_getTime(Time *const time)
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x00);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    time->sec = I2c_read(1);
    time->min = I2c_read(1);
    time->hour = I2c_read(0);
    I2c_stop();
}

void Rtc_getDate(Date *const date)
{
    I2c_start();
    I2c_write(0xD0);
    I2c_write(0x03);
    I2c_stop();

    I2c_start();
    I2c_write(0xD1);
    date->day = I2c_read(1);
    date->date = I2c_read(1);
    date->month = I2c_read(1);
    date->year = I2c_read(0);
    I2c_stop();
}
