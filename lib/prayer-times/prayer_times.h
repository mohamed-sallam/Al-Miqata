/* In the name of Allah, the Most Gracious, the Most Merciful */

#pragma once

#include <stdint.h>
#include "../../inc/types.h"

typedef enum __attribute__((packed))
{
    TimeFormat_24hr = 0,
    TimeFormat_12hr_NO_SUFFIX = 1
} TimeFormat;

typedef enum __attribute__((packed))
{
    HigherLatitudesMethod_NONE = 0,
    HigherLatitudesMethod_NIGHT_MIDDLE = 1,
    HigherLatitudesMethod_ONE_SEVENTH = 2,
    HigherLatitudesMethod_ANGLE_BASED = 3
} HigherLatitudesMethod;

typedef enum __attribute__((packed))
{
    _TimeName_FAJR = 0,
    _TimeName_SUNRISE = 1,
    _TimeName_DHUHR = 2,
    _TimeName_ASR = 3,
    _TimeName_SUNSET = 4,
    _TimeName_MAGHRIB = 5,
    _TimeName_ISHA = 6,

    _TIMES_COUNT
} _TimeName;

typedef enum __attribute__((packed))
{
    _Direction_COUNTERCLOCKWISE = -1,
    _Direction_CLOCKWISE = 1
} _Direction;

typedef struct __attribute__((packed))
{
    double fajr_angle;
    double dhuhr_minutes;
    uint8_t asr_factor;
    boolean maghrib_is_minutes;
    double maghrib_value; /* angle or minutes */
    boolean isha_is_minutes;
    double isha_value; /* angle or minutes */
} AdjustingParams;

typedef struct __attribute__((packed))
{
    AdjustingParams method_params;
    HigherLatitudesMethod higher_latitudes_method;
    TimeFormat time_format;
    double latitude;
    double timezone_offset; /* timezone offset = local timezone with dst - longitude / 15.0 */
    double rise_set_angle;  /* = 0.833 */
    uint8_t offsets_in_minutes[_TIMES_COUNT];
} Settings;

typedef struct __attribute__((packed))
{
    double declination;
    double equation;
} _SunPosition;


void PrayerTimes_init(const Settings *const settings);
void PrayerTimes_get(double julianDate, uint8_t output[6][4]);

/* ---------------------- Private ---------------------- */
/* ---------------------- Compute Prayer Times ----------------------- */
/* compute prayer times */
void _compute_times(double output[_TIMES_COUNT]);
/* compute prayer times at given julian date */
void _compute_prayer_times(double output[_TIMES_COUNT]);
/* adjust times in a prayer time array */
void _adjust_times(double output[_TIMES_COUNT]);
/* apply offsets to the times */
void _tune_times(double output[_TIMES_COUNT]);
/* convert times to given time format */
void _modify_formats(double timesInFloat[_TIMES_COUNT], uint8_t output[6][4]);
/* adjust times for locations in higher latitudes */
void _adjust_higher_latitudes_times(double output[_TIMES_COUNT]);
/* adjust a time for higher latitudes */
double _adjust_higher_latitudes_time(double time, double base, double angle, double night, _Direction direction);
/* the night portion used for adjusting times in higher latitudes */
double _night_portion(double angle, double night);
/* convert hours to day portions  */
void _day_portion(double output[]);

/* ---------------------- Calculation Functions ----------------------- */
/* References: */
/* http://www.ummah.net/astronomy/saltime   */
/* http://aa.usno.navy.mil/faq/docs/SunApprox.html */
/* compute declination angle of sun and equation of time */
_SunPosition _sun_position(double jd);
/* compute mid-day (Dhuhr, Zawal) time */
double _compute_mid_day(double time);
/* compute the time at which sun reaches a specific angle below horizon */
double _sun_angle_time(double angle, double time, _Direction direction);
/* compute the time of Asr */
double _compute_asr(uint8_t factor, double time);

/* ---------------------- Format Functions ----------------------- */
/* convert float time to the given format (see timeFormats) */
/* ex: 16.5 (i.e., 4:30PM) -> [_get_formated_time] -> {0, 3, 4, 0} */
void _get_formated_time(double time, uint8_t output[4]);
