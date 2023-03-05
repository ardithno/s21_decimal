#include "../s21_decimal.h"

int s21_get_power(s21_decimal number) {
  int power = 0;
  int result = 0;
  for (int i = 0; i < 7; i++) {
    int temp = s21_get_bit(number, 96 + i + 16);
    power = (1U << i) * temp;
    result += power;
  }
  return result;
}
