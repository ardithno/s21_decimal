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
  s21_decimal x = {.bits = {-2, -1, -1, 0x10000}};
  s21_decimal y = {.bits = {5, 0, 0, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;

  print_bits(sizeof(x), &x);
  print_bits(sizeof(y), &y);

  _s21_big_decimal bx = S21_DECIMAL_NULL;
  _s21_big_decimal by = S21_DECIMAL_NULL;
  _s21_big_decimal bresult = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&x, &bx);
  _s21_decimal_to_big_decimal(&y, &by);

  bresult = _s21_big_decimal_add(&bx, &by);

  _s21_big_decimal_to_decimal(&bresult, &result);
  print_bits(sizeof(result), &result);

  // printf("d = %u\n", 0b11111111111111111111111110110100);

  // s21_decimal y = {.bits = {1, 0, 0, 0x80000000}};
  // _s21_big_decimal by = S21_DECIMAL_NULL;
  // _s21_decimal_to_big_decimal(&y, &by);

  // _s21_big_decimal bresult = S21_DECIMAL_NULL;
  // bresult = _s21_big_decimal_add(&by, &by);
  // printf("big_result\n");
  // print_bits(sizeof(bresult), &bresult);

  // s21_decimal result = S21_DECIMAL_NULL;
  // printf("result\n");
  // print_bits(sizeof(result), &result);

  // int f = 0b11111111111111111111111111111110;
  // printf("f=%d\n", f);
  // print_bits(sizeof(f), &f);
}
