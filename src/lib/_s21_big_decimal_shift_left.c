#include "../s21_decimal.h"

void _s21_big_decimal_shift_left(_s21_big_decimal *big_decimal_ptr) {
  // Shift big_decimal_ptr value bits to left once

  uint8_t bit_from_lower_word = 0;

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = big_decimal_ptr->bits[i];

    temp <<= 1;
    temp |= bit_from_lower_word;
    bit_from_lower_word = (uint8_t)(temp >> 32);

    big_decimal_ptr->bits[i] = (uint32_t)(temp & 0xffffffff);
  }
}
