#include "../s21_decimal.h"

int s21_is_equal(s21_decimal first, s21_decimal second) {
  // Zero edge case
  if (s21_is_zero(first) && s21_is_zero(second)) {
    return S21_TRUE;
  }

  // Non zero cases. Support same value decimals with different scale
  _s21_big_decimal big_first = S21_DECIMAL_NULL;
  _s21_big_decimal big_second = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&first, &big_first);
  _s21_decimal_to_big_decimal(&second, &big_second);

  return _s21_is_big_decimals_equal(&big_first, &big_second);
}
