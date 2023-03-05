#include "../s21_decimal.h"

void _s21_big_decimal_multiply_ten(_s21_big_decimal *big_ptr) {
  // Multiply the `big_decimal` to 10
  // It means increasing scale. Something like that 123 * 10 = 1230

  uint8_t overflow_from_lower_bits = 0;  // It's enough for multiply by 10

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = (uint64_t)(big_ptr->bits[i]);
    temp *= 10;
    temp += overflow_from_lower_bits;

    big_ptr->bits[i] = (uint32_t)(temp & 0xffffffff);
    overflow_from_lower_bits = (uint8_t)(temp >> 32);
  }
}
