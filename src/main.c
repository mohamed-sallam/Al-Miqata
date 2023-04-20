/* In the name of Allah, the Most Gracious, the Most Merciful */

#include <avr/io.h>

#include <seven_segments.h>
#include <prayer_times.h>


int main() 
{
    const double julianDate = 2460049.4132407387;
    const Settings settings = {
        .method_params = {
            .fajr_angle = 19.5,
            .dhuhr_minutes = 0,
            .asr_factor = 1,
            .maghrib_is_minutes = 1,
            .maghrib_value = 0,
            .isha_is_minutes = 0,
            .isha_value = 17.5,
        },
        .higher_latitudes_method = HigherLatitudesMethod_NONE,
        .time_format = TimeFormat_12hr_NO_SUFFIX,
        .latitude = 30.033333,
        .timezone_offset = -0.08222226666666677,
        .rise_set_angle = 0.833,
        .offsets_in_minutes = {0, 0, 0, 0, 0, 0, 0}
    };
    PrayerTimes_init(&settings);
    uint8_t digits[NUMBER_OF_DIGITS];
    PrayerTimes_get(julianDate, digits);
    
    SevenSegments_init();

    while (1) 
    {
        SevenSegments_writeDigits(digits);
    }
}