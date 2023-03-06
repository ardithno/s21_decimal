#include "../s21_decimal.h"

void _s21_decimal_to_big_decimal(s21_decimal const *decimal_ptr,
                                 _s21_big_decimal *big_decimal_ptr) {
  _s21_big_decimal big_decimal = S21_DECIMAL_NULL;

  // Fill initial big decimal bits from decimal representation
  for (int i = LOW; i <= HIGH; i++) {
    big_decimal.bits[i] = decimal_ptr->bits[i];
  }

  // Set sign and save the scale.
  // The scale will be used to restore decimal scale if applicable
  big_decimal.bits[BIG_SCALE] = decimal_ptr->bits[SCALE];

  uint8_t power_of_ten = S21_DECIMAL_MAX_SCALE - _s21_get_scale(decimal_ptr);

  while (power_of_ten-- != 0) {
    _s21_big_decimal_multiply_ten(&big_decimal);
  }

  *big_decimal_ptr = big_decimal;
}
