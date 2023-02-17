#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

void print_bits(size_t size, void *value_ptr) {
  // Assume we work with little endian
  char byte_bits;
  unsigned char *value_as_bytes;

  value_as_bytes = (unsigned char *)value_ptr;

  for (size_t byte_number = size; byte_number > 0; byte_number--) {
    printf("   ");
    byte_bits = value_as_bytes[byte_number - 1];

    for (char bit_number = 7; bit_number >= 0; bit_number--) {
      char bit_value;
      bit_value = (byte_bits >> bit_number) & 1;
      printf("%d", bit_value);
    }
    printf(" ");
  }
  printf("\n");

  for (size_t byte_number = size; byte_number > 0; byte_number--) {
    printf("%11p", value_as_bytes + byte_number - 1);

    if (byte_number != 0) printf(" ");
  }
  printf("\n");
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
  _s21_big_decimal x = {.bits={1, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal y = {.bits={0, 1, 0, 0, 0, 0, 0x80000000}};;

  int result = _s21_compare_big_decimals(&x, &y);
  printf("result=%d\n", result);
}
