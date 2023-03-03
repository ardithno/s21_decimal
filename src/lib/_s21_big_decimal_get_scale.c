#include "../s21_decimal.h"

uint8_t _s21_big_decimal_get_scale(_s21_big_decimal const *x) {
  uint32_t scale = x->bits[BIG_SCALE];

  scale = scale << 8;
  scale = scale >> 24;

  return (uint8_t)scale;
}
