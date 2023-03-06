#include <check.h>

#include "../s21_decimal.h"

START_TEST(biggest_decimal_round_conversion) {
  s21_decimal decimal = {.bits = {0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result, 28);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
}
END_TEST

START_TEST(negative_decimal_round_conversion) {
  s21_decimal decimal = {.bits = {0x7, 0xffffffff, 0, 0x80000000}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result, 28);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
}
END_TEST

START_TEST(smallest_decimal_round_conversion) {
  s21_decimal decimal = {.bits = {1, 0, 0, 0x801c0000}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result, 28);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
  ck_assert_int_eq(_s21_get_scale(&result), 28);
}
END_TEST

START_TEST(save_scale_if_possible) {
  s21_decimal decimal = {.bits = {100000000, 0, 0, 0x80080000}};
  s21_decimal result = S21_DECIMAL_NULL;
  _s21_big_decimal big;

  _s21_decimal_to_big_decimal(&decimal, &big);
  _s21_big_decimal_to_decimal(&big, &result, 28);

  ck_assert_int_eq(s21_is_equal(decimal, result), 1);
  ck_assert_int_eq(_s21_get_scale(&result), 8);
}
END_TEST

START_TEST(do_not_save_scale_if_not_possible) {
  _s21_big_decimal big = {.bits = {0x8f640000, 0x3d1536f0, 0x4050652d,
                                   0xb0ec652d, 0x33b2e3c, 0, 0, 0x10000}};
  s21_decimal expect = {.bits = {0x3b9aca01, 0x3b9aca01, 0x3b9aca01, 0xa0000}};
  s21_decimal result = S21_DECIMAL_NULL;

  _s21_big_decimal_to_decimal(&big, &result, 28);

  ck_assert_int_eq(s21_is_equal(expect, result), 1);
  ck_assert_int_eq(_s21_get_scale(&result), 10);
}
END_TEST

TCase *tcase__s21_big_decimal_to_decimal(void) {
  TCase *tc;

  tc = tcase_create("Tests for `_s21_big_decimal_to_decimal`");

  tcase_add_test(tc, biggest_decimal_round_conversion);
  tcase_add_test(tc, negative_decimal_round_conversion);
  tcase_add_test(tc, smallest_decimal_round_conversion);
  tcase_add_test(tc, save_scale_if_possible);
  tcase_add_test(tc, do_not_save_scale_if_not_possible);

  return tc;
}
