#include "../s21_decimal.h"

void _reset_decimal_scale(s21_decimal *decimal) {
  // We reset scale here but save the sign
  decimal->bits[SCALE] &= 0x80000000;
}

_s21_big_decimal _copy_decimal_to_big(s21_decimal decimal) {
  _s21_big_decimal big = S21_DECIMAL_NULL;

  big.bits[BIG_SCALE] = decimal.bits[SCALE];

  for (int i = LOW; i < SCALE; i++) {
    big.bits[i] = decimal.bits[i];
  }

  return big;
}

_s21_big_decimal _save_dividend_as_big_scaled_30(s21_decimal dividend) {
  // Reset scale of the dividend (we will handle it manually)
  // And save the value as `big_decimal` with scale 30 (!!!)
  // It's needed for precision purpose
  _s21_big_decimal big_dividend = S21_DECIMAL_NULL;

  _reset_decimal_scale(&dividend);
  _s21_decimal_to_big_decimal(&dividend, &big_dividend);
  _s21_big_decimal_multiply_ten(&big_dividend);
  _s21_big_decimal_multiply_ten(&big_dividend);

  return big_dividend;
}

int s21_div(s21_decimal dividend, s21_decimal divisor,
            s21_decimal *result_ptr) {
  // What we do here:
  // 1. Multiply dividend to 10^30 (!!!) It's needed for result with enough
  //    precision
  // 2. Divide by divisor
  // 3. Convert resulted big decimal to decimal

  int is_error = 3;

  if (s21_is_zero(divisor)) return is_error;

  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  int dividend_scale = _s21_get_scale(&dividend);
  int divisor_scale = _s21_get_scale(&divisor);
  int result_scale = (30 - (28 - dividend_scale) + (28 - divisor_scale));

  _s21_big_decimal big_dividend = _save_dividend_as_big_scaled_30(dividend);
  _s21_big_decimal big_divisor = _copy_decimal_to_big(divisor);

  _s21_big_decimal_unsafe_div(big_dividend, big_divisor, &big_result, NULL);
  is_error = _s21_big_decimal_to_decimal(&big_result, &result, result_scale);

  if (!is_error) {
    *result_ptr = result;
  }

  return is_error;
}
