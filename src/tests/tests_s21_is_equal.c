#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

int is_equal;

void setup_s21_is_equal(void) {
  is_equal = -10; // Set equal as non valid value before any test run
}

START_TEST(positive_zero_equal_other_positive_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_TRUE);
}
END_TEST

START_TEST(negative_zero_equal_other_negative_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;
  s21_change_sign(&first);
  s21_change_sign(&second);

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_TRUE);
}
END_TEST

START_TEST(positive_zero_equal_negative_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;
  s21_change_sign(&second); // Set second as negative zero

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_TRUE);
}
END_TEST

START_TEST(same_value_decimals_is_equal) {
  s21_decimal first = {{0, 2, 4, 34}};
  s21_decimal second = {{0, 2, 4, 34}};

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_TRUE);
}
END_TEST

START_TEST(same_values_with_different_sign_is_not_equal) {
  s21_decimal first = {{0, 2, 4, 34}};
  s21_decimal second = {{0, 2, 4, 34}};
  s21_change_sign(&second);

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_FALSE);
}
END_TEST

START_TEST(same_values_different_scale_is_equal) {
  s21_decimal first = {{0, 0xffffffff, 0, 0}};
  s21_decimal second = {{0, 0xfffe7960, 0x1869f, 0x50000}}; // scale 5

  is_equal = s21_is_equal(first, second);

  ck_assert_int_eq(is_equal, S21_TRUE);
}
END_TEST

TCase *tcase_s21_is_equal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_is_equal`");
  tcase_add_checked_fixture(tc, setup_s21_is_equal, NULL);

  tcase_add_test(tc, positive_zero_equal_other_positive_zero);
  tcase_add_test(tc, negative_zero_equal_other_negative_zero);
  tcase_add_test(tc, positive_zero_equal_negative_zero);
  tcase_add_test(tc, same_value_decimals_is_equal);
  tcase_add_test(tc, same_values_with_different_sign_is_not_equal);
  tcase_add_test(tc, same_values_different_scale_is_equal);

  return tc;
}
