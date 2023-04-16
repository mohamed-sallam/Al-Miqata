#include "dtrig.h"

#include "math.h"


double dsin(double d)
{
    return sin(deg2rad(d));
}

double dcos(double d)
{
    return cos(deg2rad(d));
}

double dtan(double d)
{
    return tan(deg2rad(d));
}

double darcsin(double x)
{
    return rad2deg(asin(x));
}

double darccos(double x)
{
    return rad2deg(acos(x));
}

double darctan2(double y, double x)
{
    return rad2deg(atan2(y, x));
}

double darccot(double x)
{
    return rad2deg(atan(1.0 / x));
}

double deg2rad(double d)
{
    return d * M_PI / 180.0;
}

double rad2deg(double r)
{
    return r * 180.0 / M_PI;
}

double fix(double a, uint16_t b)
{
    a = a - b * ((int)(a / b));
    return (a < 0) ? a + b : a;
}

double fix_angle(double a)
{
    return fix(a, 360);
}

double fix_hour(double a)
{
    return fix(a, 24);
}

double time_diff(double time1, double time2) 
{
    return fix_hour(time2 - time1);
}
