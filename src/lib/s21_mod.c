#include "../s21_decimal.h"

int s21_mod(s21_decimal dividend, s21_decimal divisor,
            s21_decimal *result_ptr) {
  s21_decimal result = S21_DECIMAL_NULL;

  _s21_big_decimal big_dividend = S21_DECIMAL_NULL;
  _s21_big_decimal big_divisor = S21_DECIMAL_NULL;
  _s21_big_decimal big_reminder = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&dividend, &big_dividend);
  _s21_decimal_to_big_decimal(&divisor, &big_divisor);

  _s21_big_decimal_unsafe_div(big_dividend, big_divisor, NULL, &big_reminder);

  // Set desired scale to result
  uint32_t divisor_scale = _s21_get_scale(&divisor);
  big_reminder.bits[BIG_SCALE] &= 0x80000000;
  big_reminder.bits[BIG_SCALE] |= divisor_scale << 16;

  _s21_big_decimal_to_decimal(&big_reminder, &result, 28);

  *result_ptr = result;
  return 0;
}
