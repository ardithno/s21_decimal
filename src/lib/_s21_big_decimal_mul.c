#include "../s21_decimal.h"

uint8_t _big_decimal_get_bit(_s21_big_decimal const *big_ptr, int bit_num) {
  uint8_t word_num = bit_num / 32;
  uint8_t bit_num_in_word = bit_num % 32;

  uint32_t temp = big_ptr->bits[word_num] & (uint32_t)(1ULL << bit_num_in_word);

  return (temp == 0) ? 0 : 1;
}

uint8_t _is_big_overflowed(_s21_big_decimal const *big_ptr) {
  int pre_scale_bit_value = big_ptr->bits[BIG_SCALE - 1];
  return (pre_scale_bit_value == 0) ? S21_FALSE : S21_TRUE;
}

uint8_t _big_decimal_shift_left_n(_s21_big_decimal *big_ptr, int n) {
  // Shift big decimal left n times
  // Overflow may happen. If happened return error
  uint8_t is_error = S21_FALSE;

  for (int j = 1; (j <= n) && (is_error == S21_FALSE); j++) {
    _s21_big_decimal_shift_left(big_ptr);
    is_error = _is_big_overflowed(big_ptr);
  }

  return is_error;
}

int _s21_big_decimal_mul(_s21_big_decimal const *first_ptr,
                         _s21_big_decimal const *second_ptr,
                         _s21_big_decimal *result_ptr) {
  _s21_big_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal first = *first_ptr;
  _s21_big_decimal second = *second_ptr;

  int is_error = 0;  // No error by default

  int first_sign = _s21_big_decimal_get_sign(&first);
  if (first_sign) _s21_big_decimal_change_sign(&first);

  int second_sign = _s21_big_decimal_get_sign(&second);
  if (second_sign) _s21_big_decimal_change_sign(&second);

  // Do multiplication by shifting left
  for (int bit_num = 0; (bit_num < BIG_SCALE * 32) && (is_error == 0);
       bit_num++) {
    uint8_t bit_value_of_second = _big_decimal_get_bit(second_ptr, bit_num);

    if (bit_value_of_second == 1) {
      _s21_big_decimal temp = first;
      is_error = _big_decimal_shift_left_n(&temp, bit_num);
      result = _s21_big_decimal_add(&result, &temp);
    }
  }

  if (first_sign != second_sign) _s21_big_decimal_change_sign(&result);

  if (!is_error) *result_ptr = result;
  if (is_error && first_sign != second_sign) is_error = 2;

  return is_error;
}
