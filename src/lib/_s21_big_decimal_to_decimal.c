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

uint8_t _s21_big_decimal_reduce_scale_once(_s21_big_decimal *big_ptr) {
  _s21_big_decimal dividend = *big_ptr;
  _s21_big_decimal divisor = {.bits = {10, 0, 0, 0, 0, 0, 0, 0}};  // ten as big
  _s21_big_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal reminder = S21_DECIMAL_NULL;

  _s21_big_decimal_unsafe_div(dividend, divisor, &result, &reminder);

  *big_ptr = result;
  return (uint8_t)reminder.bits[LOW];
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

uint8_t _s21_big_decimal_reduce_scale(_s21_big_decimal *big_ptr,
                                      int *scale_ptr) {
  uint8_t reminder = 0;
  int scale = *scale_ptr;

  // Checking scale > 28 is a `hack` for division precision purpose.
  // We store dividend scaled 10^29 to access to possible reminder for
  // while converting to plain decimal.
  while (_is_extra_bits_not_empty(big_ptr) || scale > 28) {
    scale--;
    reminder = _s21_big_decimal_reduce_scale_once(big_ptr);
  }

  *scale_ptr = scale;
  return reminder;
}

int _s21_big_decimal_to_decimal(_s21_big_decimal const *big_decimal_ptr,
                                s21_decimal *decimal_ptr, int scale) {
  _s21_big_decimal big = *big_decimal_ptr;
  uint8_t reminder = 0;
  int desired_scale = _s21_big_decimal_get_scale(&big);
  int is_error = S21_FALSE;

  reminder = _s21_big_decimal_reduce_scale(&big, &scale);

  // Remove trailing zeros from result but not more than `desired_scale`
  for (uint8_t temp_reminder = reminder;
       scale > desired_scale && temp_reminder == 0;) {
    _s21_big_decimal temp_big = big;
    temp_reminder = _s21_big_decimal_reduce_scale_once(&temp_big);
    if (temp_reminder == 0) {
      scale--;
      big = temp_big;
    }
  }

  // Bank rounding if required
  if (reminder > 5 || (reminder == 5 && big.bits[LOW] & 1)) {
    _s21_big_decimal one_as_big = {{1, 0, 0, 0, 0, 0, 0, big.bits[BIG_SCALE]}};
    big = _s21_big_decimal_add(&big, &one_as_big);
    reminder = _s21_big_decimal_reduce_scale(&big, &scale);
  }

  if (scale < 0) is_error = (_s21_big_decimal_get_sign(&big) == 0) ? 1 : 2;

  if (!is_error) {
    *decimal_ptr = _s21_convert_suitable_big_decimal_to_decimal(&big, scale);
  }

  return is_error;
}
