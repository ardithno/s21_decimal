#include "../s21_decimal.h"

void s21_left_shift(s21_decimal *dec, int shift) {
  int bit1 = 0;
  int bit2 = 0;
  while (shift != 0) {
    for (int i = 0; i <= 2; i++) {
      if (i == 0) {
        bit1 = s21_get_bit(*dec, 31);
        bit2 = s21_get_bit(*dec, 63);
      }
      dec->bits[i] <<= 1;
      if (bit1 == 1 && i == 1) {
        S21_BIT_SET(dec->bits[i], 0);
      }
      if (bit2 == 1 && i == 2) {
        S21_BIT_SET(dec->bits[i], 0);
      }
    }
    shift--;
  }
}