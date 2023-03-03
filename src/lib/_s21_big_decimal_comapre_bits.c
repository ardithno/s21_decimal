#include "../s21_decimal.h"

int _s21_big_decimal_compare_bits(const _s21_big_decimal *first,
                                  const _s21_big_decimal *second) {
  // Return 0 if bits are the same
  // Return -1 if `first` bigger than `second` on bits basis
  // Return 1 if `second` bigger than `first` on bits basis

  int result = 0;

  for (int i = (BIG_SCALE - 1); i >= 0; i--) {
    if (first->bits[i] != second->bits[i]) {
      result = first->bits[i] > second->bits[i] ? -1 : 1;
      break;
    }
  }

  return result;
}
