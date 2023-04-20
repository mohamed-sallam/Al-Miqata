#include "kuwaiti_hijri_date.h"

void KuwaitiHijriDate_calculate(double julian_date, uint16_t* const out_year, uint8_t* const out_month, uint8_t* const out_day)
{
    double y = 354.366666667;
    double shift1 = 0.1335;
    double z = julian_date - 1948084.0;
    uint8_t cyc = z / 10631;
    z = z - 10631 * cyc;
    uint8_t j = (z - shift1) / y;
    z = z - (uint16_t)(j * y + shift1);

    *out_year = 30 * cyc + j;
    *out_month = (z + 28.5001) / 29.5;
    if (*out_month == 13)
        *out_month = 12;
    *out_day = z - (uint16_t)(29.5001 * (*out_month) - 29);
}