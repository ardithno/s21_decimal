#include "../s21_decimal.h"

uint8_t _s21_get_scale(s21_decimal const *x) {
  uint32_t scale = x->bits[SCALE];

  scale = scale << 8;
  scale = scale >> 24;

  return (uint8_t)scale;
}
