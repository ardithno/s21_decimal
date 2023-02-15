#include "../s21_decimal.h"

int _is_extra_bits_not_empty(_s21_big_decimal *big_decimal_ptr) {
  // Return S21_TRUE if upper big decimal's bytes that don't fit in decimal is
  // NOT empty (not equals zero).
  int num_empty_bits = 0;

  for (int i = SCALE; i < BIG_SCALE; i++) {
    if (big_decimal_ptr->bits[i] == 0) {
      num_empty_bits++;
    } else {
      break;
    }
  }

  return (num_empty_bits != BIG_SCALE - SCALE) ? S21_TRUE : S21_FALSE;
}

_s21_big_decimal _big_decimal_shift_right(
    _s21_big_decimal const *big_decimal_ptr, uint8_t shift_count) {
  // Shift big_decimal value bits to right `shift_count` times
  // `shift_count` has to be less or equal than 32

  _s21_big_decimal big_decimal = *big_decimal_ptr;
  uint32_t bits_from_upper_word = 0;

  for (int i = BIG_SCALE - 1; i >= LOW; i--) {
    uint64_t temp = big_decimal.bits[i];

    big_decimal.bits[i] >>= shift_count;
    big_decimal.bits[i] |= bits_from_upper_word;

    temp <<= (32 - shift_count);
    bits_from_upper_word = (uint32_t)(temp & 0xffffffff);
  }

  return big_decimal;
}

void _big_decimal_shift_left(_s21_big_decimal *big_decimal_ptr) {
  // Shift big_decimal_ptr value bits to left once

  uint8_t bit_from_lower_word = 0;

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = big_decimal_ptr->bits[i];

    temp <<= 1;
    temp |= bit_from_lower_word;
    bit_from_lower_word = (uint8_t)(temp >> 32);

    big_decimal_ptr->bits[i] = (uint32_t)(temp & 0xffffffff);
  }
}

_s21_big_decimal _sub_big_decimal(_s21_big_decimal minuend,
                                  _s21_big_decimal subtrahend) {
  _s21_big_decimal big_result = S21_DECIMAL_NULL;

  for (int i = LOW; i < BIG_SCALE; i++) {
    uint64_t temp = 0x100000000 | minuend.bits[i];
    temp -= subtrahend.bits[i];

    big_result.bits[i] = (uint32_t)(temp & 0xffffffff);

    for (int j = i + 1; temp >> 32 == 0; j++) {
      temp = 0x100000000 | minuend.bits[j];
      temp -= 1;
      minuend.bits[j] = (uint32_t)(temp & 0xffffffff);
    }
  }

  return big_result;
}

void s21_set_big_decimal_bit(_s21_big_decimal *big_ptr, uint8_t bit_num) {
  uint8_t word_num = bit_num / 32;
  uint8_t bit_in_word_num = bit_num % 32;

  S21_BIT_SET(big_ptr->bits[word_num], bit_in_word_num);
}

uint32_t s21_div_big_decimal(_s21_big_decimal const *dividend_ptr,
                             _s21_big_decimal const *divisor_ptr,
                             _s21_big_decimal *result_ptr) {
  // Long division algorithm in binary representation:
  //
  // 1. Find the quotient, which is the largest value equal to the divisor
  //    raised to the power of 2 that is less than or equal to the dividend.
  // 2. The exponent of 2 to which the divisor must be raised equals the bit
  //    in the result that has a value of 1.
  // 3. Subtract the quotient from the dividend.
  // 4. Repeat until the divisor is greater than the dividend."

  _s21_big_decimal dividend = *dividend_ptr;
  _s21_big_decimal divisor = *divisor_ptr;
  _s21_big_decimal result = S21_DECIMAL_NULL;

  while (_s21_compare_big_decimals(&divisor, &dividend) != -1) {
    _s21_big_decimal quotient = divisor;
    uint8_t result_bit_num_to_set_one = 0;

    int compare = _s21_compare_big_decimals(&quotient, &dividend);

    while (compare != -1) {
      result_bit_num_to_set_one++;

      _s21_big_decimal temp = quotient;
      _big_decimal_shift_left(&temp);

      compare = _s21_compare_big_decimals(&temp, &dividend);
      quotient = (compare == -1) ? quotient : temp;
    }

    dividend = _sub_big_decimal(dividend, quotient);

    if (result_bit_num_to_set_one != 0) {
      s21_set_big_decimal_bit(&result, result_bit_num_to_set_one - 1);
    }
  }

  *result_ptr = result;
  return dividend.bits[LOW];
}

s21_decimal _s21_convert_suitable_big_decimal_to_decimal(
    _s21_big_decimal const *big_decimal_ptr, uint8_t scale) {
  s21_decimal result = S21_DECIMAL_NULL;

  for (int i = LOW; i < SCALE; i++) {
    result.bits[i] = big_decimal_ptr->bits[i];
  }

  result.bits[SCALE] |= (uint32_t)scale << 16;
  result.bits[SCALE] |= big_decimal_ptr->bits[BIG_SCALE] & 0x80000000;

  return result;
}

int _s21_big_decimal_to_decimal(_s21_big_decimal const *big_decimal_ptr,
                                s21_decimal *decimal_ptr) {
  _s21_big_decimal big = *big_decimal_ptr;

  uint32_t scale = 0;
  uint32_t reminder = 0;

  while ((_is_extra_bits_not_empty(&big)) || (scale < 28 && reminder == 0)) {
    _s21_big_decimal divisor = {.bits = {10, 0, 0, 0, 0, 0, 0}};  // ten as big
    _s21_big_decimal temp_result = S21_DECIMAL_NULL;

    reminder = s21_div_big_decimal(&big, &divisor, &temp_result);

    if (reminder == 0) {
      scale++;
      big = temp_result;
    }

    print_bits(sizeof(big), &big);
  }

  *decimal_ptr = _s21_convert_suitable_big_decimal_to_decimal(&big, 28 - scale);

  return 0;
}
