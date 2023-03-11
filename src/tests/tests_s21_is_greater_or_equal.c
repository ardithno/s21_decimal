#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

int is_greater_or_equal;

void setup_s21_is_greater_or_equal(void) { is_greater_or_equal = -10; }

START_TEST(positive_zero_and_negative_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;

  s21_change_sign(&second);

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_TRUE);
}
END_TEST

START_TEST(first_greater_then_second) {
  s21_decimal first = {.bits = {0, 0, 1, 0}};
  s21_decimal second = {.bits = {98761, 12312, 0, 0}};

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_TRUE);
}
END_TEST

START_TEST(first_less_then_second) {
  s21_decimal first = {.bits = {98761, 12312, 0, 0}};
  s21_decimal second = {.bits = {0, 0, 1, 0}};

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_FALSE);
}
END_TEST

START_TEST(value_equal_first_positive_second_negative) {
  s21_decimal first = {.bits = {98761, 123, 1, 0}};
  s21_decimal second = {.bits = {98761, 123, 1, 0x80000000}};

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_TRUE);
}
END_TEST

START_TEST(first_value_less_first_scale_less_first_greater) {
  s21_decimal first = {.bits = {35, 1123, 0, 0x1000}};
  s21_decimal second = {.bits = {98761, 123, 1, 0x80000}};

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_TRUE);
}
END_TEST

START_TEST(first_value_less_first_negative) {
  s21_decimal first = {.bits = {35, 1123, 0, 0x1000}};
  s21_decimal second = {.bits = {98761, 123, 1, 0x80000}};
  s21_change_sign(&first);

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_FALSE);
}
END_TEST

START_TEST(first_value_less_first_negative_second_negative) {
  s21_decimal first = {.bits = {35, 1123, 0, 0x80000}};
  s21_decimal second = {.bits = {98761, 123, 1, 0x1000}};

  s21_change_sign(&first);
  s21_change_sign(&second);

  is_greater_or_equal = s21_is_greater_or_equal(first, second);

  ck_assert_int_eq(is_greater_or_equal, S21_TRUE);
}
END_TEST

TCase *tcase_s21_is_greater_or_equal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_is_greater_or_equal`");
  tcase_add_checked_fixture(tc, setup_s21_is_greater_or_equal, NULL);

  tcase_add_test(tc, positive_zero_and_negative_zero);
  tcase_add_test(tc, first_greater_then_second);
  tcase_add_test(tc, first_less_then_second);
  tcase_add_test(tc, value_equal_first_positive_second_negative);
  tcase_add_test(tc, first_value_less_first_scale_less_first_greater);
  tcase_add_test(tc, first_value_less_first_negative);
  tcase_add_test(tc, first_value_less_first_negative_second_negative);

  return tc;
}
