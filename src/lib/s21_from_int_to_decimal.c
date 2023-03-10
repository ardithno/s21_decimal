#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return S21_TRUE;  // Mean error happened

  s21_decimal decimal = S21_DECIMAL_NULL;

  if (src < 0) {
    s21_change_sign(&decimal);
    src = -src;
  }

  decimal.bits[LOW] = src;
  *dst = decimal;

  return S21_FALSE;  // Mean no errors during work
}
