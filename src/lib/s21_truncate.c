#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int is_error = 0;

  s21_decimal current_value = value;
  current_value.bits[SCALE] = 0;

  uint32_t scale = _s21_get_scale(&value);
  while (scale != 0) {
    s21_decimal temp = S21_DECIMAL_NULL;
    s21_decimal ten_decimal = {.bits = {10, 0, 0, 0}};

    is_error = s21_mod(current_value, ten_decimal, &temp);
    is_error = s21_sub(current_value, temp, &temp);
    is_error = s21_div(temp, ten_decimal, &temp);

    for (int i = LOW; i <= HIGH; i++) {
      current_value.bits[i] = temp.bits[i];
    }

    scale--;
  }

  uint32_t sign = value.bits[SCALE] & 0x80000000;
  current_value.bits[SCALE] = current_value.bits[SCALE] | sign;

  *result = current_value;

  return (is_error != 0) ? 1: 0;
}
