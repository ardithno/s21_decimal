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
  s21_decimal x = {.bits = {1, 2, 3, 655360}};
  s21_decimal y = {.bits = {1, 2, 3, -2146828288}};

  print_bits(sizeof(x), &x);
  print_bits(sizeof(y), &y);
  // uint64_t y = 0xffffffff;
  // printf("y as bits not mul 10\n");
  // uint32_t y_bits[2] = {y << 32 >> 32, y >> 32};
  // print_bits(sizeof(y_bits), &y_bits);

  // uint64_t temp = y_bits[0] * 10;
  // uint8_t overflow_from_lower_bits = temp >> 32;
  // y_bits[0] = temp << 32 >> 32;

  // y_bits[1] *= 10;
  // y_bits[1] += overflow_from_lower_bits;

  // print_bits(sizeof(y_bits), &y_bits);

  // printf("y_low_bits=%x\n", y_bits[0]);
  // printf("y_high_bits=%x\n", y_bits[1]);

  // s21_decimal same_decimal = {{0xffffffff, 0, 0, 0}};
  // _s21_big_decimal converted_same;
  // s21_decimal decimal_scale_one = {{0xfffffff6, 0x9, 0, 0x10000}};  // scale 1
  // _s21_big_decimal converted_scale_one;

  // _s21_decimal_to_big_decimal(&decimal_scale_one, &converted_scale_one);
  // _s21_decimal_to_big_decimal(&same_decimal, &converted_same);

  // printf("Not_scaled\n");
  // print_bits(sizeof(same_decimal), &same_decimal);
  // print_bits(sizeof(converted_same), &converted_same);

  // printf("Scaled\n");
  // print_bits(sizeof(decimal_scale_one), &decimal_scale_one);
  // print_bits(sizeof(converted_scale_one), &converted_scale_one);

  // for (int i = 1; i <= 10; i++) {
  //   x *= 10;
  //   print_bits(sizeof(x), &x);
  // }
  // s21_decimal max_decimal = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  // _s21_big_decimal max_big_decimal = S21_DECIMAL_NULL;

  // _s21_decimal_to_big_decimal(&max_decimal, &max_big_decimal);

  // print_bits(sizeof(max_decimal), &max_decimal);
  // print_bits(sizeof(max_big_decimal), &max_big_decimal);



}
