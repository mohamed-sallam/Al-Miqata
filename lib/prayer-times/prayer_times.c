#include "prayer_times.h"

#include "dtrig/dtrig.h"

const Settings* _settings;
double _julian_date;

void PrayerTimes_init(const Settings* const settings) {
    _settings = settings;
}

void PrayerTimes_get(double julianDate, uint8_t output[6][4]) {
    _julian_date = julianDate;

    double times[_TIMES_COUNT] = {5, 6, 12, 13, 18, 18, 18};
    _compute_times(times);
    _modify_formats(times, output);
}


/* ---------------------- Compute Prayer Times ----------------------- */
/* compute prayer times */
void _compute_times(double output[_TIMES_COUNT]) 
{
    _compute_prayer_times(output);
    _adjust_times(output);
    _tune_times(output);
}

/* compute prayer times at given julian date */
void _compute_prayer_times(double output[_TIMES_COUNT])
{
    _day_portion(output);

    output[_TimeName_FAJR]    = _sun_angle_time(_settings->method_params.fajr_angle, output[_TimeName_FAJR], _Direction_COUNTERCLOCKWISE);
    output[_TimeName_SUNRISE] = _sun_angle_time(_settings->rise_set_angle, output[_TimeName_SUNRISE], _Direction_COUNTERCLOCKWISE);
    output[_TimeName_DHUHR]   = _compute_mid_day(output[_TimeName_DHUHR]);
    output[_TimeName_ASR]     = _compute_asr(_settings->method_params.asr_factor, output[_TimeName_ASR]);
    output[_TimeName_SUNSET]  = _sun_angle_time(_settings->rise_set_angle, output[_TimeName_SUNSET], _Direction_CLOCKWISE);
    output[_TimeName_MAGHRIB] = _sun_angle_time(_settings->method_params.maghrib_value, output[_TimeName_MAGHRIB], _Direction_CLOCKWISE);
    output[_TimeName_ISHA]    = _sun_angle_time(_settings->method_params.isha_value, output[_TimeName_ISHA], _Direction_CLOCKWISE);
}

/* adjust times in a prayer time array */
void _adjust_times(double output[_TIMES_COUNT])
{
    for (uint8_t i = 0; i < _TIMES_COUNT; ++i)
        output[i] += _settings->timezone_offset;

    if (_settings->higher_latitudes_method != HigherLatitudesMethod_NONE)
        _adjust_higher_latitudes_times(output);

    output[_TimeName_DHUHR] += _settings->method_params.dhuhr_minutes / 60.0;		/* Dhuhr */
    
    if (_settings->method_params.maghrib_is_minutes)		                        /* Maghrib */
        output[_TimeName_MAGHRIB] = output[_TimeName_SUNSET] + _settings->method_params.maghrib_value / 60.0;
    
    if (_settings->method_params.isha_is_minutes)		                            /* Isha */
        output[_TimeName_ISHA] = output[_TimeName_MAGHRIB] + _settings->method_params.isha_value / 60.0;
}

/* apply offsets to the times */
void _tune_times(double output[_TIMES_COUNT]) 
{
    for (uint8_t i = 0; i < _TIMES_COUNT; ++i)
        output[i] += _settings->offsets_in_minutes[i] / 60.0;
}

/* convert times to given time format */
void _modify_formats(double timesInFloat[_TIMES_COUNT], uint8_t output[6][4]) 
{
    _get_formated_time(timesInFloat[_TimeName_FAJR], output[0]);
    _get_formated_time(timesInFloat[_TimeName_SUNRISE], output[1]);
    _get_formated_time(timesInFloat[_TimeName_DHUHR], output[2]);
    _get_formated_time(timesInFloat[_TimeName_ASR], output[3]);
    _get_formated_time(timesInFloat[_TimeName_MAGHRIB], output[4]);
    _get_formated_time(timesInFloat[_TimeName_ISHA], output[5]);
}

/* adjust times for locations in higher latitudes */
void _adjust_higher_latitudes_times(double output[_TIMES_COUNT])
{
    double night_time = time_diff(output[_TimeName_SUNSET], output[_TimeName_SUNRISE]);

    output[_TimeName_FAJR] = _adjust_higher_latitudes_time(output[_TimeName_FAJR], output[_TimeName_SUNRISE], _settings->method_params.fajr_angle, night_time, _Direction_COUNTERCLOCKWISE);
    output[_TimeName_MAGHRIB] = _adjust_higher_latitudes_time(output[_TimeName_MAGHRIB], output[_TimeName_SUNSET], _settings->method_params.maghrib_value, night_time, _Direction_CLOCKWISE);
    output[_TimeName_ISHA] = _adjust_higher_latitudes_time(output[_TimeName_ISHA], output[_TimeName_SUNSET], _settings->method_params.isha_value, night_time, _Direction_CLOCKWISE);
}

