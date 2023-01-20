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

int main() {
  unsigned int x;
  x = INT32_MAX;
  x += 1;

  // print_bits(sizeof(unsigned int), &x);

  // int y;
  // y = INT32_MIN;
  // print_bits(sizeof(int), &y);

  x = 23;
  for(int i=1; i<=5; i++) {
    x *= 10;
    printf("x=%d\n", x);
    print_bits(sizeof(unsigned int), &x);
  }
}
