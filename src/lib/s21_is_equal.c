#include "../s21_decimal.h"

int s21_is_equal(s21_decimal first, s21_decimal second) {
  int is_equal = S21_FALSE;

  // Zero case
  if (s21_is_zero(first) && s21_is_zero(second)) {
    is_equal = S21_TRUE;
  }

  // Non zero case. Maybe NAN should be the handled here
  if (!is_equal) {
    int num_equal_bytes = 0;

    for (int byte_num = 0; byte_num < DECIMAL_PARTS_COUNT; byte_num++) {
      if (first.bits[byte_num] == second.bits[byte_num]) num_equal_bytes++;
    }

    if (num_equal_bytes == DECIMAL_PARTS_COUNT) is_equal = S21_TRUE;
  }

  return is_equal;
}
