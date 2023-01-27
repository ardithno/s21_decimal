#include "../s21_decimal.h"

int s21_is_zero(s21_decimal decimal) {
  int is_zero = S21_TRUE;

  S21_BIT_CLEAR(decimal.bits[SCALE], 31);

  for (int byte_num = 0; byte_num < DECIMAL_PARTS_COUNT; byte_num++) {
    if (decimal.bits[byte_num] != 0) is_zero = S21_FALSE;
  }

  return is_zero;
}
