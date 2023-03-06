#include "../s21_decimal.h"

void _reset_decimal_scale(s21_decimal *decimal) { decimal->bits[SCALE] = 0; }

void _represent_decimal_as_big_decimal(s21_decimal const *decimal,
                                       _s21_big_decimal *big_ptr) {
  _s21_big_decimal big_empty = S21_DECIMAL_NULL;

  *big_ptr = big_empty;

  for (int i = LOW; i < SCALE; i++) {
    big_ptr->bits[i] = decimal->bits[i];
  }
}

_s21_big_decimal stupid_div(_s21_big_decimal dividend,
                            _s21_big_decimal divisor) {
  // It's stupid long division algorithm
  // We don't check a sign or overflow here.
  // You should do something with that because it almost the same
  // that used in `reduce_scale`.
  _s21_big_decimal result = S21_DECIMAL_NULL;

  while (_s21_big_decimal_compare_bits(&divisor, &dividend) != -1) {
    _s21_big_decimal quotient = divisor;
    uint8_t one_bit_num_in_result = 0;

    int compare = _s21_big_decimal_compare_bits(&dividend, &divisor);

    while (compare == -1) {
      _s21_big_decimal temp_quotient = quotient;
      _s21_big_decimal_shift_left(&temp_quotient);
      compare = _s21_big_decimal_compare_bits(&dividend, &temp_quotient);

      if (compare == -1 || compare == 0) {
        one_bit_num_in_result++;
        quotient = temp_quotient;
      }
    }

    dividend = _s21_big_decimal_sub(&dividend, &quotient);
    _s21_big_decimal_set_bit(&result, one_bit_num_in_result);
  }

  return result;
}

int s21_div(s21_decimal dividend, s21_decimal divisor,
            s21_decimal *result_ptr) {
  // What we do here:
  // 1. Multiply dividend to 10^29 (!!!) It's needed for result with enough
  //    precision
  // 2. Divide by divisor
  // 3. Convert resulted big decimal to decimal

  int is_error = 3;

  if (s21_is_zero(divisor)) return is_error;

  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big_dividend = S21_DECIMAL_NULL;
  _s21_big_decimal big_divisor = S21_DECIMAL_NULL;
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  int dividend_scale = _s21_get_scale(&dividend);
  int dividend_sign = s21_get_sign(dividend);

  int divisor_scale = _s21_get_scale(&divisor);
  int divisor_sign = s21_get_sign(divisor);

  // We reset scale to the dividend (we will handle it manually)
  // And save it as `big_decimal` with scale 29 (!!!)
  // It's needed for precision purpose
  _reset_decimal_scale(&dividend);
  _s21_decimal_to_big_decimal(&dividend, &big_dividend);
  _s21_big_decimal_multiply_ten(&big_dividend);

  // Divisor used `as is` but as big_decimal.
  _represent_decimal_as_big_decimal(&divisor, &big_divisor);

  big_result = stupid_div(big_dividend, big_divisor);
  if (dividend_sign != divisor_sign) _s21_big_decimal_change_sign(&big_result);

  // The initial scale is 29 because the dividend used with that scale
  int result_scale = (29 - (28 - dividend_scale) + (28 - divisor_scale));

  is_error = _s21_big_decimal_to_decimal(&big_result, &result, result_scale);

  if (!is_error) {
    *result_ptr = result;
  }

  return is_error;
}