/* adjust a time for higher latitudes */
double _adjust_higher_latitudes_time(double time, double base, double angle, double night, _Direction direction)
{
    double portion = _night_portion(angle, night);
    double timediff = (direction == _Direction_COUNTERCLOCKWISE) ?
                      time_diff(time, base):
                      time_diff(base, time);
    if (isnan(time) || timediff > portion)
        time = base + direction * portion;
    return time;
}

/* the night portion used for adjusting times in higher latitudes */
double _night_portion(double angle, double night)
{
    switch (_settings->higher_latitudes_method)
    {
    case HigherLatitudesMethod_NIGHT_MIDDLE:
        return 0.5 * night;
    case HigherLatitudesMethod_ANGLE_BASED:
        return (1.0 / 60.0 * angle) * night;
    case HigherLatitudesMethod_ONE_SEVENTH:
        return (1.0 / 7.0) * night;
    default:
        __builtin_unreachable();
    }
}

/* convert hours to day portions  */
void _day_portion(double output[])
{
    for (uint8_t i = 0; i < _TIMES_COUNT; ++i)
        output[i] /= 24.0;
}


/* ---------------------- Calculation Functions ----------------------- */
/* References: */
/* http://www.ummah.net/astronomy/saltime   */
/* http://aa.usno.navy.mil/faq/docs/SunApprox.html */
/* compute declination angle of sun and equation of time */
_SunPosition _sun_position(double jd)
{
    double d = jd - 2451545.0;
    double g = fix_angle(357.529 + 0.98560028 * d);
    double q = fix_angle(280.459 + 0.98564736 * d);
    double l = fix_angle(q + 1.915 * dsin(g) + 0.020 * dsin(2 * g));

    double e = 23.439 - 0.00000036 * d;

    double ra = darctan2(dcos(e) * dsin(l), dcos(l)) / 15.0;
    double eq_t = q / 15.0 - fix_hour(ra);
    double dd = darcsin(dsin(e) * dsin(l));
    _SunPosition result = {.declination = dd, 
                          .equation    = eq_t};
    return result;
}

/* compute mid-day (Dhuhr, Zawal) time */
double _compute_mid_day(double time)
{
    double eqt = _sun_position(_julian_date + time).equation;
    double noon = fix_hour(12 - eqt);
    return noon;
}

/* compute the time at which sun reaches a specific angle below horizon */
double _sun_angle_time(double angle, double time, _Direction direction) 
{
    double decl = _sun_position(_julian_date + time).declination;
    double noon = _compute_mid_day(time);
    double t = 1 / 15.0 * darccos((-dsin(angle) - dsin(decl) * dsin(_settings->latitude)) / (dcos(decl) * dcos(_settings->latitude)));
    return noon + (direction * t);
}

/* compute the time of Asr */
double _compute_asr(uint8_t factor, double time) 
{
    double decl = _sun_position(_julian_date + time).declination;
    double angle = -darccot(factor + dtan(fabs(_settings->latitude - decl)));
    return _sun_angle_time(angle, time, _Direction_CLOCKWISE);
}


/* ---------------------- Format Functions ----------------------- */
/* convert float time to the given format (see timeFormats) */
/* ex: 16.5 (i.e., 4:30PM) -> [_get_formated_time] -> {0, 3, 4, 0} */
void _get_formated_time(double time, uint8_t output[4]) 
{
    if (isnan(time))
    {
        /*                               E   R   R   O */
        const uint8_t invalid_time[4] = {10, 11, 11, 0};
        output = invalid_time;
        return;
    }
    
    time = fix_hour(time + 0.5 / 60); /* add 0.5 minutes to round */
    uint8_t hours = time;
    uint8_t minutes = (time - hours) * 60;

    /* Minutes digits */
    output[0] = minutes % 10;
    output[1] = (minutes / 10) % 10;

    /* Hours digits */
    if (_settings->time_format == TimeFormat_12hr_NO_SUFFIX)
        hours = (hours + 12 - 1) % 12 + 1;
    output[2] = hours % 10;
    output[3] = (hours / 10) % 10;
}
