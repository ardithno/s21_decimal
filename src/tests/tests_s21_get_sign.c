#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

int sign;

void setup_s21_get_sign(void) {
  sign = -10;  // Set sign as non valid value before any test run
}

START_TEST(positive_zero_sign_zero) {
  s21_decimal decimal = S21_DECIMAL_NULL;

  sign = s21_get_sign(decimal);

  ck_assert_int_eq(sign, S21_FALSE);
}
END_TEST

START_TEST(positive_non_zero_value_sign_zero) {
  s21_decimal decimal = {{0, 0, 34, 0}};  // Some positive int value

  sign = s21_get_sign(decimal);

  ck_assert_int_eq(sign, S21_FALSE);
}
END_TEST

START_TEST(negative_zero_sign_one) {
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_change_sign(&decimal);

  sign = s21_get_sign(decimal);

  ck_assert_int_eq(sign, S21_TRUE);
}
END_TEST

START_TEST(negative_non_zero_value_sign_one) {
  s21_decimal decimal = {{0, 0, 34, 0}};  // Some positive int value
  s21_change_sign(&decimal);              // Change sign to negative

  sign = s21_get_sign(decimal);

  ck_assert_int_eq(sign, S21_TRUE);
}
END_TEST

TCase *tcase_s21_get_sign(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_get_sign`");
  tcase_add_checked_fixture(tc, setup_s21_get_sign, NULL);

  tcase_add_test(tc, positive_zero_sign_zero);
  tcase_add_test(tc, positive_non_zero_value_sign_zero);
  tcase_add_test(tc, negative_zero_sign_one);
  tcase_add_test(tc, negative_non_zero_value_sign_one);

  return tc;
}
