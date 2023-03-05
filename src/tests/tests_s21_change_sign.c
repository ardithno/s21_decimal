#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(zero_decimal_set_31_bit_to_one) {
  s21_decimal decimal = S21_DECIMAL_NULL;

  s21_change_sign(&decimal);

  ck_assert_int_eq(decimal.bits[3], 1U << 31);
}
END_TEST

START_TEST(zero_negative_decimal_set_31_bit_to_zero) {
  s21_decimal decimal = S21_DECIMAL_NULL;
  decimal.bits[SCALE] = 1U << 31;

  s21_change_sign(&decimal);  // Change sign should produce 0 in scale

  ck_assert_int_eq(decimal.bits[3], 0);
}
END_TEST

START_TEST(using_twice_return_original_value) {
  s21_decimal decimal = {{20, 2, 34, 30}};  // Other bits are filled
  s21_decimal same_value_decimal = {{20, 2, 34, 30}};

  s21_change_sign(&decimal);
  s21_change_sign(&decimal);

  int is_bits_equal = _s21_decimal_compare_bits(&decimal, &same_value_decimal);
  ck_assert_int_eq(is_bits_equal, 0);  // Zero means equal
}
END_TEST

TCase *tcase_s21_change_sign(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_change_sign` implementation");

  tcase_add_test(tc, zero_decimal_set_31_bit_to_one);
  tcase_add_test(tc, zero_negative_decimal_set_31_bit_to_zero);
  tcase_add_test(tc, using_twice_return_original_value);

  return tc;
}
