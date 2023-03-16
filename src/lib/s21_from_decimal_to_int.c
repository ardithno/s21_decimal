#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int scale = _s21_get_scale(&src);
  long double num = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      int res = s21_get_bit(src, i * 32 + j);
      if (res == 1) {
        num += pow(2, i * 32 + j);
      }
    }
  }
  while (scale != 0) {
    num /= 10;
    scale--;
  }

  if (s21_get_sign(src) != 0) {
    num = -num;
  }

  if (num > 2147483647 || num < -2147483648 || dst == NULL) {
    error = 1;
  } else {
    *dst = (int)num;
  }
  return error;
}