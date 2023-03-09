#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return convertation_error;
  }

  int err = convertation_ok;
  s21_truncate(src, &src);
  int numSign = s21_get_sign(src);

  if (src.bits[1] || src.bits[2] || src.bits[3] ||
      (numSign && src.bits[0] > MIN_INT) ||
      (!numSign && src.bits[0] > MAX_INT)) {
    err = convertation_error;
  }

  *dst = src.bits[0];
  if (numSign)
    *dst *= -1;

  return err;
}