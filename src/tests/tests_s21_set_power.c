#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(pow_1) {
  s21_decimal first = {.bits = {0, 0, 0, 0}};
  s21_decimal second = {.bits = {0, 0, 0, 65536}};
  s21_set_power(&first, 1);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
}
END_TEST

START_TEST(pow_28) {
  s21_decimal first = {.bits = {54, 353, 3, 0}};
  s21_decimal second = {.bits = {123, 657, 1, 1835008}};
  s21_set_power(&first, 28);
  ck_assert_int_eq(first.bits[3], second.bits[3]);
}
END_TEST

TCase *tcase_s21_set_power(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_set_power`");

  tcase_add_test(tc, pow_1);
  tcase_add_test(tc, pow_28);

  return tc;
}
