#include "../s21_decimal.h"

_s21_big_decimal _s21_decimal_copy_to_big_decimal(s21_decimal decimal) {
  // Just copy decimal to big_decimal structure
  _s21_big_decimal big = S21_DECIMAL_NULL;

  big.bits[BIG_SCALE] = decimal.bits[SCALE];

  for (int i = LOW; i < SCALE; i++) {
    big.bits[i] = decimal.bits[i];
  }

  return big;
}
