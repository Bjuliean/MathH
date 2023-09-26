#ifndef _S21_MATH_
#define _S21_MATH_

#include <stdio.h>
#define s21_PI 3.141592653589793238462643
#define s21_E 1e-17
#define s21_NAN 0.0 / 0.0
#define s21_INF 1.0 / 0.0
#define s21_MAX_double 1.7976931348623157e308

long double s21_pow(double a, double b);
long double s21_ceil(double a);
long double s21_floor(double a);
int s21_abs(int a);
long double s21_sqrt(double a);
long double s21_fabs(double a);
long double s21_exp(double a);
long double s21_fmod(double a, double b);
long double s21_factorial(double a);
long double s21_sin(double a);
long double s21_cos(double a);
long double s21_tan(double a);
long double s21_asin(double a);
long double s21_acos(double a);
long double s21_atan(double a);
long double s21_log(double a);

void round_to_pi(double *a);
long double p_log(double a);

#endif  // _S21_MATH_
