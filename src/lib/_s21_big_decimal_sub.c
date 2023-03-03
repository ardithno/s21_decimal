#include "../s21_decimal.h"

_s21_big_decimal _s21_bits_sub(const _s21_big_decimal *minuend_ptr,
                               const _s21_big_decimal *subtrahend_ptr) {
  // Subtrahend on bits level only.
  // It's required that minuend on bit level is bigger than subtrahend.
  // And it's user responsibility to validate this.
  //
  // The sign of the result will be get from minuend
  _s21_big_decimal big_result = *minuend_ptr;

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = 0x100000000 | big_result.bits[i];
    temp -= subtrahend_ptr->bits[i];

    big_result.bits[i] = (uint32_t)(temp & 0xffffffff);

    for (int j = i + 1; temp >> 32 != 0x00000001; j++) {
      temp = 0x100000000 | big_result.bits[j];
      temp -= 1;
      big_result.bits[j] = (uint32_t)(temp & 0xffffffff);
    }
  }

  return big_result;
}

_s21_big_decimal _s21_big_decimal_sub(const _s21_big_decimal *minuend_ptr,
                                      const _s21_big_decimal *subtrahend_ptr) {
  // We assume that there is NO chance to overflow big_decimal during
  // subtraction, because the values stored in each big_decimal are
  // converted decimals.
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  int minuend_sign = _s21_big_decimal_get_sign(minuend_ptr);
  int subtrahend_sign = _s21_big_decimal_get_sign(subtrahend_ptr);

  // If signs differs we should use `add` instead
  if (minuend_sign != subtrahend_sign) {
    _s21_big_decimal temp = *subtrahend_ptr;
    _s21_big_decimal_change_sign(&temp);
    big_result = _s21_big_decimal_add(minuend_ptr, &temp);
  }

  // If signs the same we could do subtraction
  if (minuend_sign == subtrahend_sign) {
    int bits_compare;
    bits_compare = _s21_big_decimal_compare_bits(minuend_ptr, subtrahend_ptr);
    if (bits_compare == -1) {
      big_result = _s21_bits_sub(minuend_ptr, subtrahend_ptr);
    } else if (bits_compare == 1) {
      big_result = _s21_bits_sub(subtrahend_ptr, minuend_ptr);
      _s21_big_decimal_change_sign(&big_result);
    } else {  // if bits equal == values equal and result = 0. Save scale here
      big_result.bits[BIG_SCALE] = minuend_ptr->bits[BIG_SCALE];
    }
  }

  return big_result;
}
