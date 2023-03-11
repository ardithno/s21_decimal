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

_s21_big_decimal _int_as_big_decimal(uint32_t x) {
  _s21_big_decimal big = S21_DECIMAL_NULL;
  big.bits[LOW] = x;
  return big;
}

_s21_big_decimal _make_big_reminder(uint32_t x, int power_of_ten) {
  _s21_big_decimal reminder = S21_DECIMAL_NULL;
  reminder.bits[LOW] = x;

  for (int i = 1; i <= power_of_ten; i++) {
    _s21_big_decimal_multiply_ten(&reminder);
  }

  return reminder;
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

int _s21_big_decimal_reduce_scale(_s21_big_decimal *big_ptr, int *scale_ptr) {
  _s21_big_decimal big_reminder = S21_DECIMAL_NULL;
  _s21_big_decimal to_compare = {.bits = {5, 0, 0, 0, 0, 0, 0, 0}};
  int scale = *scale_ptr;
  int iteration = 1;

  // Checking scale > 28 is a `hack` for precision of division purpose.
  // We use scale 30 in division.
  // We also save `reminder` as big decimal and comparing it with `to_compare`
  // and return wether rounding is required or not
  while (_is_extra_bits_not_empty(big_ptr) || scale > 28) {
    scale--;
    uint8_t temp = _s21_big_decimal_reduce_scale_once(big_ptr);

    _s21_big_decimal big_temp_reminder = _make_big_reminder(temp, iteration++);
    big_reminder = _s21_big_decimal_add(&big_reminder, &big_temp_reminder);
    _s21_big_decimal_multiply_ten(&to_compare);
  }

  *scale_ptr = scale;

  // Return 0 if reminder equals 0
  // Return 1 if rounding required
  // Return -1 if reminder not 0 but rounding not required
  int result = 0;
  _s21_big_decimal null = S21_DECIMAL_NULL;
  int compare_result = 0;
  int is_reminder_null = 0;

  is_reminder_null = _s21_big_decimal_compare_bits(&big_reminder, &null);
  compare_result = _s21_big_decimal_compare_bits(&big_reminder, &to_compare);

  if (is_reminder_null == 0) {
    result = 0;
  } else if (compare_result == -1 ||
             (big_ptr->bits[LOW] & 1 && compare_result == 0)) {
    result = 1;
  } else {
    result = -1;
  }

  return result;
}

int _s21_big_decimal_to_decimal(_s21_big_decimal const *big_decimal_ptr,
                                s21_decimal *decimal_ptr, int scale) {
  _s21_big_decimal big = *big_decimal_ptr;
  int conversion_result = 0;
  int desired_scale = _s21_big_decimal_get_scale(&big);
  int is_error = S21_FALSE;

  conversion_result = _s21_big_decimal_reduce_scale(&big, &scale);

  // Bank rounding if required
  if (conversion_result == 1) {
    _s21_big_decimal one_as_big = {{1, 0, 0, 0, 0, 0, 0, big.bits[BIG_SCALE]}};
    big = _s21_big_decimal_add(&big, &one_as_big);
    conversion_result = _s21_big_decimal_reduce_scale(&big, &scale);
  }

  // Remove trailing zeros from result but not more than `desired_scale`
  while (conversion_result == 0 && scale > desired_scale) {
    _s21_big_decimal temp_big = big;
    conversion_result = _s21_big_decimal_reduce_scale_once(&temp_big);

    if (conversion_result == 0) {
      scale--;
      big = temp_big;
    }
  }

  if (scale < 0) is_error = (_s21_big_decimal_get_sign(&big) == 0) ? 1 : 2;

  if (!is_error) {
    *decimal_ptr = _s21_convert_suitable_big_decimal_to_decimal(&big, scale);
  }

  return is_error;
}
