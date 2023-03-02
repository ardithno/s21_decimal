#include "../s21_decimal.h"

int _is_extra_bits_not_empty(_s21_big_decimal *big_decimal_ptr) {
  // Return S21_TRUE if upper big decimal's bytes that don't fit in decimal is
  // NOT empty (not equals zero).
  int num_empty_bits = 0;

  for (int i = SCALE; i < BIG_SCALE; i++) {
    if (big_decimal_ptr->bits[i] == 0) {
      num_empty_bits++;
    } else {
      break;
    }
  }

  return (num_empty_bits != BIG_SCALE - SCALE) ? S21_TRUE : S21_FALSE;
}

void _s21_big_decimal_set_bit(_s21_big_decimal *big_ptr, uint8_t bit_num) {
  uint8_t word_num = bit_num / 32;
  uint8_t bit_in_word_num = bit_num % 32;

  S21_BIT_SET(big_ptr->bits[word_num], bit_in_word_num);
}

uint8_t _s21_big_decimal_reduce_scale(_s21_big_decimal const *dividend_ptr,
                                      _s21_big_decimal *result_ptr) {
  // Reduce big_decimal scale
  //
  // It's actually the long division algorithm in binary representation:
  //
  // 1. Find the quotient, which is the largest value equal to the divisor
  //    raised to the power of 2 that is less than or equal to the dividend
  // 2. Set bit in result
  // 3. Subtract the quotient from the dividend
  // 4. Repeat until the divisor is greater than the dividend
  // 5. Return reminder. It's always less than 10 in binary representation

  _s21_big_decimal dividend = *dividend_ptr;
  _s21_big_decimal divisor = {.bits = {10, 0, 0, 0, 0, 0, 0}};  // ten as big
  _s21_big_decimal result = S21_DECIMAL_NULL;

  int dividend_sign = _s21_big_decimal_get_sign(&dividend);
  if (dividend_sign == 1) _s21_big_decimal_change_sign(&dividend);

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

  if (dividend_sign == 1) _s21_big_decimal_change_sign(&result);

  *result_ptr = result;
  return (uint8_t)dividend.bits[LOW];
}

s21_decimal _s21_convert_suitable_big_decimal_to_decimal(
    _s21_big_decimal const *big_decimal_ptr, uint8_t scale) {
  s21_decimal result = S21_DECIMAL_NULL;

  for (int i = LOW; i < SCALE; i++) {
    result.bits[i] = big_decimal_ptr->bits[i];
  }

  result.bits[SCALE] |= (uint32_t)scale << 16;
  result.bits[SCALE] |= big_decimal_ptr->bits[BIG_SCALE] & 0x80000000;

  return result;
}

int _s21_big_decimal_to_decimal(_s21_big_decimal const *big_decimal_ptr,
                                s21_decimal *decimal_ptr) {
  _s21_big_decimal big = *big_decimal_ptr;

  int scale = 28;
  // int desirable_scale = _s21_big_decimal_get_scale(big_decimal_ptr);
  uint8_t reminder = 0;
  int is_error = 0;

  while (_is_extra_bits_not_empty(&big) && scale > 0) {
    reminder = _s21_big_decimal_reduce_scale(&big, &big);
    scale--;
  }

  if (reminder > 5 || (reminder == 5 && big.bits[LOW] & 1)) {
    _s21_big_decimal one_as_big = {{1, 0, 0, 0, 0, 0, big.bits[BIG_SCALE]}};
    big = _s21_big_decimal_add(&big, &one_as_big);
  }

  is_error = _is_extra_bits_not_empty(&big);

  if (!is_error) {
    *decimal_ptr = _s21_convert_suitable_big_decimal_to_decimal(&big, scale);
  }

  return is_error;
}
