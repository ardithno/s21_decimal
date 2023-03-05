#include "../s21_decimal.h"

void _s21_big_decimal_set_bit(_s21_big_decimal *big_ptr, uint8_t bit_num) {
  // It's supporting function that help to set bit to 1 in big_decimal
  uint8_t word_num = bit_num / 32;
  uint8_t bit_in_word_num = bit_num % 32;

  S21_BIT_SET(big_ptr->bits[word_num], bit_in_word_num);
}
