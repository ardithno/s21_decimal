#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

// void print_bits(size_t size, void *value_ptr) {
//   // Assume we work with little endian
//   char byte_bits;
//   unsigned char *value_as_bytes;

//   value_as_bytes = (unsigned char *)value_ptr;

//   for (size_t byte_number = size; byte_number > 0; byte_number--) {
//     // printf("   ");
//     byte_bits = value_as_bytes[byte_number - 1];

//     for (char bit_number = 7; bit_number >= 0; bit_number--) {
//       char bit_value;
//       bit_value = (byte_bits >> bit_number) & 1;
//       printf("%d", bit_value);
//     }

//     printf(" ");
//     if ((byte_number - 1) % 4 == 0 && (byte_number - 1) != 0) printf("| ");
//   }
//   printf("\n");

//   // for (size_t byte_number = size; byte_number > 0; byte_number--) {
//     // printf("%11p", value_as_bytes + byte_number - 1);
//     // if (byte_number != 0) printf(" ");
//   // }
//   // printf("\n");
// }

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
  s21_decimal d_max = {.bits={0xffffffff, 0xffffffff, 0xffffffff, 0}};
  _s21_big_decimal bdx_max = S21_DECIMAL_NULL;
  _s21_big_decimal bdy_max = S21_DECIMAL_NULL;

  _s21_decimal_to_big_decimal(&d_max, &bdx_max);
  _s21_decimal_to_big_decimal(&d_max, &bdy_max);

  _s21_big_decimal result = _s21_big_decimal_sub(&bdx_max, &bdy_max);

  print_bits(sizeof(result), &result);

  int x = 0x000000ff;
  int y = 0x000000ff;
  int z = y + x;

  print_bits(sizeof(x), &x);
  print_bits(sizeof(y), &y);
  print_bits(sizeof(z), &z);

}
