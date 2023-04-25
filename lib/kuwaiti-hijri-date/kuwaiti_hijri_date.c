#include "kuwaiti_hijri_date.h"

void KuwaitiHijriDate_calculate(double julian_date, uint8_t output[8])
{
    const double y = 354.3666666666667;
    const double shift1 = 0.1335;

    double z = julian_date - 1948084.0;
    uint32_t cyc = z / 10631;
    z = z - 10631 * cyc;
    uint8_t j = (z - shift1) / y;
    z = z - (uint16_t)(j * y + shift1);

    uint16_t year = 30 * cyc + j;
    uint8_t month = (z + 28.5001) / 29.5;
    if (month == 13)
        month = 12;
    uint8_t day = z - (uint8_t)(29.5001 * month - 29);

    /* Year digits */
    for (uint8_t i = 0; i < 4; ++i, year /= 10)
        output[i] = year % 10;
    
    /* Day digits */
    output[4] = day % 10;
    output[5] = (day / 10) % 10;

    /* Month digits */
    output[6] = month % 10;
    output[7] = (month / 10) % 10;
}