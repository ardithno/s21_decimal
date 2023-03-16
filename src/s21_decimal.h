#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

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

#define MAX_DECIMAL 79228162514264337593543950335.
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

int s21_add(s21_decimal first, s21_decimal second, s21_decimal *result_ptr);
int s21_div(s21_decimal divisor, s21_decimal dividend, s21_decimal *result_ptr);
void s21_change_sign(s21_decimal *decimal);
int s21_get_bit(s21_decimal x, unsigned int position);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_get_sign(s21_decimal decimal);
int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int s21_is_less(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);
void s21_set_power(s21_decimal *number, int pow);
int s21_is_zero(s21_decimal decimal);
int s21_mod(s21_decimal dividend, s21_decimal divisor, s21_decimal *result_ptr);
int s21_mul(s21_decimal first, s21_decimal second, s21_decimal *result_ptr);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_sub(s21_decimal first, s21_decimal second, s21_decimal *result_ptr);
int s21_get_exp(float a);
void s21_left_shift(s21_decimal *decimal, int step);
int s21_get_mantissa(float a);

/* -----------------------------------------------------
--------- Internal functions and definitions -----------
------------------------------------------------------ */

#define BIG_DECIMAL_PARTS_LEN 8
#define BIG_SCALE (BIG_DECIMAL_PARTS_LEN - 1)

// The structure is big enough to store any decimal scaled to zero
typedef struct _s21_big_decimal {
  uint32_t bits[BIG_DECIMAL_PARTS_LEN];
} _s21_big_decimal;

_s21_big_decimal _s21_big_decimal_add(const _s21_big_decimal *first_ptr,
                                      const _s21_big_decimal *second_ptr);
void _s21_big_decimal_change_sign(_s21_big_decimal *big_decimal_ptr);
int _s21_big_decimal_compare_bits(_s21_big_decimal const *first,
                                  _s21_big_decimal const *second);
_s21_big_decimal _s21_decimal_copy_to_big_decimal(s21_decimal decimal);
int _s21_big_decimal_compare(_s21_big_decimal const *first,
                             _s21_big_decimal const *second);
uint8_t _s21_big_decimal_get_scale(_s21_big_decimal const *x);
int _s21_big_decimal_get_sign(_s21_big_decimal const *big_decimal);
int _s21_big_decimal_mul(_s21_big_decimal const *first_ptr,
                         _s21_big_decimal const *second_ptr,
                         _s21_big_decimal *result_ptr);
void _s21_big_decimal_multiply_ten(_s21_big_decimal *big_ptr);
void _s21_big_decimal_set_bit(_s21_big_decimal *big_decimal, uint8_t bit_num);
void _s21_big_decimal_shift_left(_s21_big_decimal *big_decimal_ptr);
_s21_big_decimal _s21_big_decimal_sub(const _s21_big_decimal *minuend_ptr,
                                      const _s21_big_decimal *subtrahend_ptr);
int _s21_big_decimal_to_decimal(_s21_big_decimal const *big_decimal_ptr,
                                s21_decimal *decimal_ptr, int scale);
void _s21_big_decimal_unsafe_div(_s21_big_decimal dividend,
                                 _s21_big_decimal divisor,
                                 _s21_big_decimal *result_ptr,
                                 _s21_big_decimal *reminder_ptr);
int _s21_decimal_compare_bits(s21_decimal const *first,
                              s21_decimal const *second);
void _s21_decimal_to_big_decimal(s21_decimal const *decimal,
                                 _s21_big_decimal *big_decimal_ptr);
uint8_t _s21_get_scale(s21_decimal const *decimal);

// def me
void print_bits(size_t size, void *value_ptr);
// del ne

#endif  // SRC_S21_DECIMAL_H_
