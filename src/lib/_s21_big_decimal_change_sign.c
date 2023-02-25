#include "../s21_decimal.h"

void _s21_big_decimal_change_sign(_s21_big_decimal *big_decimal_ptr) {
  S21_BIT_FLIP(big_decimal_ptr->bits[BIG_SCALE], 31);
}
