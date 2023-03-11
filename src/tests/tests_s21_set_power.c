#include <check.h>

#include "../s21_decimal.h"
#include "test_cases.h"

START_TEST(pow_1) {
  s21_decimal decimal = {.bits = {0, 0, 0, 0}};
  uint32_t expected = 1 << 16;

  s21_set_power(&decimal, 1);

  ck_assert_int_eq(decimal.bits[3], expected);
}
END_TEST

START_TEST(pow_28) {
  s21_decimal decimal = {.bits = {54, 353, 3, 0}};
  uint32_t expected = 28 << 16;

  s21_set_power(&decimal, 28);

  ck_assert_uint_eq(decimal.bits[3], expected);
}
END_TEST

START_TEST(the_power_could_be_set_for_negative_decimals) {
  s21_decimal decimal = {.bits = {54, 353, 3, 0x80000000}};  // Negative decimal
  uint32_t expected = (1ULL << 31) | (28 << 16);

  s21_set_power(&decimal, 28);

  ck_assert_uint_eq(decimal.bits[3], expected);
}
END_TEST

TCase *tcase_s21_set_power(void) {
  TCase *tc;

  tc = tcase_create("Tests for `s21_set_power`");

  tcase_add_test(tc, pow_1);
  tcase_add_test(tc, pow_28);
  tcase_add_test(tc, the_power_could_be_set_for_negative_decimals);

  return tc;
}
