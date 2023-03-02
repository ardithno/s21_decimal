#include "../s21_decimal.h"

_s21_big_decimal _s21_bits_add(const _s21_big_decimal *first_ptr,
                               const _s21_big_decimal *second_ptr) {
  // Adding on bits level only.
  // The sign of the result will be get from `first_ptr` value
  _s21_big_decimal big_result = *first_ptr;

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = big_result.bits[i];
    temp += second_ptr->bits[i];

    big_result.bits[i] = (uint32_t)(temp & 0xffffffff);

    for (int j = i + 1; temp >> 32 == 0x00000001; j++) {
      temp = big_result.bits[j] + 1;
      big_result.bits[j] = (uint32_t)(temp & 0xffffffff);
    }
  }

  return big_result;
}

_s21_big_decimal _s21_big_decimal_add(const _s21_big_decimal *first_ptr,
                                      const _s21_big_decimal *second_ptr) {
  // We assume that there is NO chance to overflow big_decimal during
  // adding, because the values stored in each big_decimal are
  // converted decimals and they are too small to overflow.
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  int first_sign = _s21_big_decimal_get_sign(first_ptr);
  int second_sign = _s21_big_decimal_get_sign(second_ptr);

  // If first positive and second negative => call sub for: first - second
  if (first_sign == 0 && second_sign == 1) {
    _s21_big_decimal temp = *second_ptr;
    _s21_big_decimal_change_sign(&temp);
    big_result = _s21_big_decimal_sub(first_ptr, &temp);
  }

  // If second positive and first negative => call sub for: second - first
  if (first_sign == 1 && second_sign == 0) {
    _s21_big_decimal temp = *first_ptr;
    _s21_big_decimal_change_sign(&temp);
    big_result = _s21_big_decimal_sub(second_ptr, &temp);
  }

  if (first_sign == second_sign) {
    big_result = _s21_bits_add(first_ptr, second_ptr);
  }

  return big_result;
}
