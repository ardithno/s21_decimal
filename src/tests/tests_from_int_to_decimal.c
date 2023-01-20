#include <check.h>
#include <stdint.h>

#include "../s21_decimal.h"

START_TEST(positive_int_saved_ok) {
  int x = 1;
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_decimal expected = {{x, 0, 0, 0}};

  s21_from_int_to_decimal(x, &decimal);

  ck_assert_int_eq(s21_is_equal(decimal, expected), S21_TRUE);
}
END_TEST

START_TEST(positive_int_max_saved_ok) {
  int x = INT32_MAX;
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_decimal expected = {{x, 0, 0, 0}};

  s21_from_int_to_decimal(x, &decimal);

  ck_assert_int_eq(s21_is_equal(decimal, expected), S21_TRUE);
}
END_TEST

START_TEST(negative_int_saved_ok) {
  int x = -34;
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_decimal expected = {{-x, 0, 0, 1}};  // Set `-x` negative manually

  s21_from_int_to_decimal(x, &decimal);

  ck_assert_int_eq(s21_is_equal(decimal, expected), S21_TRUE);
}
END_TEST

START_TEST(negative_int_equal_positive_int_with_changed_sign) {
  int x = -3400;
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_decimal expected = S21_DECIMAL_NULL;

  s21_from_int_to_decimal(-x, &expected);
  s21_from_int_to_decimal(x, &decimal);
  s21_change_sign(&decimal);

  ck_assert_int_eq(s21_is_equal(decimal, expected), S21_TRUE);
}
END_TEST

START_TEST(negative_int_min_saved_ok) {
  s21_decimal decimal = S21_DECIMAL_NULL;
  s21_decimal expected = {{(unsigned int)INT32_MAX + 1, 0, 0, 0}};

  s21_change_sign(&expected);
  s21_from_int_to_decimal(INT32_MIN, &decimal);

  ck_assert_int_eq(s21_is_equal(decimal, expected), S21_TRUE);
}
END_TEST

TCase *tcase_s21_from_int_to_decimal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_from_int_to_decimal`");

  tcase_add_test(tc, positive_int_saved_ok);
  tcase_add_test(tc, positive_int_max_saved_ok);
  tcase_add_test(tc, negative_int_saved_ok);
  tcase_add_test(tc, negative_int_equal_positive_int_with_changed_sign);
  tcase_add_test(tc, negative_int_min_saved_ok);

  return tc;
}
