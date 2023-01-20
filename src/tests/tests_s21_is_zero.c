#include <check.h>

#include "../s21_decimal.h"

START_TEST(zero_positive_decimal_return_true) {
  s21_decimal decimal = {0};  // Zero positive decimal

  ck_assert_int_eq(s21_is_zero(decimal), S21_TRUE);
}
END_TEST

START_TEST(zero_negative_decimal_return_true) {
  s21_decimal decimal = {0};
  s21_change_sign(&decimal);

  ck_assert_int_eq(s21_is_zero(decimal), S21_TRUE);
}
END_TEST

START_TEST(any_non_zero_return_false) {
  s21_decimal decimal = {34, 2, 0, 2};  // Any non null decimal should suite

  ck_assert_int_eq(s21_is_zero(decimal), S21_FALSE);
}
END_TEST

TCase *tcase_s21_is_zero(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_is_zero` decimal implementation");

  tcase_add_test(tc, zero_positive_decimal_return_true);
  tcase_add_test(tc, zero_negative_decimal_return_true);
  tcase_add_test(tc, any_non_zero_return_false);

  return tc;
}
