#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

uint32_t get_int_bits_as_uint(int x) {
  union convert {
    int int_value;
    uint32_t uint_value;
  } convert = {.int_value = x};

  return convert.uint_value;
}

int get_uint_bits_as_int(uint32_t x) {
  union convert {
    int int_value;
    uint32_t uint_value;
  } convert = {.uint_value = x};

  return convert.int_value;
}

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
  s21_decimal x = {.bits = {1, 1, 1, 655360}};
  s21_decimal y = {.bits = {1, 10, 1, -2146500608}};

  s21_decimal result = S21_DECIMAL_NULL;
  s21_div(x, y, &result);

  print_bits(sizeof(result), &result);

  s21_decimal value = {.bits=894784853, 3475376110, 1807003620, 0};

  printf("result_ints=%d, %d, %d, %d, sign=%d\n",
         get_uint_bits_as_int(value.bits[0]),
         get_uint_bits_as_int(value.bits[1]),
         get_uint_bits_as_int(value.bits[2]), value.bits[3] << 8 >> 24,
         s21_get_sign(value));

  printf("-2146500608 as uint = %u\n", get_int_bits_as_uint(-2146500608));
}
