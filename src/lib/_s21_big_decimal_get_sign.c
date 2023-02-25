#include "../s21_decimal.h"

int _s21_big_decimal_get_sign(_s21_big_decimal const *big_decimal) {
  // Return 0 for positive and 1 for negative
  return (int)(big_decimal->bits[BIG_SCALE] >> 31 & 1);
}
