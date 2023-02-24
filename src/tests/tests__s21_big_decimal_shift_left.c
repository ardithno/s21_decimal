#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_shift_left_zero_untouched) {
  _s21_big_decimal big = S21_DECIMAL_NULL;
  _s21_big_decimal null = S21_DECIMAL_NULL;
  int is_equal = -999;

  _s21_big_decimal_shift_left(&big);

  is_equal = _s21_compare_big_decimals(&big, &null);
  ck_assert_int_eq(is_equal, 0);
}
END_TEST

START_TEST(test_negative_zero_shift_left_zero_untouched) {
  _s21_big_decimal big = {.bits = {0, 0, 0, 0, 0, 0, 0x80000000}};
  _s21_big_decimal neg_null = {.bits = {0, 0, 0, 0, 0, 0, 0x80000000}};
  int is_equal = -999;

  _s21_big_decimal_shift_left(&big);

  is_equal = _s21_compare_big_decimals(&big, &neg_null);
  ck_assert_int_eq(is_equal, 0);
}
END_TEST

START_TEST(test_shift_regular_case) {
  _s21_big_decimal big = {.bits = {1, 0, 0, 0, 0, 0, 0}};
  _s21_big_decimal expected = {.bits = {2, 0, 0, 0, 0, 0, 0}};
  int is_equal = -999;

  _s21_big_decimal_shift_left(&big);

  is_equal = _s21_compare_big_decimals(&big, &expected);
  ck_assert_int_eq(is_equal, 0);
}
END_TEST

START_TEST(test_shifting_with_overflow) {
  _s21_big_decimal big = {.bits = {1, 0, 0, 0, 0xffffffff, 0xffffffff, 0}};
  _s21_big_decimal expected = {.bits = {2, 0, 0, 0, 0xfffffffe, 0xffffffff, 0}};
  int is_equal = -999;

  _s21_big_decimal_shift_left(&big);

  is_equal = _s21_compare_big_decimals(&big, &expected);
  ck_assert_int_eq(is_equal, 0);
}
END_TEST

TCase* tcase__s21_big_decimal_shift_left(void) {
  TCase* tc;

  tc = tcase_create("Tests for shift left big decimal");

  tcase_add_test(tc, test_shift_left_zero_untouched);
  tcase_add_test(tc, test_negative_zero_shift_left_zero_untouched);
  tcase_add_test(tc, test_shift_regular_case);
  tcase_add_test(tc, test_shifting_with_overflow);

  return tc;
}
