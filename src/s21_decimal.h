#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stddef.h>
#include <stdint.h>

enum S21_BOOL {
  S21_FALSE,
  S21_TRUE,
};

enum S21_DECIMAL_BYTE_PURPOSE {
  LOW,
  MID,
  HIGH,
  SCALE,
};

#define DECIMAL_PARTS_LEN 4
#define S21_DECIMAL_MAX_SCALE 28

typedef struct s21_decimal {
  uint32_t bits[DECIMAL_PARTS_LEN];
} s21_decimal;

#define S21_DECIMAL_NULL {0};

// Thank Steve for these beautiful macros https://stackoverflow.com/a/263738
#define S21_BIT_SET(target, bit_num) ((target) |= (1ULL << (bit_num)))
#define S21_BIT_CLEAR(target, bit_num) ((target) &= ~(1ULL << (bit_num)))
#define S21_BIT_FLIP(target, bit_num) ((target) ^= (1ULL << (bit_num)))

void s21_change_sign(s21_decimal *decimal);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_get_sign(s21_decimal decimal);
int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_zero(s21_decimal decimal);
int s21_negate(s21_decimal value, s21_decimal *result);

/* -----------------------------------------------------
--------- Internal functions and definitions -----------
------------------------------------------------------ */

#define BIG_DECIMAL_PARTS_LEN ((DECIMAL_PARTS_LEN - 1) * 2 + 1)
#define BIG_SCALE (BIG_DECIMAL_PARTS_LEN - 1)

// The structure is big enough to store any decimal scaled to zero
typedef struct _s21_big_decimal {
  uint32_t bits[BIG_DECIMAL_PARTS_LEN];
} _s21_big_decimal;

int _s21_compare_big_decimals(_s21_big_decimal const *first,
                               _s21_big_decimal const *second);
int _s21_decimal_to_big_decimal(s21_decimal const *decimal,
                                _s21_big_decimal *big_decimal_ptr);
uint8_t _s21_get_scale(s21_decimal const *decimal);
int _s21_get_big_decimal_sign(_s21_big_decimal const *big_decimal);

#endif  // SRC_S21_DECIMAL_H_
