#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

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

#define DECIMAL_PARTS_COUNT 4

typedef struct s21_decimal {
  unsigned int bits[DECIMAL_PARTS_COUNT];
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

#endif  // SRC_S21_MATH_H_