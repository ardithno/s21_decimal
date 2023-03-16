#include "../s21_decimal.h"

int s21_get_exp(float a) {
  int num = 0;
  memcpy(&num, &a, 4);
  return (((num >> 23) & 255) - 127);
}