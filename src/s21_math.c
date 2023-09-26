#include "s21_math.h"

long double s21_pow(double a,
                    double b) {
  long double znak = 1.0;
  long double x = a;
  long double y = b;
  if (x < 0 && y == (int)y) {
    x = -x;
    znak = -1.0;
    if ((int)y % 2 == 0) znak *= -1.0;
  }
  return y == 0 ? 1 : x == 0 ? 0 : znak * s21_exp(y * s21_log(x));
}
long double s21_ceil(double a) {
  long double x = a;
  return x - (long long int)a > 0 ? x - (x - (long long int)a) + 1
                                  : x - (x - (long long int)a);
}

long double s21_floor(double a) {
  long double x = a;
  return x - (int)x > 0 ? x - (x - (int)x) : x - (int)x < 0 ? (int)x - 1 : x;
}

int s21_abs(int a) {
  if (a < 0) a = -a;
  return a;
}

long double s21_sqrt(double a) {
  double t = 0, sqrt = a / 2;
  if (a > 0) {
    while ((t - sqrt) != 0) {
      t = sqrt;
      sqrt = (t + (a / t)) / 2;
    }
  }
  return a < 0 ? s21_NAN : sqrt;
}

long double s21_fabs(double a) {
  if (a < 0.0) a = -a;
  return a;
}

long double s21_exp(double a) {
  long double res, t;
  long double b = a;
  int znak = 0;
  if (b < 0) {
    b = -b;
    znak = -1;
  }
  int n = 1;
  for (res = 1.0, t = 1.0; s21_fabs(t) > s21_E; n++) {
    t *= b / n;
    res += t;
    if (res > s21_MAX_double) {
      res = s21_INF;
      break;
    }
  }
  return res != s21_INF ? znak == -1 ? 1 / res : res : s21_INF;
}

long double s21_fmod(
    double a,
    double b) {
  int metka_a = 0, metka_b = 0;
  if (a < 0) {
    metka_a = 1;
  }
  if (b < 0) {
    metka_b = 1;
  }
  if (metka_b == 1) {
    b = b * (-1);
  }
  if (metka_a == 1) {
    a = a * (-1);
  }
  double n = s21_floor(a / b);
  double result = a - n * b;
  if (metka_a == 1) {
    result = result * (-1);
  }
  return result;
}

long double s21_factorial(double a) {
  double res = 1;
  for (int i = 1; i <= a; i++) {
    res *= i;
  }
  return res;
}

void round_to_pi(double *a) {
  while (s21_fabs(*a) > (2.0 * s21_PI)) {
    if (*a < 0)
      *a = *a + (2.0 * s21_PI);
    else
      *a = *a - (2.0 * s21_PI);
  }
}
long double s21_sin(double a) {
  if (s21_fabs(a) <= 0.000001) a = 0.0;
  round_to_pi(&a);
  long double res = 0.0, n = 0.0, an = 1.0;
  while (!(an >= -s21_E && an <= s21_E)) {
    an = s21_pow(-1, n) * s21_pow(a, 2 * n + 1) / s21_factorial(2 * n + 1);
    res += an;
    n++;
  }
  return res;
}

long double s21_cos(double a) {
  if (s21_fabs(a) <= 0.000001) a = 0.0;
  round_to_pi(&a);
  long double res = 1.0, n = 1.0, an = 1.0;
  while (!(an >= -s21_E && an <= s21_E)) {
    an *= (-1.0) * a * a / ((2.0 * n - 1.0) * (2.0 * n));
    res += an;
    n++;
  }
  return res;
}
long double s21_tan(double a) {
  return s21_sin(a) / s21_cos(a);
}
long double s21_asin(double a) {
  int metka = 0;
  if (a < 0 && a != -1) {
    a = a * -1;
    metka = 1;
  }
  long double n = 1, x = a, s = 1, res = a;
  if (a < 1 && a > -1) {
    while (s > s21_E) {
      x = a * a * (x * (2 * n - 1)) / (2 * n);
      s = x / (2 * n + 1);
      res = res + s;
      n++;
    }
    if (metka == 1) {
      res = res * -1;
    }
  } else if (a == 1) {
    res = s21_PI / 2;
  } else if (a == -1) {
    res = -s21_PI / 2;
  } else if (a == 0) {
    res = 0;
  } else {
    res = s21_NAN;
  }
  return res;
}

long double s21_acos(double a) {
  long double res = 0;
  if (a < 1 && a > -1) {
    res = s21_PI / 2 - s21_asin(a);
  } else if (a == 1) {
    res = 0;
  } else if (a == -1) {
    res = s21_PI;
  } else {
    res = s21_NAN;
  }
  return res;
}

long double s21_atan(double a) {
  return s21_asin(a / s21_sqrt(1 + (a * a)));
}

long double s21_log(double a) {
  long double result;
  if (a == 1)
    result = 0;
  else if (a == 0)
    result = -s21_INF;
  else if (a < 0) {
    result = s21_NAN;
  } else {
    if (a > 0 && a < 1) {
      result = p_log(a);
    } else {
      long double res = 0.0, term = (a - 1) / a;
      long long denominator = 2;
      long double temp = term;
      unsigned int count = 0;
      while (temp > s21_E) {
        res += temp;
        term *= (a - 1) / a;
        temp = term * (1.0 / denominator);
        denominator += 1;
        count++;
      }
      result = res;
    }
  }
  return result;
}

long double p_log(double a) {
  a--;
  long double r = a, t = a;
  long double i = 2;
  while (s21_fabs(r) > s21_E) {
    r *= -a * (i - 1) / i;
    i += 1;
    t += r;
  }
  return t;
}
