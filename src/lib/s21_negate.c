#include <stddef.h>

#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int is_error = S21_FALSE;

  if (result == NULL) is_error = S21_TRUE;

  if (!is_error) {
    *result = value;
    s21_change_sign(result);
  }

  return is_error;
}
