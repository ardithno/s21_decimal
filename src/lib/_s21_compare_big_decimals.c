#include "../s21_decimal.h"

int _s21_compare_big_decimals(_s21_big_decimal const *first,
                              _s21_big_decimal const *second) {
  // Return -1, 0, or 1
  // if first bigger than second return -1
  // if first equal second return 0
  // if first less than second return 1
  int first_sign = _s21_get_big_decimal_sign(first);
  int second_sign = _s21_get_big_decimal_sign(second);
  int num_zero_bits = 0;

  int bits_compare = 0;

  for (int i = BIG_DECIMAL_PARTS_LEN - 1; i >= 0; i--) {
    if (first->bits[i] != second->bits[i]) {
      bits_compare = (second->bits[i] > first->bits[i]) ? 1 : -1;
      break;
    }

    if (first->bits[i] == 0 && second->bits[i] == 0) num_zero_bits++;
  }

  int result = -999;  // Any non valid value

  // Edge case: two big decimals are zeros (negative or positive)
  if (bits_compare == 0 && num_zero_bits == BIG_DECIMAL_PARTS_LEN - 1) {
    result = 0;
  }

  // Edge case: any of big decimals is not zero, but all bits the same
  if (bits_compare == 0 && num_zero_bits != BIG_DECIMAL_PARTS_LEN - 1) {
    // Same signs
    if (first_sign == second_sign) result = 0;

    // First is positive, second negative
    if (first_sign != second_sign && first_sign == 0) result = -1;

    // First is negative, second positive
    if (first_sign != second_sign && first_sign == 1) result = 1;
  }

  // Regular case: bits of big decimals differs
  if (bits_compare != 0) {
    // Different signs, first is positive
    if (first_sign != second_sign && first_sign == 0) result = -1;

    // Different signs, first is negative
    if (first_sign != second_sign && first_sign == 1) result = 1;

    // Same signs, first is positive
    if (first_sign == second_sign && first_sign == 0) result = bits_compare;

    // Same signs, first is negative
    if (first_sign == second_sign && first_sign == -1) result = -bits_compare;
  }

  return result;
}
