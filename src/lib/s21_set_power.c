
#include "../s21_decimal.h"

void s21_set_power(s21_decimal *number, int pow) {
  number->bits[3] &= 0x80000000;
  for (int i = 16; i <= 23 && pow; i++) {
    if (pow % 2 == 1) {
      S21_BIT_SET(number->bits[3], i);
    }
    pow /= 2;
  }
}