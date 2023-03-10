#include "../s21_decimal.h"

int s21_is_zero(s21_decimal decimal) {
  int is_zero = S21_TRUE;

  for (int byte_num = LOW; byte_num < SCALE; byte_num++) {
    if (decimal.bits[byte_num] != 0) is_zero = S21_FALSE;
  }

  return is_zero;
}
