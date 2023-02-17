#include "../s21_decimal.h"

void s21_change_sign(s21_decimal *decimal) {
  S21_BIT_FLIP(decimal->bits[SCALE], 31);
}
