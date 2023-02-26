#include <check.h>

#include "../s21_decimal.h"

START_TEST(decimal_round_conversion) {
  s21_decimal decimal = {.bits = {0xffffffff, 0, 0xffffffff, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
}
END_TEST

START_TEST(negative_decimal_round_conversion) {
  s21_decimal decimal = {.bits = {0x7, 0xffffffff, 0, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
}
END_TEST

TCase *tcase__s21_big_decimal_to_decimal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `_s21_big_decimal_to_decimal`");

  tcase_add_test(tc, decimal_round_conversion);
  tcase_add_test(tc, negative_decimal_round_conversion);

  return tc;
}
