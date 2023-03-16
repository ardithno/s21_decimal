#include "../s21_decimal.h"

int s21_get_mantissa(float a) {
  int num = 0;
  memcpy(&num, &a, 4);
  return (num & 0x7FFFFF);
}