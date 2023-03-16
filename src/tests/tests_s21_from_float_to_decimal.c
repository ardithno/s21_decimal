#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(scale_7_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-0.57495734034, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -0.57495734034, 1e-06);
}
END_TEST

START_TEST(scale_7_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(0.948374356345, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 0.948374356345, 1e-06);
}
END_TEST

START_TEST(scale_6_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(1.85466345, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 1.85466345, 1e-05);
}
END_TEST

START_TEST(scale_6_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-1.352847384, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -1.352847384, 1e-05);
}
END_TEST

START_TEST(scale_5_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-10.84566345, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -10.84566345, 1e-04);
}
END_TEST

START_TEST(scale_5_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(93.654456436, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 93.654456436, 1e-04);
}
END_TEST

START_TEST(scale_4_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(684.53764356345, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 684.53764356345, 1e-03);
}
END_TEST

START_TEST(scale_4_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-949.7546456, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -949.7546456, 1e-03);
}
END_TEST

START_TEST(scale_3_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-5653.10293754, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -5653.10293754, 1e-02);
}
END_TEST

START_TEST(scale_3_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(7342.7865342, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 7342.7865342, 1e-02);
}
END_TEST

START_TEST(scale_2_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-99987.45233234, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -99987.45233234, 1e-01);
}
END_TEST

START_TEST(scale_2_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(86874.98541, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 86874.98541, 1e-01);
}
END_TEST

START_TEST(scale_1_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-124531.987654321, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -124531.987654321, 1);
}
END_TEST

START_TEST(scale_1_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(999999.9, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 999999.98541, 1);
}
END_TEST

START_TEST(scale_over_plus) {
  s21_decimal dec;
  s21_from_float_to_decimal(7.743628326e18, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, 7.743628326e18, 1e+12);
}
END_TEST

START_TEST(scale_over_minus) {
  s21_decimal dec;
  s21_from_float_to_decimal(-5.6584159654e25, &dec);
  float num = 0;
  s21_from_decimal_to_float(dec, &num);
  ck_assert_float_eq_tol(num, -5.6584159654e25, 1e+19);
}
END_TEST

START_TEST(error_1) {
  s21_decimal dec;
  int error = s21_from_float_to_decimal(4e30, &dec);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(error_2) {
  s21_decimal dec;
  int error = s21_from_float_to_decimal(4e-30, &dec);
  ck_assert_int_eq(error, 1);
}
END_TEST

TCase *tcase_s21_from_float_to_decimal(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_from_float_to_decimal` implementation");

  tcase_add_test(tc, scale_7_minus);
  tcase_add_test(tc, scale_7_plus);
  tcase_add_test(tc, scale_6_plus);
  tcase_add_test(tc, scale_6_minus);
  tcase_add_test(tc, scale_5_minus);
  tcase_add_test(tc, scale_5_plus);
  tcase_add_test(tc, scale_4_plus);
  tcase_add_test(tc, scale_4_minus);
  tcase_add_test(tc, scale_3_plus);
  tcase_add_test(tc, scale_3_minus);
  tcase_add_test(tc, scale_2_minus);
  tcase_add_test(tc, scale_2_plus);
  tcase_add_test(tc, scale_1_minus);
  tcase_add_test(tc, scale_1_plus);
  tcase_add_test(tc, scale_over_plus);
  tcase_add_test(tc, scale_over_minus);
  tcase_add_test(tc, error_1);
  tcase_add_test(tc, error_2);

  return tc;
}
