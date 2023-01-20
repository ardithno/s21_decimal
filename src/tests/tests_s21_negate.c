#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

int is_bits_equal(const s21_decimal value, const s21_decimal expected) {
  // Comparing bits here because we want `bare metal` comparision
  // And `s21_is_equal` is not suites for it
  int is_equal = S21_TRUE;

  for (int i = 0; i < DECIMAL_PARTS_COUNT; i++) {
    if (value.bits[i] != expected.bits[i]) is_equal = S21_FALSE;
  }

  return is_equal;
}

START_TEST(negate_positive_zero) {
  s21_decimal value = S21_DECIMAL_NULL;
  s21_decimal expected = S21_DECIMAL_NULL;
  s21_change_sign(&expected);

  s21_decimal result = {{0, 1, 2, 3}};  // Any valid but not null value suits
  s21_negate(value, &result);

  ck_assert_int_eq(is_bits_equal(result, expected), S21_TRUE);
}
END_TEST

START_TEST(negate_negative_zero) {
  s21_decimal value = S21_DECIMAL_NULL;
  s21_change_sign(&value);
  s21_decimal expected = S21_DECIMAL_NULL;

  s21_decimal result = {{0, 1, 2, 3}};  // Any valid but not null value suits
  s21_negate(value, &result);

  ck_assert_int_eq(is_bits_equal(result, expected), S21_TRUE);
}
END_TEST

START_TEST(double_negate_return_initial_value) {
  s21_decimal initial = {{20, 2, 1000, 0}};
  s21_decimal result = S21_DECIMAL_NULL;

  s21_negate(initial, &result);
  s21_negate(result, &result);

  ck_assert_int_eq(is_bits_equal(result, initial), S21_TRUE);
}
END_TEST

START_TEST(negate_regular_decimal_is_ok) {
  s21_decimal value = {{20, 2, 1000, 0}};
  s21_decimal expected = {{20, 2, 1000, 1}};  // 1 in last bit is sign actually
  s21_decimal result = S21_DECIMAL_NULL;

  s21_negate(value, &result);

  ck_assert_int_eq(is_bits_equal(result, expected), S21_TRUE);
}
END_TEST

START_TEST(return_zero_as_function_result_if_ok) {
  s21_decimal value = {{20, 2, 1000, 0}};
  s21_decimal destination = S21_DECIMAL_NULL;
  int result = 999;

  result = s21_negate(value, &destination);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(return_one_if_null_pointer_as_argument_passed) {
  s21_decimal value = {{20, 2, 1000, 0}};
  int result = 999;

  result = s21_negate(value, NULL);

  ck_assert_int_eq(result, 1);
}
END_TEST

TCase *tcase_s21_negate(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_negate` implementation");

  tcase_add_test(tc, negate_positive_zero);
  tcase_add_test(tc, negate_negative_zero);
  tcase_add_test(tc, double_negate_return_initial_value);
  tcase_add_test(tc, negate_regular_decimal_is_ok);
  tcase_add_test(tc, return_zero_as_function_result_if_ok);
  tcase_add_test(tc, return_one_if_null_pointer_as_argument_passed);

  return tc;
}
