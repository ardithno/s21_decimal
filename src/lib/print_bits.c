#include <stdio.h>

#include "../s21_decimal.h"

void print_bits(size_t size, void *value_ptr) {
  // Assume we work with little endian
  char byte_bits;
  unsigned char *value_as_bytes;

  value_as_bytes = (unsigned char *)value_ptr;

  for (size_t byte_number = size; byte_number > 0; byte_number--) {
    // printf("   ");
    byte_bits = value_as_bytes[byte_number - 1];

    for (int bit_number = 7; bit_number >= 0; bit_number--) {
      char bit_value;
      bit_value = (byte_bits >> bit_number) & 1;
      printf("%d", bit_value);
    }

    printf(" ");
    if ((byte_number - 1) % 4 == 0 && (byte_number - 1) != 0) printf("| ");
  }
  printf("\n");
}