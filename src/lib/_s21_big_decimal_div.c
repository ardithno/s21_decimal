#include "../s21_decimal.h"

void _s21_big_decimal_set_bit(_s21_big_decimal *big_ptr, uint8_t bit_num) {
  uint8_t word_num = bit_num / 32;
  uint8_t bit_in_word_num = bit_num % 32;

  S21_BIT_SET(big_ptr->bits[word_num], bit_in_word_num);
}

uint32_t _s21_big_decimal_div(_s21_big_decimal const *dividend_ptr,
                              _s21_big_decimal const *divisor_ptr,
                              _s21_big_decimal *result_ptr) {
  // Long division algorithm in binary representation:
  //
  // 1. Find the quotient, which is the largest value equal to the divisor
  //    raised to the power of 2 that is less than or equal to the dividend.
  // 2. The exponent of 2 to which the divisor must be raised to get quotient
  //    equals the bit number with value of 1 in the result.
  // 3. Subtract the quotient from the dividend.
  // 4. Repeat until the divisor is greater than the dividend."
  //
  // If `reminder_ptr` is not NULL than save the remainder after division

  _s21_big_decimal dividend = *dividend_ptr;
  _s21_big_decimal divisor = *divisor_ptr;
  _s21_big_decimal result = S21_DECIMAL_NULL;

  int dividend_sign = _s21_big_decimal_get_sign(&dividend);
  int divisor_sign = _s21_big_decimal_get_sign(&divisor);

  if (dividend_sign == 1) _s21_big_decimal_change_sign(&dividend);
  if (divisor_sign == 1) _s21_big_decimal_change_sign(&divisor);

  while (_s21_big_decimal_compare_bits(&divisor, &dividend) != -1) {
    _s21_big_decimal quotient = divisor;
    uint8_t one_bit_num_in_result = 1;

    int compare = _s21_big_decimal_compare_bits(&dividend, &divisor);

    while (compare == -1) {
      _s21_big_decimal temp = quotient;
      _s21_big_decimal_shift_left(&temp);
      compare = _s21_big_decimal_compare_bits(&dividend, &temp);

      if (compare == -1 || compare == 0) {
        one_bit_num_in_result++;
        quotient = temp;
      }
    }

    dividend = _s21_big_decimal_sub(&dividend, &quotient);

    _s21_big_decimal_set_bit(&result, one_bit_num_in_result - 1);
  }

  if (dividend_sign != divisor_sign) _s21_big_decimal_change_sign(&result);

  *result_ptr = result;
  // if (reminder_ptr != NULL) *reminder_ptr = dividend;

  // We should return error if division by Zero here
  // return 0;

  return dividend.bits[LOW];
}