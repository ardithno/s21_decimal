#include <check.h>

#include "../s21_decimal.h"

int _tests_sub_check_bits(s21_decimal first, s21_decimal second) {
  int is_equal = S21_TRUE;

  for (int i = LOW; i <= SCALE; i++) {
    if (first.bits[i] != second.bits[i]) is_equal = S21_FALSE;
  }

  return is_equal;
}

START_TEST(possible_verter_test_1) {
  s21_decimal x = {.bits = {1, 1, 1, 65536}};
  s21_decimal y = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal expect = {.bits = {0x2, 0x2, 0x2, 0x10000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_sub(x, y, &result);

  is_equal = _tests_sub_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_2) {
  s21_decimal x = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal y = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal expect = {.bits = {0, 0, 0, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_sub(x, y, &result);

  is_equal = _tests_sub_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

START_TEST(possible_verter_test_3) {
  s21_decimal x = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal y = {.bits = {1, 1, 1, 65536}};
  s21_decimal expect = {.bits = {0x2, 0x2, 0x2, 0x80010000}};
  s21_decimal result = S21_DECIMAL_NULL;
  int is_equal = -999;
  int is_error = -99;

  is_error = s21_sub(x, y, &result);

  is_equal = _tests_sub_check_bits(result, expect);
  ck_assert_int_eq(is_equal, S21_TRUE);
  ck_assert_int_eq(is_error, 0);
}
END_TEST

TCase *tcase_s21_sub(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_sub`");

  tcase_add_test(tc, possible_verter_test_1);
  tcase_add_test(tc, possible_verter_test_2);
  tcase_add_test(tc, possible_verter_test_3);

  return tc;
}
