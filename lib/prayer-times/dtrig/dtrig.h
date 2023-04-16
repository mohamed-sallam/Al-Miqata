/* In the name of Allah, the Most Gracious, the Most Merciful */

#pragma once 

#include <stdint.h>

/* ---------------------- Trigonometric Functions ----------------------- */
/* degree sin */
double dsin(double d);

/* degree cos */
double dcos(double d);

/* degree tan */
double dtan(double d);

/* degree arcsin */
double darcsin(double x);

/* degree arccos */
double darccos(double x);

/* degree arctan2 */
double darctan2(double y, double x);

/* degree arccot */
double darccot(double x);

/* degree to radian */
double deg2rad(double d);

/* radian to degree */
double rad2deg(double r);

double fix(double a, uint16_t b);

/* range reduce angle in degrees. */
double fix_angle(double a);

/* range reduce hours to 0..23 */
double fix_hour(double a);


/* ---------------------- Misc Functions ----------------------- */
/* compute the difference between two times */
double time_diff(double time1, double time2) ;
