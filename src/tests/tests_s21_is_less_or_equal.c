#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

int is_less_or_equal;

void setup_s21_is_less_or_equal(void) { is_less_or_equal = -10; }

START_TEST(positive_zero_and_positive_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(positive_zero_and_negative_zero) {
  s21_decimal first = S21_DECIMAL_NULL;
  s21_decimal second = S21_DECIMAL_NULL;
  s21_change_sign(&first);

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(first_less_then_second) {
  s21_decimal first = {.bits = {35, 34, 0, 0}};
  s21_decimal second = {.bits = {0, 35, 0, 0}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(second_less_then_first) {
  s21_decimal first = {.bits = {0, 0, 1, 0}};
  s21_decimal second = {.bits = {1231, 748, 0, 0}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_FALSE);
}
END_TEST

START_TEST(first_less_negative_sign) {
  s21_decimal first = {.bits = {0, 0, 1, 0x80000000}};
  s21_decimal second = {.bits = {0, 0, 1, 0}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(equal) {
  s21_decimal first = {.bits = {60, 56, 134, 0x80000000}};
  s21_decimal second = {.bits = {60, 56, 134, 0x80000000}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(same_value_different_scale_first_less) {
  s21_decimal first = {.bits = {60, 56, 134, 0x80000}};
  s21_decimal second = {.bits = {60, 56, 134, 0x1000}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(same_all_first_less) {
  s21_decimal first = {.bits = {123, 9, 132, 0x80000}};
  s21_decimal second = {.bits = {12, 52, 154, 0x8000000}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_TRUE);
}
END_TEST

START_TEST(same_all_second_less) {
  s21_decimal first = {.bits = {12, 52, 154, 0x8000000}};
  s21_decimal second = {.bits = {123, 9, 132, 0x80000}};

  is_less_or_equal = s21_is_less_or_equal(first, second);

  ck_assert_int_eq(is_less_or_equal, S21_FALSE);
}
END_TEST

TCase *tcase_s21_is_less_or_equal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_is_less_or_equal`");
  tcase_add_checked_fixture(tc, setup_s21_is_less_or_equal, NULL);

  tcase_add_test(tc, positive_zero_and_positive_zero);
  tcase_add_test(tc, positive_zero_and_negative_zero);
  tcase_add_test(tc, first_less_then_second);
  tcase_add_test(tc, second_less_then_first);
  tcase_add_test(tc, first_less_negative_sign);
  tcase_add_test(tc, equal);
  tcase_add_test(tc, same_value_different_scale_first_less);
  tcase_add_test(tc, same_all_first_less);
  tcase_add_test(tc, same_all_second_less);

  return tc;
}