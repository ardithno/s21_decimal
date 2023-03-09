#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

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

uint8_t _s21_get_scale(s21_decimal const *x) {
  uint32_t scale = x->bits[SCALE];

  scale = scale << 8;
  scale = scale >> 24;

  return (uint8_t)scale;
}


int s21_get_sign(s21_decimal decimal) {
  return (int)(decimal.bits[SCALE] >> 31 & 1);
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (dst == NULL) {
    result = 1;
  } else {
    double num = 0;
    int scale = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 32; j++) {
        int res = s21_get_bit(src, i * 32 + j);
        printf("%d\n", res);
        if (res == 1) {
          num += pow(2, i * 32 + j);
        }
      }
    }
    scale = _s21_get_scale(&src);
    num /= (double)pow(10.0, (double)scale);
    if (s21_get_sign(src) == 1) {
      num *= -1;
    }
    *dst = (float)num;
  }
  return result;
}

int main() {
    s21_decimal value = {{8}};
    float a = 0;
    s21_from_decimal_to_float(value, &a);
    printf("%f\n", a);
    return 0;
}