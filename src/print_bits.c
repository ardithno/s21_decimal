#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

void s21_mul_int(s21_decimal *input, int multiplier) {
  s21_decimal x = *input;

  uint64_t to_sum_from_low_bits = 0;

  for (int i = LOW; i <= HIGH; i++) {
    uint64_t temp = x.bits[i];
    temp *= multiplier;
    temp += to_sum_from_low_bits;

    to_sum_from_low_bits = temp >> 32;
    x.bits[i] = (uint32_t)(temp & 0xffffffff);
  }

  *input = x;
}

int main() {
  // 792.28162514264337593543950335 + 10 = 802.2816251426433759354395034
  s21_decimal x = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0x1a0000}};
  s21_decimal y = {.bits = {1, 0, 0, 0}};
  // s21_decimal expect = {.bits = {0xe399999a, 0xafad9ae1, 0x19a1df2e, 0x190000}};
  // s21_decimal result = S21_DECIMAL_NULL;

  _s21_big_decimal big_x = S21_DECIMAL_NULL;
  _s21_big_decimal big_y = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&x, &big_x);
  _s21_decimal_to_big_decimal(&y, &big_y);

  print_bits(sizeof(big_y), &big_y);
  print_bits(sizeof(big_x), &big_x);

  _s21_big_decimal result = S21_DECIMAL_NULL;
  result = _s21_big_decimal_add(&big_x, &big_y);
  print_bits(sizeof(result), &result);
}
