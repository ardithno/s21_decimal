#include "../s21_decimal.h"

void _s21_big_decimal_unsafe_div(_s21_big_decimal dividend,
                                 _s21_big_decimal divisor,
                                 _s21_big_decimal *result_ptr,
                                 _s21_big_decimal *reminder_ptr) {
  // Unsafe big_decimal long division algorithm
  // We don't handle possible overflow here. Do it manually outside.
  _s21_big_decimal result = S21_DECIMAL_NULL;

  int dividend_sign = _s21_big_decimal_get_sign(&dividend);
  int divisor_sign = _s21_big_decimal_get_sign(&divisor);

  if (dividend_sign) _s21_big_decimal_change_sign(&dividend);
  if (divisor_sign) _s21_big_decimal_change_sign(&divisor);

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

    _s21_big_decimal_set_bit(&result, one_bit_num_in_result);
    dividend = _s21_big_decimal_sub(&dividend, &quotient);
  }

  if (dividend_sign != divisor_sign) _s21_big_decimal_change_sign(&result);

  if (result_ptr != NULL) *result_ptr = result;
  if (reminder_ptr != NULL) *reminder_ptr = dividend;
}
