#include "../s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
  int flag = S21_FALSE;

  if (s21_is_equal(first, second) == S21_FALSE) {
    _s21_big_decimal big_first = S21_DECIMAL_NULL;
    _s21_big_decimal big_second = S21_DECIMAL_NULL;

    _s21_decimal_to_big_decimal(&first, &big_first);
    _s21_decimal_to_big_decimal(&second, &big_second);

    if (_s21_big_decimal_compare(&big_first, &big_second) == 1) {
      flag = S21_TRUE;
    }
  }

  return flag;
}