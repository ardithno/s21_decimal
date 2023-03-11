#include "../s21_decimal.h"

int s21_mul(s21_decimal first, s21_decimal second, s21_decimal *result_ptr) {
  s21_decimal result = S21_DECIMAL_NULL;
  int is_error = 0;  // No errors by default

  _s21_big_decimal big_first = S21_DECIMAL_NULL;
  _s21_big_decimal big_second = S21_DECIMAL_NULL;
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  big_first = _s21_decimal_copy_to_big_decimal(first);
  big_second = _s21_decimal_copy_to_big_decimal(second);

  int first_scale = _s21_get_scale(&first);
  int second_scale = _s21_get_scale(&second);
  int result_scale = first_scale + second_scale;

  // Overflow may happen on this step
  is_error = _s21_big_decimal_mul(&big_first, &big_second, &big_result);

  if (!is_error) {
    is_error = _s21_big_decimal_to_decimal(&big_result, &result, result_scale);
  }

  if (!is_error) {
    *result_ptr = result;
  }

  return is_error;
}
