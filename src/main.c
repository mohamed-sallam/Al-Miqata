/* In the name of Allah, the Most Gracious, the Most Merciful */

#include <avr/io.h>

#include <seven_segments.h>
#include <led.h>
#include <rtc.h>
#include <timer0.h>
#include <timer1.h>

#include <prayer_times.h>
#include <kuwaiti_hijri_date.h>

uint8_t hijri_date[8];
uint8_t gregorian_date[8];

void swapHijriGregorianDate(uint8_t digits[8], uint8_t *const hijri_gregorian_led_index)
{
    static uint8_t time_count = 0;
    if (time_count == 0)
    {
        for (uint8_t i = 0; i < 8; ++i)
            digits[i] = hijri_date[i];
        *hijri_gregorian_led_index = 0;
    }
    else if (time_count == 128)
    {
        for (uint8_t i = 0; i < 8; ++i)
            digits[i] = gregorian_date[i];
        *hijri_gregorian_led_index = 1;
    }
    ++time_count;
}

int main()
{
    const double julianDate = 2460049.4132407387;
    const Settings settings = {
        .method_params = {
            .fajr_angle = 19.5,
            .dhuhr_minutes = 0,
            .asr_factor = 1,
            .maghrib_is_minutes = True,
            .maghrib_value = 0,
            .isha_is_minutes = False,
            .isha_value = 17.5,
        },
        .higher_latitudes_method = HigherLatitudesMethod_NONE,
        .time_format = TimeFormat_12hr_NO_SUFFIX,
        .latitude = 30.033333,
        .timezone_offset = -0.08222226666666677,
        .rise_set_angle = 0.833,
        .offsets_in_minutes = {0, 0, 0, 0, 0, 0, 0}};
    PrayerTimes_init(&settings);
    uint8_t digits[NUMBER_OF_DIGITS];
    PrayerTimes_get(julianDate, &digits[12]);

    timer0_init(digits); // display 7-segments
    timer1_init();
    timer1_countdown(PrayerTimes_getNextTime());

    Rtc_init();
    const Date date = {
        .day = 0x06,
        .date = 0x21,
        .month = 0x04,
        .year = 0x23};
    const Time time = {
        .sec = 0x55,
        .min = 0x59,
        .hour = 0x11};
    SevenSegments_init();
    Rtc_setDateTime(&date, &time);
    Rtc_getDate(gregorian_date);
    KuwaitiHijriDate_calculate(julianDate, hijri_date);
    Led leds[3] = {
        {.group_index = 38, .index = 0},
        {.group_index = 39, .index = 0},
        {.group_index = 48, .index = 0}};
    leds[2].index = Rtc_getDay();
    Led_init();

    while (1)
    {
        swapHijriGregorianDate(digits, &leds[0].index);
        Rtc_getTime12H(&digits[8], &leds[1].index);
        Led_litLeds(leds);
        SevenSegments_writeDigits(digits);
    }
}