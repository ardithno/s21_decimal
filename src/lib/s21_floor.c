#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int is_error = 0;

  uint32_t sign = value.bits[SCALE] & 0b10000000000000000000000000000000;
  uint32_t signCheck = sign >> 31;

  s21_decimal currentValue = S21_DECIMAL_NULL;
  for (int i = LOW; i <= HIGH; i++) {
    currentValue.bits[i] = value.bits[i];
  }
  currentValue.bits[SCALE] = 0;

  uint32_t scale = _s21_get_scale(&value);
  while (scale != 0) {
    s21_decimal temp = S21_DECIMAL_NULL;
    s21_decimal tenDecimal = {.bits = {10, 0, 0, 0}};

    is_error = s21_mod(currentValue, tenDecimal, &temp);
    if (scale == 1) {
      if (signCheck == 1 && temp.bits[LOW] != 0) {
        s21_add(currentValue, tenDecimal, &currentValue);
      }
    }
    is_error = s21_sub(currentValue, temp, &temp);
    is_error = s21_div(temp, tenDecimal, &temp);

    for (int i = LOW; i <= HIGH; i++) {
      currentValue.bits[i] = temp.bits[i];
    }

    scale--;
  }

  currentValue.bits[SCALE] = currentValue.bits[SCALE] | sign;

  *result = currentValue;

  return (is_error != 0) ? 1: 0;
}
