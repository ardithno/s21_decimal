#include "../s21_decimal.h"

int s21_get_sign(s21_decimal decimal) {
  return (int)(decimal.bits[SCALE] & 1ULL);
}
