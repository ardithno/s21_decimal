#include "../s21_decimal.h"

int _s21_is_big_decimals_equal(_s21_big_decimal const *first,
                               _s21_big_decimal const *second) {
  int num_equal_bits = 0;

  for (int i = LOW; i < BIG_DECIMAL_PARTS_COUNT; i++) {
    if (first->bits[i] == second->bits[i]) num_equal_bits++;
  }

  return (num_equal_bits == BIG_DECIMAL_PARTS_COUNT) ? S21_TRUE : S21_FALSE;
}
