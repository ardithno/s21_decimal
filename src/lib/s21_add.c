#include "../s21_decimal.h"

int s21_add(s21_decimal first, s21_decimal second, s21_decimal *result_ptr) {
  _s21_big_decimal big_first = S21_DECIMAL_NULL;
  _s21_big_decimal big_second = S21_DECIMAL_NULL;
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&first, &big_first);
  _s21_decimal_to_big_decimal(&second, &big_second);

  big_result = _s21_big_decimal_add(&big_first, &big_second);

  return _s21_big_decimal_to_decimal(&big_result, result_ptr);
}
