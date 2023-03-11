#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(normal_float) {
  s21_decimal value = {{8}};
  float a = 0;
  float b = 8.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(s21_get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(null_float) {
  s21_decimal value = {0};
  float a = 0.0;
  float b = 0.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(s21_get_sign(value), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_power) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.8;
  s21_set_power(&value, 1);
  s21_change_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_big_power) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.0000000000000000000000000008;
  s21_set_power(&value, 28);
  s21_change_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_power_max_value) {
  s21_decimal value = {0};
  value.bits[0] = 147484107;
  float a = 0.0;
  float b = -1.47484107;
  s21_set_power(&value, 8);
  s21_change_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_power_max_dec) {
  s21_decimal value = {0};
  value.bits[0] = 214748;
  float a = 0.0;
  float b = -0.00000214748;
  s21_set_power(&value, 11);
  s21_change_sign(&value);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_error) {
  s21_decimal value = {0};
  float *a = NULL;
  int res = s21_from_decimal_to_float(value, a);
  ck_assert_uint_eq(res, 1);
}
END_TEST

TCase *tcase_s21_from_decimal_to_float(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_from_decimal_to_float` implementation");

  tcase_add_test(tc, normal_float);
  tcase_add_test(tc, null_float);
  tcase_add_test(tc, float_power);
  tcase_add_test(tc, float_big_power);
  tcase_add_test(tc, float_power_max_value);
  tcase_add_test(tc, float_power_max_dec);
  tcase_add_test(tc, float_power_max_dec);
  tcase_add_test(tc, float_error);

  return tc;
}
