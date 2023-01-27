#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

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

  u_int64_t to_sum_from_low_bits = 0;

  for (int i=LOW; i<=HIGH; i++) {
    uint64_t temp = x.bits[i];
    temp *= multiplier;
    temp += to_sum_from_low_bits;

    to_sum_from_low_bits = temp >> 32;
    x.bits[i] = (uint32_t)(temp & 0xffffffff);
  }

  *input = x;
}

int main() {
  // unsigned int x;
  // x = INT32_MAX;
  // x += 1;

  // print_bits(sizeof(unsigned int), &x);

  // int y;
  // y = INT32_MIN;
  // print_bits(sizeof(int), &y);

  // x = 23;
  // for(int i=1; i<=5; i++) {
  //   x *= 10;
  //   printf("x=%d\n", x);
  //   print_bits(sizeof(unsigned int), &x);
  // }

  // x = 15;
  // print_bits(sizeof(unsigned int), &x);

  // x += x;
  // print_bits(sizeof(unsigned int), &x);

  int multiplier = INT32_MAX;

  s21_decimal d = {{INT32_MAX, 0, 0, 0}};
  s21_mul_int(&d, multiplier);
  print_bits(sizeof(s21_decimal), &d);
  
  uint64_t compare = INT32_MAX;
  compare *= multiplier;
  print_bits(sizeof(uint64_t), &compare);

  // printf("uint size = %lu\n", sizeof(unsigned int));
  // printf("uint long size = %lu\n", sizeof(unsigned long int));
  // printf("uint long long size = %lu\n", sizeof(unsigned long long int));
  // printf("uint long long long size = %lu\n", sizeof(unsigned long long int));
}


34 * 10e-4 = 0.0034



