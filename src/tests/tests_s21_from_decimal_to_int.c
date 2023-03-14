#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(int_max) {
    int value = INT_MAX;
    int result = 0;
    s21_decimal src = {{INT_MAX, 0, 0, 0}};
    int status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(result, value);
    ck_assert_int_eq(status, 0);
}

START_TEST(int_min) {
    int value = INT_MIN;
    int result = 0;
    s21_decimal src = {{INT_MIN, 0, 0, 0}};
    s21_change_sign(&src);
    int status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(result, value);
    ck_assert_int_eq(status, 0);
}

START_TEST(overflow) {
    int result = 0;
    s21_decimal src = {{INT_MIN, 0, 0, 0}};
    int status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(status, 1);
}


START_TEST(normal_int) {
    s21_decimal src = {{133141, 0, 0, 0}};
    int status = 0;
    int result = 0;
    status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(result, 133141);
    ck_assert_int_eq(status, 0);
}
END_TEST


START_TEST(normal_negative_int) {
    s21_decimal src = {{123451234, 0, 0, 0}};
    int status = 0;
    int result = 0;
    s21_change_sign(&src);
    status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(result, -123451234);
    ck_assert_int_eq(status, 0);
}
END_TEST


START_TEST(overflow_with_scale) {
    s21_decimal src = {{1714336475, 602887423, 48737584, 2148401152}};
    int status = 0;
    int result = 0;
    status = s21_from_decimal_to_int(src, &result);
    ck_assert_int_eq(status, 1);
}
END_TEST


START_TEST(int_with_big_pow) {
  s21_decimal src = {{344, 4294967295, 0, 0}};
  int value = 184467440;
  int result = 0;
  s21_set_power(&src, 11);
  s21_from_decimal_to_int(src, &result);
  ck_assert_int_eq(value, result);

}
END_TEST


START_TEST(int_and_decimal_nul) {
  s21_decimal value_1 = {0};
  s21_decimal test = {0};
  int a = 0;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_sign(value_1), 0);
  a = 123456;
  test.bits[0] = 123456;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  s21_change_sign(&value_1);
  int b = 0;
  s21_from_decimal_to_int(value_1, &b);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_get_sign(value_1), 1);

}
END_TEST

TCase *tcase_s21_from_decimal_to_int(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_from_decimal_to_int` implementation");

  tcase_add_test(tc, int_max);
  tcase_add_test(tc, int_min);
  tcase_add_test(tc, overflow);
  tcase_add_test(tc, normal_int);
  tcase_add_test(tc, normal_negative_int);
  tcase_add_test(tc, overflow_with_scale);
  tcase_add_test(tc, int_with_big_pow);
  tcase_add_test(tc, int_and_decimal_nul);
  
  return tc;
}