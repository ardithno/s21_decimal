#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(float_1) {
    s21_decimal dec;
    s21_from_float_to_decimal(-0.478965218, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -0.478965218, 1e-06);
}
END_TEST

START_TEST(float_2) {
    s21_decimal dec;
    s21_from_float_to_decimal(0.8541465951, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 0.8541465951, 1e-06);
}
END_TEST

START_TEST(float_3) {
    s21_decimal dec;
    s21_from_float_to_decimal(1.4896752254, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 1.4896752254, 1e-05);
}
END_TEST

START_TEST(float_4) {
    s21_decimal dec;
    s21_from_float_to_decimal(-1.89651472, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -1.89651472, 1e-05);
}
END_TEST

START_TEST(float_5) {
    s21_decimal dec;
    s21_from_float_to_decimal(-10.000584145, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -10.000584145, 1e-04);
}
END_TEST

START_TEST(float_6) {
    s21_decimal dec;
    s21_from_float_to_decimal(87.185547514, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 87.185547514, 1e-04);
}
END_TEST

START_TEST(float_7) {
    s21_decimal dec;
    s21_from_float_to_decimal(954.6547892, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 954.6547892, 1e-03);
}
END_TEST

START_TEST(float_8) {
    s21_decimal dec;
    s21_from_float_to_decimal(-547.6587123, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -547.6587123, 1e-03);
}
END_TEST

START_TEST(float_9) {
    s21_decimal dec;
    s21_from_float_to_decimal(-1547.6587123, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -1547.6587123, 1e-02);
}
END_TEST

START_TEST(float_10) {
    s21_decimal dec;
    s21_from_float_to_decimal(6874.98541, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 6874.98541, 1e-02);
}
END_TEST

START_TEST(float_11) {
    s21_decimal dec;
    s21_from_float_to_decimal(-86874.98541, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -86874.98541, 1e-01);
}
END_TEST

START_TEST(float_12) {
    s21_decimal dec;
    s21_from_float_to_decimal(-686874.98541, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -686874.98541, 1);
}
END_TEST

START_TEST(float_13) {
    s21_decimal dec;
    s21_from_float_to_decimal(-686874.98541, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, -686874.98541, 1);
}
END_TEST

START_TEST(float_14) {
    s21_decimal dec;
    s21_from_float_to_decimal(4.189654154e18, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 4.189654154e18, 1e+12);
}
END_TEST

START_TEST(float_16) {
    s21_decimal dec;
    s21_from_float_to_decimal(5.6584159654e25, &dec);
    float tmp = 0;
    s21_from_decimal_to_float(dec, &tmp);
    ck_assert_float_eq_tol(tmp, 5.6584159654e25, 1e+19);
}
END_TEST

TCase *tcase_s21_from_float_to_decimal(void) {
  TCase *tc;

  tc = tcase_create("Test for `s21_from_float_to_decimal` implementation");

    tcase_add_test(tc, float_1);
    tcase_add_test(tc, float_2);
    tcase_add_test(tc, float_3);
    tcase_add_test(tc, float_4);
    tcase_add_test(tc, float_5);
    tcase_add_test(tc, float_6);
    tcase_add_test(tc, float_7);
    tcase_add_test(tc, float_8);
    tcase_add_test(tc, float_9);
    tcase_add_test(tc, float_10);
    tcase_add_test(tc, float_11);
    tcase_add_test(tc, float_12);
    tcase_add_test(tc, float_13);
    tcase_add_test(tc, float_14);
    tcase_add_test(tc, float_16);

  return tc;
}
    