#include "../s21_decimal.h"

int s21_get_bit(s21_decimal x, unsigned int position) {
  unsigned int result = 0;
  unsigned int mask = (1 << position);
  if (position < 32) {
    result = x.bits[0] & mask;
  }
  if (position >= 32 && position <= 63) {
    result = x.bits[1] & mask;
  }
  if (position >= 64 && position <= 95) {
    result = x.bits[2] & mask;
  }
  if (position >= 96 && position <= 127) {
    result = x.bits[3] & mask;
  }
  return (result == 0) ? 0 : 1;
}
