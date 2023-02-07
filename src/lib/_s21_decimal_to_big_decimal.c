#include "../s21_decimal.h"

int _s21_decimal_to_big_decimal(s21_decimal const *decimal_ptr,
                                _s21_big_decimal *big_decimal_ptr) {
  _s21_big_decimal big_decimal = S21_DECIMAL_NULL;

  // Fill initial big decimal bits from decimal representation
  for (int i = LOW; i <= HIGH; i++) {
    big_decimal.bits[i] = decimal_ptr->bits[i];
  }

  // Set big decimal scale to zero with sign form incoming decimal
  big_decimal.bits[BIG_SCALE] = decimal_ptr->bits[SCALE] & 0x80000000;

  uint8_t power_of_ten = S21_DECIMAL_MAX_SCALE - _s21_get_scale(decimal_ptr);
  uint8_t overflow_from_lower_bits = 0;  // It's enough for multiply by 10

  while (power_of_ten-- != 0) {
    for (int i = LOW; i < BIG_SCALE; i++) {
      uint64_t temp = (uint64_t)(big_decimal.bits[i]);
      temp = (temp << 3) + (temp << 1);  // Multiple to ten as bit shifts
      temp += overflow_from_lower_bits;

      big_decimal.bits[i] = (uint32_t)(temp & 0xffffffff);
      overflow_from_lower_bits = (uint8_t)(temp >> 32);
    }
  }

  *big_decimal_ptr = big_decimal;

  // False meaning no errors during conversion
  return (overflow_from_lower_bits == 0) ? S21_FALSE : S21_TRUE;
}
