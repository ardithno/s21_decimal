#include <stdio.h>

#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }

  if (0 < fabs(src) && fabs(src) < 1e-28) {
    error = 1;
  } else if (0 < fabs(src) && fabs(src) < 1) {
    int src_new = roundl(src * (pow(10, 7)));
    s21_from_int_to_decimal(src_new, dst);
    s21_set_power(dst, 7);
  } else if (fabs(src) < 1000000) {
    int sign = 0;
    int scale = 6;
    if (src < 0) {
      sign = 1;
      src = -src;
    }
    double src_new = src;
    while (!(src_new < 10)) {
      src_new /= 10;
      scale--;
    }
    src_new = roundl(src * pow(10, scale));
    s21_from_int_to_decimal(src_new, dst);
    s21_set_power(dst, scale);
    if (sign == 1) {
      s21_change_sign(dst);
    }

  } else if (fabs(src) < MAX_DECIMAL) {
    int exponent = s21_get_exp(src);
    int mantissa = s21_get_mantissa(src);
    dst->bits[0] = mantissa;
    S21_BIT_SET(dst->bits[0], 23);
    s21_left_shift(dst, exponent - 23);
    if (src < 0) s21_change_sign(dst);
  } else {
    error = 1;
  }
  return error;
}
