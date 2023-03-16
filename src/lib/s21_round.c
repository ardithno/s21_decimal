#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int is_error = 0;

  uint32_t sign = value.bits[SCALE] & 0x80000000;

  s21_decimal current_value = value;
  current_value.bits[SCALE] = 0;

  uint32_t scale = _s21_get_scale(&value);

  int fl_round = 0;
  while (scale != 0) {
    s21_decimal temp = S21_DECIMAL_NULL;
    s21_decimal ten_decimal = {.bits = {10, 0, 0, 0}};

    is_error = s21_mod(current_value, ten_decimal, &temp);

    if (temp.bits[0] != 0 && scale != 1) {
      fl_round = 1;
    }

    if (scale == 1) {
      if (temp.bits[LOW] > 5 || (temp.bits[LOW] == 5 && fl_round == 1)) {
        s21_add(current_value, ten_decimal, &current_value);
      }
    }
    is_error = s21_sub(current_value, temp, &temp);
    is_error = s21_div(temp, ten_decimal, &temp);

    for (int i = LOW; i <= HIGH; i++) {
      current_value.bits[i] = temp.bits[i];
    }

    scale--;
  }

  current_value.bits[SCALE] = current_value.bits[SCALE] | sign;

  *result = current_value;

  return (is_error != 0) ? 1 : 0;
}
